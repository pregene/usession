#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class CACertInfo
{
public:
  CACertInfo() {}
  ~CACerInfo() {}
  
  int ParseString(string cert_line)
  {
    return 0;
  }
  
  string m_nation; // /C=
  string m_state;  // /ST=
  string m_city;   // /L=
  string m_organization; // /O=
  string m_unit;   // /OU=
  string m_email;  // /CN=
};


int main(int argc, char* argv[])
{
  string cert_line="/C=KR/ST=Seoul/L=Seocho-gu/O=OSCI/OU=Cloud Migration/CN=dhkim.com";
  CACertInfo info;
  
  int status=info.ParseSting(cert_line);
  printf("status=%d\n", status);
  if (status == 0)
  {
    printf("Country: %s\n", info.m_nation.c_str());
  } 
  return 0;
} 