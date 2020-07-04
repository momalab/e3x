#include <iostream>

using std::cout;

int main()
{
    cout << "BEGINNING OF USER CODE\n";
    asm("l.debug");

    //... do stuff
    asm("le.add ze0,ze1,ze2");

    asm("l.debug");
    cout << "ENDING OF USER CODE\n";
}
