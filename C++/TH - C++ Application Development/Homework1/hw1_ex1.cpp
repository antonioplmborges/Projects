#include <iostream>

using namespace std;

int main()
{
   
    double num1,num2;
    num1 = 10;
    num2 = 5;
    double *fPtr;
    fPtr = &num1;
    cout<<*fPtr<<endl;
    num2=*fPtr;
    cout<<num2<<endl;
    cout<<&num1<<endl;
    cout<<fPtr<<endl;
   
   return 0;
}

