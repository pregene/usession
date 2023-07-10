#include "certmaker.h"

using namespace CTCERT;

int CAIssuer::MakeKEY(string filename, RSABIT bits)
{
  int				ret = CA_SUCCESS;
	RSA				*r = NULL;
	BIGNUM		*bne = NULL;
	BIO				*bp_private = NULL;

	unsigned long	e = RSA_F4;

	// 1. generate rsa key
	bne = BN_new();
	ret = BN_set_word(bne,e);
	if(ret != 1){
    ret = CA_FAIL;
		goto free_all;
	}

	r = RSA_new();
	ret = RSA_generate_key_ex(r, bits, bne, NULL);
	if(ret != 1){
    ret = (CA_FAIL -1);
		goto free_all;
	}

	// 3. save private key
	bp_private = BIO_new_file(filename.c_str(), "w+");
	ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

	m_key=filename;
	
	// 4. free
free_all:
	BIO_free_all(bp_private);
	RSA_free(r);
	BN_free(bne);
  return ret;
}
int CAIssuer::MakeCSR(string filename, string subj)
{
  CACertInfo info(subj);
  /*
  openssl req -new -key root.key
          -out root.csr
          -subj "/C=KO/ST=Seoul/L=Seoul/O=CoreTrust, Inc.
          /OU=eurycrypt.com/CN=paul
          /emailAddress=paul@coretrust.com
          /UID=192.168.100.209"
  */
  string cmd;
  cmd.resize(2048);
  m_csr = filename;
  sprintf((char*) cmd.c_str(),
  		  "openssl req -new -key \"%s\" "
  		  "-out \"%s\" -subj \"%s\" ",
  		  m_key.c_str(),
  		  m_csr.c_str(),
  		  info.Make().c_str());
  		  
  printf("cmd: %s\n", cmd.c_str()); 
  FILE* file = popen(cmd.c_str(), "r");
  if (file)
  {
    char buffer[1024];
    while (fgets(buffer, 1024, file))
    {
      cout << buffer;
    }
    cout << endl;
    pclose(file);
  }  
  return 0;
}
int CAIssuer::MakeCRT(string filename, int days)
{
  /*
    openssl X509 -req -days 99999 
    -extensions v3_ca -set_serial 103 
    -in root.csr -signkey root.key 
    -out root.crt
  */
  string cmd;
  cmd.resize(2048);
  m_crt = filename;
  sprintf((char*) cmd.c_str(), 
		  "openssl x509 -req -days %d "
		  "-extensions v3_ca -set_serial 103 "
		  "-in \"%s\" -signkey \"%s\" "
		  "-out \"%s\" ",
		  days,
		  m_csr.c_str(),
		  m_key.c_str(),
		  m_crt.c_str());
  FILE* file = popen(cmd.c_str(), "r");
  if (file)
  {
    char buffer[1024];
    while (fgets(buffer, 1024, file))
    {
      cout << buffer;
    }
    cout << endl;
    pclose(file);
  }
  return 0;
}

/*
 openssl x509 -req 
 -in CT_client.csr 
 -CA CT_root.crt 
 -CAkey CT_root.key 
 -CAcreateserial 
 -out CT_client.crt
*/

int CACertificate::MakeCRT(string filename, int days)
{
  string cmd;
  cmd.resize(2048);
  if (!m_pCA || m_pCA->GetKEY().empty() || m_pCA->GetCRT().empty())
    return CA_FAIL;
  m_crt = filename;
  sprintf((char*) cmd.c_str(), "openssl x509 -req -days %d -extensions v3_user "
		  	       "-in \"%s\" -CA \"%s\" "
			       "-CAkey \"%s\" -CAcreateserial "
			       "-out \"%s\" ",
			       days,
			       m_csr.c_str(),
			       m_pCA->GetCRT().c_str(),
			       m_pCA->GetKEY().c_str(),
			       m_crt.c_str());
  cout << cmd << endl;
  FILE* file = popen(cmd.c_str(), "r");
  if (file)
  {
    char buffer[1024];
    while (fgets(buffer, 1024, file))
    {
      cout << buffer;
    }
    cout << endl;
    pclose(file);
  }
  return 0;
}
