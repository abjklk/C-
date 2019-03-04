#include <iostream>
using namespace std;

class Employee{
public:
    string name;
    float salary;
    Employee():name("-"),salary(0){}
    Employee(string name,float salary)
    {
        this->name=name;
        this->salary=salary;
    }
    void hike(float p)
    {
        salary=salary+((p/100)*salary);
    }
    void display()
    {
        cout << "name is " << name << " Salary is " << salary << endl;
    }
};

class Manager : public Employee
{
    public:
    int noOfStocks;
    Manager(string n,float s,int no):Employee(n,s){
        noOfStocks=no;
    }
    void hike(float p)
    {
        salary=salary+((p/100)*salary)+(noOfStocks*10);
    }
};

class Normal : public Employee
{
    public:
    Normal(string n,float s):Employee(n,s){}
    static void hike(Normal n[],float p)
    {
        for(int i=0;i<5;i++)
        {
            n[i].salary=n[i].salary+((p/100)*n[i].salary);
        }
    }
};

int main()
{
    Normal n1("a",200.0);
    Normal n2("b",4500.0);
    Normal n3("c",230.0);
    Normal n4("d",25230.0);
    Normal n5("e",240.0);
    Normal normarr[]={n1,n2,n3,n4,n5};
    Normal::hike(normarr,2.0);
    for(int i=0;i<5;i++)
    {
        normarr[i].display();
    }
    
}