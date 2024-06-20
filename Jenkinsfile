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
                script {
                    sh 'sudo apt-get update'
                    sh 'sudo apt-get install -y build-essential cmake g++ libgtest-dev python3-pip'
                    
                    // Install gcovr using pip within a virtual environment
                    sh '''
                        python3 -m venv venv
                        . venv/bin/activate
                        pip install gcovr
                    '''
                }
            }
        }
        
        stage('Build') {
            steps {
                script {
                    // Example build commands
                    sh 'cmake .'
                    sh 'make'
                }
            }
        }
        
        stage('Run Unit Tests') {
            steps {
                script {
                    // Example unit test commands
                    sh 'ctest'
                }
            }
        }

        stage('Code Coverage') {
            steps {
                sh 'cd build && gcovr -r .. --html --html-details -o coverage.html'
                publishHTML(target: [
                    reportName: 'Code Coverage',
                    reportDir: 'build',
                    reportFiles: 'coverage.html',
                    alwaysLinkToLastBuild: true,
                    keepAll: true
                ])
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
