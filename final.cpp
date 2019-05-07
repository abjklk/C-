#include <iostream>
using namespace std;

class Account
{
  public:
    int accno;
    float balance;
    Account()
    {
        accno = 0;
        balance = 0;
    }
    Account(int a, float b)
    {
        accno = a;
        balance = b;
    }
    virtual void withdraw()
    {
        cout << "no";
    }
    virtual void deposit()
    {
        cout << "no";
    }
    virtual void display() = 0;
};

class Savings : public Account
{
  public:
    Savings()
    {
    }
    Savings(int a, float b) : Account(a, b) {}
    void withdraw()
    {
        cout << "withdraw";
    }
    void deposit()
    {
        cout << "deposit";
    }
    void display()
    {
        cout << "savings: " << accno << " " << balance << endl;
    }
};

class PF : public Account
{
  public:
    PF()
    {
    }
    PF(int a, float b) : Account(a, b) {}
    void display()
    {
        cout << "PF: " << accno << " " << balance << endl;
    }
};

class Customer
{
  public:
    string name;
    Account *arr[2];
    void addaccs()
    {
        arr[0] = new Savings(1, 900);
        arr[1] = new PF(2, 1000);
    }
    void displayac()
    {
        arr[0]->display();
        arr[1]->display();
    }
    void transfer(float a)
    {
        arr[0]->balance -= a;
        arr[1]->balance += a;
    }
};

int main()
{
    Customer c;
    c.addaccs();
    c.displayac();
    c.transfer(120);
    c.displayac();
}