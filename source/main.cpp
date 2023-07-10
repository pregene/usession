#include "certinfo.h"
#include "certmaker.h"

using namespace CTCERT;

int main(int argc, char* argv[])
{
  string cert_line="/C=KO/ST=Seoul/L=Seoul/O=CoreTrust, Inc./OU=ca.eurycrypt.com/CN=ca.eurycrypt.com/emailAddress=biz@coretrust.com";
  CACertInfo info;

  cout << "Certificate Information Parser " << VERSION_INFO << ", ";
  cout << "(C)Copyrihgt 2023, CoreTrust, Inc. ";
  cout << "Build Number " << BUILDNO_INFO << endl;

  int status=info.ParseString(cert_line);
  printf("status=%d\n", status);
  if (status == 0)
  {
    printf("Country: %s\n",       info.m_nation.c_str());
    printf("State: %s\n",         info.m_state.c_str());
    printf("Local: %s\n",         info.m_city.c_str());
    printf("Organization: %s\n",  info.m_organ.c_str());
    printf("Unit: %s\n",          info.m_unit.c_str());
    printf("Common: %s\n",        info.m_name.c_str());
    printf("Email: %s\n",         info.m_email.c_str());
  }

  CAIssuer issue;
  issue.MakeKEY("root.key", CA_RSA_2048);
  return 0;
}
