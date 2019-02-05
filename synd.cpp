/* Consider a bank 'SyndBank' has created multiple accounts
and pays interest to all accounts periodically.
Simulate the bank scenario by printing account details
before and after paying interest to all accounts.*/

#include <iostream>

using namespace std;
static int noOfAcc = 0;
class BankAcc
{
private:
    int accnum;
    float balance;
public:

    BankAcc()
    {
        accnum = 0;
        balance =0;
        noOfAcc +=1;
    }
    BankAcc(int x , float y)
    {
        accnum= x;
        balance = y;
        noOfAcc +=1;
    }
    void setbal(float x)
    {
        balance = x;
    }
    float getbal()
    {
        return balance;
    }
    void printacc()
    {
        cout << "acc num is " << accnum << " balance is "<< balance<<endl;
    }
};

class Bank
{
    string name;
public:
    BankAcc accs[];
    void payInterest(float interest)
    {
        for(int i=0;i<noOfAcc;i++)
        {
            float x = accs[i].getbal();
            x=x+(interest*x);
            accs[i].setbal(x);
        }
    }
    void printAccounts()
    {
        for(int i=0;i<noOfAcc;i++)
        {
            accs[i].printacc();
        }
    }
};

int main()
{
BankAcc o1;
BankAcc o2(123,1000);
BankAcc o3(456,5000);
Bank Synd;
Synd.accs[3]=(o1,o2,o3);
Synd.printAccounts();
Synd.payInterest(0.05);
Synd.printAccounts();
return 0;
}
