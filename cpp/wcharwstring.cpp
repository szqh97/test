#include <cstring>
#include <iostream>

int main()
{
#if 0
   const char text[] = "olé" ;


   std::cout << "sizeof(char)    : " << sizeof(char) << std::endl ;
   std::cout << "text            : " << text << std::endl ;
   std::cout << "sizeof(text)    : " << sizeof(text) << std::endl ;
   std::cout << "strlen(text)    : " << strlen(text) << std::endl ;

   std::cout << "text(bytes)     :" ;

   for(size_t i = 0, iMax = strlen(text); i < iMax; ++i)
   {
      std::cout << " " << static_cast<unsigned int>(
                              static_cast<unsigned char>(text[i])
                          );
   }

   std::cout << std::endl << std::endl ;

   // - - - 
#endif

   const wchar_t wtext[] = L"a数第一个字节的首字符为非";
   const std::string s = "a数第一个字节的首字符为非";

   std::cout << "sizeof(wchar_t) : " << sizeof(wchar_t) << std::endl ;
   //std::cout << "wtext           : " << wtext << std::endl ; <- error
   std::cout << "wtext           : UNABLE TO CONVERT NATIVELY." << std::endl ;
   std::wcout << L"wtext           : " << wtext << std::endl;

   std::cout << "sizeof(wtext)   : " << sizeof(wtext) << std::endl ;
   std::cout << s.size() << std::endl;
   std::cout << "wcslen(wtext)   : " << wcslen(wtext) << std::endl ;

   std::cout << "wtext(bytes)    :" ;

   for(size_t i = 0, iMax = wcslen(wtext); i < iMax; ++i)
   {
      std::cout << " " << static_cast<unsigned int>(
                              static_cast<unsigned short>(wtext[i])
                              );
   }

   std::cout << std::endl << std::endl ;

   return 0;
}
