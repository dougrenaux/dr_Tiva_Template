#include <iostream>
using std::cout, std::endl;
int main()
{
    cout << "This is a C++ compiler: " <<  __cplusplus << endl;
    cout << "Compiled on: " << __DATE__ << " "<< __TIME__ << endl;
    cout << "This is source file/line: " << __FILE__ << " " << __LINE__ << endl;
    cout << "Standard C/version: " << __STDC__ << " " << __STDC_VERSION__ << endl;
 
    return 0;
}
