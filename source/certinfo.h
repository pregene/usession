#if !defined(__CORETRUST_CERTIFICATE_INFO__)
#define __CORETRUST_CERTIFICATE_INFO__

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
  ~CACertInfo() {}

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
      if (el.empty())
        continue;
      vector<string> arr=ParseElement(el);
      if (!arr.empty())
      {
        auto i=arr.begin(); //++i;
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
  string Make(string nation,
              string state,
              string city,
              string organ,
              string unit,
              string name,
              string email)
  {
    m_nation=nation;
    m_state=state;
    m_city=city;
    m_organ=organ;
    m_unit=unit;
    m_name=name;
    m_email=email;

    int bufferlen=nation.length();
    bufferlen += state.length();
    bufferlen += city.length();
    bufferlen += organ.length();
    bufferlen += unit.length();
    bufferlen += name.length();
    bufferlen += email.length();
    bufferlen += 200;
    m_certline.clear();
    m_certline.resize(bufferlen);

    sprintf((char*)m_certline.c_str(),
            "/C=%s/ST=%s/L=%s/O=%s/OU=%s/CN=%s/emailAddress=%s",
            nation.c_str(),
            state.c_str(),
            city.c_str(),
            organ.c_str(),
            unit.c_str(),
            name.c_str(),
            email.c_str());
    return m_certline;
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

#endif // __CORETRUST_CERTIFICATE_INFO__
