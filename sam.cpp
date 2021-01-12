#include <iostream>

using namespace std;

class A{
        public:
            int a;
        A(){
            a = 2;
        }
    };

int main(){
    A a = A();
    // a.a=1;
    cout << a.a;    
}