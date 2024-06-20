pipeline {
    agent any

    environment {
        SONARQUBE_SERVER_URL = 'http://sonarqube:9000'
        SONARQUBE_CREDENTIALS = 'sqa_f28241f0490ca57c0fc1e31b024af1a3a46c6f54' // Replace with your SonarQube token ID from Jenkins credentials
    }

    stages {
        stage('Checkout') {
            steps {
                git 'https://github.com/s24530/zad12.2.git' // Replace with your repository URL
            }
        }

        stage('Setup Build Environment') {
            steps {
                sh 'sudo apt-get update'
                sh 'sudo apt-get install -y build-essential cmake g++'
                sh 'sudo apt-get install -y libgtest-dev'
                sh '''
                cd /usr/src/googletest
                sudo cmake .
                sudo make
                sudo cp googletest/lib/libgtest.a googletest/lib/libgtest_main.a /usr/lib
                '''
                // Install gcovr
                sh 'sudo apt-get install -y gcovr'
            }
        }

        stage('Build') {
            steps {
                sh 'mkdir -p build'
                dir('build') {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }

        stage('Run Unit Tests') {
            steps {
                sh 'cd build && make test'
            }
        }

        stage('Code Coverage') {
            steps {
                script {
                    // Clean and rebuild with coverage flags
                   sh 'cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage" ..'
                   sh 'cd build && make clean && make'

                    // Ensure coverage_report directory exists
                    sh 'mkdir -p coverage_report'

                    // Generate coverage reports using gcovr
                    sh '''
                    cd build
                    gcovr --root .. --html coverage_report/coverage.html
                    '''

                    // Publish HTML report in Jenkins
                    publishHTML(target: [
                        reportName: 'Code Coverage',
                        reportDir: 'build/coverage_report/coverage.html',
                        alwaysLinkToLastBuild: true,
                        keepAll: true
                    ])
                }
            }
        }
        
        stage('Static Code Analysis') {
            steps {
                sh 'cppcheck --enable=all --xml . 2> cppcheck.xml'
                recordIssues tools: [cppCheck(pattern: 'cppcheck.xml')]
            }
        }

        stage('SonarQube Analysis') {
            steps {
                withSonarQubeEnv('SonarQube') {
                    sh 'build-wrapper-linux-x86-64 --out-dir bw-output make clean all'
                    sh 'sonar-scanner -Dsonar.projectKey=cpp-calculator -Dsonar.sources=. -Dsonar.host.url=${env.SONARQUBE_SERVER_URL} -Dsonar.login=${env.SONARQUBE_CREDENTIALS}'
                }
            }
        }
    }

    post {
        always {
            junit 'build/test-results/*.xml'
            archiveArtifacts artifacts: 'build/*.o', allowEmptyArchive: true
        }
    }
}
