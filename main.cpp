#include <iostream>

using namespace std;

class BankAccount
{
private:
    long int accnum;
    float balance;
public:
    BankAccount():accnum(0000000),balance(0){}
    BankAccount(long int x, float y):accnum(x),balance(y){}
    void addbal(float x)
    {
        balance = balance + x;
        cout << "\n-x-x-x-x-x-credited successfully-x--x-x-x-x--x-x-x-\n"<<endl;
    }
    void rembal(float x)
    {
        balance = balance - x;
        cout << "\n-x-x-x-x--x-x-x-debited successfully-x-x-x--x-x-x\n"<<endl;
    }
    void printAccount()
    {
        cout << "The account number is " << accnum << ".The balance is " << balance << endl;
    }
};

class Customer
{
private:
    string name;
    int custid;
public:
    BankAccount acc;
    Customer():name("Doe"),custid(0){}
    Customer(string a,int b, BankAccount c):name(a),custid(b),acc(c){}
    void printCustomer()
    {
        cout << "name is " << name << " id is " << custid <<endl;
        acc.printAccount();
    }
    void credit(float x)
    {
        acc.addbal(x);
    }
    void debit(float x)
    {
        acc.rembal(x);
    }
    //pass by reference
    void transfer(BankAccount &b, float x)
    {
        acc.rembal(x);
        b.addbal(x);
    }

};


int main()
{
 BankAccount a1(111111111,10200);
 BankAccount a2(1213,200);
 Customer g("abcd",123,a1);
 Customer g2("bda",456,a2);
 g2.printCustomer();
 g.printCustomer();
 g.transfer(g2.acc,300);
 g.printCustomer();
 g2.printCustomer();


}
