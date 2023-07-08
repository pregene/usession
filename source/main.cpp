#include "certinfo.h"


int main(int argc, char* argv[])
{
  string cert_line="/C=KR/ST=Seoul/L=Seocho-gu/O=OSCI/OU=Cloud Migration/CN=dhkim.com";
  CACertInfo info;
  
  int status=info.ParseString(cert_line);
  printf("status=%d\n", status);
  if (status == 0)
  {
    printf("Country: %s\n", info.m_nation.c_str());
  } 
  return 0;
} 