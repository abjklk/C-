#include <iostream>
using namespace std;

class Part
{
  public:
    string name;
    string desc;
    int id;
    virtual void display() = 0;
};

class Sensor : public Part
{
  public:
    string type;
    void display()
    {
        cout << "hi";
    }
};

class User
{
  public:
    string username;
    string password;
    Sensor s[5];
    void addS(Sensor x)
    {
        s[0] = x;
    }
};

int main()
{
}