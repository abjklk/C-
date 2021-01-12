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
    template <int t, float f>
    void withdraw(t)
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
        int id, bal;
        cout << "enter id,bal";
        cin >> id;
        cin >> bal;
        arr[0] = new Savings(id, bal);
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
    int ch;
    while (1)
    {
        cout << "menu\n1.Add Accounts\n2.Withdraw\n3.Deposit\n4.Transfer\n5.Display";
        cin >> ch;
        switch (ch)
        {
        case 1:
            c.addaccs();
            break;
        case 2:
            c.arr[0]->withdraw();
            break;
        case 3:
            c.arr[0]->deposit();
            break;
        case 4:
            int b;
            cout << "enter amt";
            cin >> b;
            c.transfer(b);
            break;
        case 5:
            c.arr[0]->display();
            c.arr[1]->display();
            break;
        }
        system("cls");
    }
}