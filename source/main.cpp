#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

class CACertInfo
{
public:
  CACertInfo() {}
  ~CACerInfo() {}

  vector<string> ParseElement(string el)
  {
    vector<string> arrs;
    istringstream ss(el);
    string buff;
    while (getline(ss, buff, '='))
    {
      arrs.push_back(buff);
    } 
    return arrs;
  } 
  
  int ParseString(string cert_line)
  {
    m_certline = cert_line;
    istringstream ss(cert_line);
    string el;
    while (getline(ss, el, '/'))
    {
      vector<string> arr=ParseElement(el);
      if (!arr.empty())
      {
        auto i=arr.begin(); ++i;
        if (*i == "C")  m_nation=*(++i);
        if (*i == "ST") m_state=*(++i);
        if (*i == "L")  m_city=*(++i);
        if (*i == "O")  m_organ=*(++i);
        if (*i == "OU") m_unit=*(++i);
        if (*i == "CN") m_name=*(++i);
        if (*i == "emailAddress") m_email=*(++i);
      }
    }
    return 0;
  }
  
  string m_certline;
  string m_nation; // /C=
  string m_state;  // /ST=
  string m_city;   // /L=
  string m_organ; // /O=
  string m_unit;   // /OU=
  string m_name;   // /CN=
  string m_email;  // /emailAddress
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