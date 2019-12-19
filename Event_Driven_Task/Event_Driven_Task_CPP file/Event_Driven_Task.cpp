// Event_Driven_Task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

using namespace std;

class Machine
{
	class State* current;
public:
	Machine();
	void setCurrent(State* s)
	{
		current = s;
	}
	void idle();
	void sensing();
	void processing();
};

class State
{
public:
	virtual void idle(Machine* m)
	{
		cout << "Nodes are in idle state" << endl;
	}
	virtual void sensing(Machine* m)
	{
		cout << "Nodes are sensing" << endl;
	}
	virtual void processing(Machine* m)
	{
		cout << "Nodes are processing" << endl;
	}

};

void Machine::idle()
{
	current->idle(this);
}

void Machine::sensing()
{
	current->sensing(this);
}

void Machine::processing()
{
	current->processing(this);
}

class Idle : public State
{
public:
	Idle()
	{
		cout << "Idle constructor" << endl;
	};
	~Idle()
	{
		cout << "destructor Idle" << endl;
	};
	void sensing(Machine* m);

};

class Sensing : public State
{
public:
	Sensing()
	{
		cout << "Sensing constructor" << endl;
	};
	~Sensing()
	{
		cout << "destructor Sensing" << endl;
	};
	void processing(Machine* m);

};

class Processing : public State
{
public:
	Processing()
	{
		cout << "Processing constructor" << endl;
	};
	~Processing()
	{
		cout << "destructor Processing" << endl;
	};

	void idle(Machine* m);

};

void Idle::sensing(Machine* m)
{
	cout << "Idle to Sensing" << endl;
	m->setCurrent(new Sensing());
	delete this;
	cout << "Reading sensor values!!!" << endl;
	Sleep(1000);
	cout << "Getting data from the humidity sensor..." << endl;
	int a = 1;
	while (a++ <= 5)
	{
		int humidity = (rand() % (100 - 10 + 1)) + 10;
		cout << "The Humidity Sensor Value: " << humidity << endl;
		Sleep(500);
	}

	Sleep(1000);
	cout << "Getting data from the temperature sensor..." << endl;
	int b = 1;
	while (b++ <= 5)
	{
		int temp = (rand() % (100 - 10 + 1)) + 10;
		cout << "Temperature Sensor Value: " << temp << endl;
		Sleep(500);
	}
	Sleep(1000);
	cout << "Values are ready for processing!!!" << endl;
	m->processing();
}

void Sensing::processing(Machine* m)
{
	cout << "Sensing to Processing" << endl;
	m->setCurrent(new Processing());
	delete this;
	cout << "Processing the sensor data!!!" << endl;
	Sleep(1000);
	cout << "Processing the humidity data..." << endl;
	Sleep(1000);
	cout << "Processing the temperature data..." << endl;
	Sleep(1000);
	cout << "Going back to Idle state!!!" << endl;
	Sleep(1000);
	m->idle();
}

void Processing::idle(Machine* m)
{
	cout << "Processing to Idle!!!" << endl;
	m->setCurrent(new Idle());
	delete this;
}

Machine::Machine()
{
	current = new Idle();
	cout << '\n';
}

int main()
{
	Machine fsm;
	char userPreference;
	for (int i = 1; i <= 5; i++)
	{
		cout << "System is idle. Do you want to start sensing (y/n): ";
		cin >> userPreference;
		char opt = char(toupper(userPreference));
		switch (opt)
		{
		case 'Y':
			fsm.sensing();
			Sleep(1000);
			break;
		case 'N':
			continue;
		default:
			cout << "Invalid character!!!" << endl;
			break;
		}
	}
	return 0;
}