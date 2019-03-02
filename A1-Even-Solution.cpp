#include <iostream>

using namespace std;

class Candidate
{
    public:
        string name;
        int id;
        float salary;
        int post;

        Candidate():name("-"),id(0),salary(0),post(-1){}
        Candidate(string n,int i,float s,int p)
        {
            name=n;
            id=i;
            salary=s;
            post=p;
        }
        void display()
        {
            cout << "\nName of Candidate : " << name << "\nID :" << id << "\nSalary:" << salary << "\nPost :" << post << endl;
        }
};

class College
{
    public:
    string name;
    string address;
    Candidate carr[4];
    int totalCandidates;
    College(string nname,string adr,int t)
    {
        name=nname;
        address=adr;
        totalCandidates=t;
    }
    bool recruitCandidate(Candidate &c)
    {
        int flag=0;
        if(carr[c.post].id==0){
            carr[c.post]=c;
            flag=1;
            totalCandidates++;
        }
        return flag;
    }
    bool replaceCandidate(Candidate &c)
    {
        int flag=0;
        if(carr[c.post].id !=0)
        {
            carr[c.post]=c;
            flag=1;
        }
        return flag;
    }

    void yetToAssignPosts()
    {
        cout << "\n-------------------\nPositions :\n0->HOD\n1->professor\n2->Associate Professor\n3->Lecturer\n\nCandidates not assigned are:\n";
        for(int i=0;i<4;i++)
        {
            if(carr[i].id==0)
                cout << "Position " << i << " not assigned" << endl;
        }
        cout << "\n-------------------\n";
    }

    void display()
    {
        cout << "\n-------------------\nName of College : " << name << "\nAddress : " << address << "\nTotal Candidates are: " << totalCandidates << endl;
        cout << "\nCandidates are :\n";
        for(int i=0;i<4;i++)
        {
            carr[i].display();
        }
        cout << "\n-------------------\n";
    }
};
int main()
{
    //Positions : 0->HOD. 1->professor. 2->Associate Professor. 3->Lecturer.
    Candidate c1;
    Candidate c2("abc",10,20000.0,0);
    Candidate cc("plm",86,20000.0,0);
    Candidate c3("xyz",20,40000.0,1);
    Candidate c4("def",30,25000.0,2);
    Candidate c5("ghi",40,28000.0,3);
    College k("KLE","Hubli",0);

    if(k.recruitCandidate(c2))
        cout << "Candidate added.\n";
    else
        cout << "Candidate could not be added.\n";

    if(k.recruitCandidate(c2))
        cout << "Candidate added.\n";
    else
        cout << "Candidate could not be added.\n";

   k.display();
   
   if(k.replaceCandidate(cc))
        cout << "\nCandidate replaced.\n";
    else
        cout << "Candidate could not be replaced.\n";

    k.display();
    k.yetToAssignPosts();

    if(k.recruitCandidate(c3))
        cout << "Candidate added.\n";
    else
        cout << "Candidate could not be added.\n";

        if(k.recruitCandidate(c4))
        cout << "Candidate added.\n";
    else
        cout << "Candidate could not be added.\n";

        if(k.recruitCandidate(c5))
        cout << "Candidate added.\n";
    else
        cout << "Candidate could not be added.\n";

    k.display();
    k.yetToAssignPosts();

}
