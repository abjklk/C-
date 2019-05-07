#include <iostream>
using namespace std;
//predict output
class Base
{
};
class Derived : public Base
{
};
int main()
{
    Derived d;

    try
    {
        throw d;
    }
    catch (Derived d)
    {
        cout << "Caught Derived Exception";
    }
    catch (Derived b)
    {
        cout << "Caught Base Exception";
    }
    return 0;
}