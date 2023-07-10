#if !defined(__CORETRUST_CERTIFICATE_ISSUER__)
#define __CORETRUST_CERTIFICATE_ISSUER__

#include "certinfo.h"
#define CA_EXECUTE "openssl"
#define CA_KEY_GEN "genrsa"
#define CA_CSR_GEN "req new"
#define CA_CRT_GEN "X509"

typedef enum
{
    CA_RSA_1024 = 1024,
    CA_RSA_2048 = 2048,
    CA_RSA_4096 = 4096,
} RSABIT;

class CAIssuer
{
public:
    CAIssuer() {}
    ~CAIssuer() {}

    virtual int MakeKEY(string filename,
                RSABIT bits);
    virtual int MakeCSR(string filename,
                string subj);
    virtual int MakeCRT(string filename);
    string GetKEY() {return m_key;}
    string GetCSR() {return m_csr;}
    string GetCRT() {return m_crt;}
    int SetKEY(string filename)
    {
        m_key = filename;
        return CA_SUCCESS;
    }
    int SetCSR(string filename)
    {
        m_csr = filename;
        return CA_SUCCESS;
    }
    int SetCRT(string filename)
    {
        m_crt = filename;
        return CA_SUCCESS;
    }

private:
    string m_key;
    string m_csr;
    string m_crt;

};

class CACertificate : public CAIssuer
{
public:
    CACertificate() : m_pCA(0) {}
    ~CACertificate() {}
    CACertificate(CAIssuer* pCA)
    {
        SetCA(pCA);
    }
    int SetCA(CAIssuer* pCA)
    {
        m_pCA=pCA;
        return CA_SUCCESS;
    }
    virtual int MakeKEY(string filename,
                RSABIT bits);
    virtual int MakeCSR(string filename,
                string subj);
    virtual int MakeCRT(string filename);

private:
    CAIssuer* m_pCA;
};

#endif // __CORETRUST_CERTIFICATE_ISSUER__
