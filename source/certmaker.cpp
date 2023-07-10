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
  		  
  return 0;
}
int CAIssuer::MakeCRT(string filename)
{
  return 0;
}
