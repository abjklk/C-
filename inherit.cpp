#include <iostream>
#include <graphics.h>
using namespace std;
//base Bird
//der: fly and nofly and falcon,penguin
class Bird
{
  public:
	string color;
	Bird() : color("-") {}
	Bird(string c)
	{
		color = c;
	}
	void fly()
	{
		cout << "Base bird flies!" << endl;
	}
	void run()
	{
		cout << "Base bird runs!" << endl;
	}
};

class Flybird : public Bird
{
  public:
	float altitude;
	Flybird() : Bird()
	{
		altitude = 0;
	}
	Flybird(string c, float alt) : Bird(c)
	{
		altitude = alt;
	}
	void fly()
	{
		cout << "derived bird flies!" << endl;
		for (int i = 0; i < 10; i++)
		{
			altitude = altitude + 1;
			cout << "Altitude is " << altitude << endl;
		}
	}
};

class Runbird : public Bird
{
  public:
	float speed;
	Runbird() : Bird()
	{
		speed = 0;
	}
	Runbird(string c, float sp) : Bird(c)
	{
		speed = sp;
	}
	void run()
	{
		cout << "derived bird runs!" << endl;
		for (int i = 0; i < 10; i++)
		{
			speed = speed + 1;
			cout << "Speed is " << speed << endl;
		}
	}
};

class Falcon : public Flybird
{
  public:
	Falcon() : Flybird() {}
	Falcon(string c, float a) : Flybird(c, a) {}
	void fly()
	{
		cout << "\nFalcon flies\n";
		for (int i = 0; i < 10; i++)
		{
			altitude = altitude + 15;
			cout << "Speed is " << altitude << endl;
		}
	}
	void display()
	{
		cout << "\nBird is of flying type. Color is " << color << endl /*"<< .Altitude is " << altitude<<endl*/;
	}
};

class Penguin : public Runbird
{
  public:
	Penguin() : Runbird() {}
	Penguin(string c, float s) : Runbird(c, s) {}
	void run()
	{
		cout << "\nPenguin runs\n";
		for (int i = 0; i < 10; i++)
		{
			speed = speed + 15;
			cout << "Speed is " << speed << endl;
		}
	}
	void display()
	{
		cout << "\nBird is of running type. Color is " << color << endl; /*" .Speed is " << speed <<endl;*/
	}
};

int main()
{
	Falcon fawkes("Golden", 0);
	Penguin p("Black", 0);
	p.display();
	fawkes.display();
	fawkes.fly();
	p.run();
	fawkes.fly();
	p.run();
	/* code */
	getchar();
	return 0;
}