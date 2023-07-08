# usession

TLS 1.3서버와 클라이언트 사이에 신뢰 통신을 구축하기 위해서는 openssl 라이브러리를 사용해야 한다. 라이브러리는 1.3.x 이상의 버전을 사용하면 된다.

### 신뢰 통신을 위한 인증서 만들기:
신뢰 통신을 구축하기 위해서는 인증서를 생성하거나 공인기관으로 부터 인증서를 발급 받아 사용해야 한다. 여기에서는 사설 인증서를 만들어서 구축한다.

### 1. 사설 인증 기관 만들기.
   공인기관 대신 인증서를 신뢰 할 수 있는 루트 인증서를 만들어야 한다. 루트 인증서를 만드는 과정은 루트 인증서의 키, 루트 인증서의 서명서, 루트 인증서 순으로 만든다. 
   ```bash
   openssl genrsa : 키생성
   openssl req new : 서명서 만들기
   openssl x509 : 인증서 만들기 
   ```
   우선, 루트 인증서의 키 문서를 만들어 본다.
   
   명령어(linux)
   ```bash
   openssl genrsa -aes256 -out rootkey.key 2048
   ```
   ```bash
   -aes256 : 암호화 키를 암호화 할 알고리즘
   -out : 출력할 키 파일명
   2048 : RSA 알고리즘 키의 길이. 즉 2048 비트의 키 길이를 사용한다는 의미. 1024비트 길이를 사용해도 되지만, 보안 레벨이 낮아 짐.
   ```
   
   루트 인증서의 키를 만들었으면, 키에 대한 서명서 파일을 만들어야 한다. 서명서는 인증서를 발행한 기관에 대한 정보를 입력하는 단계이다.
   인증서 정보는 국가, 지역(주), 도시, 발행기관명(조직명), 발행부서(주체), 발행자 등이 있다.
   ```bash
   국가 : C
   지역 : ST
   도시 : L
   조직 : O (회사명을 입력)
   부서 : OU (부서명을 입력)
   발행자 : CN (서버명 또는 도메인 입력)
   이메일 : emailAddress
   ```
   
   인증서 서명서를 위한 서명 문자열:
   ```bash
   “/C=South Korea/ST=Seoul/L=Seoul/O=CoreTrust, Inc./OU=eurycrypt.com/CN=paul/emailAddress=paul@coretrust.com”
   ```
   
   명령어(Linux)
   ```bash
   openssl req new -key rootkey.key -out root.csr -args “/C=South Korea/ST=Seoul/L=Seoul/O=CoreTrust, Inc./OU=eurycrypt.com/CN=paul/emailAddress=paul@coretrust.com”
   ```
   루트 인증서를 위한 키외 서명서를 만들었다면, 2개의 파일을 이용하여 루트 인증서를 생성한다.
   ```bash
   openssl X509
   ```
   
2. 
 
3. 
