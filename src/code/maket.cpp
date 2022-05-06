#include <iostream>
#include<sstream>
#include<string>

#define WAIT_CMD 1
#define REVERSE  2
#define CLEAN    3
#define ON       4
#define OFF      5

using namespace std;

class  CommandStrategy
{
public:
	virtual string getCommand() const = 0;
	virtual ~CommandStrategy() {}
};

class  ConsoleCommandStrategy : public CommandStrategy
{
public:
	virtual string getCommand() const override
	{
		string cmd;
		cin >> cmd;
		return cmd;
	}
};

class NetCommandStrategy : public CommandStrategy
{
	virtual string getCommand() const override
	{
		string cmd;
		//cmd = receive();
		return cmd;
	}
};

class  OnTestCommandStrategy : public CommandStrategy
{
public:
	virtual string getCommand() const override
	{
		return string("On");
	}
};

enum class EState {	Wait_cmd, Reverse, EOn,	EOff };

class Robot
{
	double angle;
	double distance;
	EState state;
	CommandStrategy *commandprocessor;	
public:
	Robot(CommandStrategy *pcommandprocessor) : commandprocessor(pcommandprocessor) {};
	~Robot()
	{
		delete commandprocessor;
	}
	void processEvent(const string& command);
	void Wait_cmdEventProcessing(const string& cmd);

	double getAngle();
	void setAngle(double n_angle);
	double getDistance();
	void setDistance(double n_distance);
	EState getState();
	void setState(EState n_state);
	void reverse(double n_angle);
	void moveStraight(double n_distance);
	void clean();

	int R(const string& com);
	string getCommand()
	{
		return commandprocessor->getCommand();
	}
};

double Robot::getAngle()
{
	return angle;
};

void Robot::setAngle(double n_angle)
{
	angle = n_angle;
};

double Robot::getDistance()
{
	return distance;
};

void Robot::setDistance(double n_distance)
{
	distance = n_distance;
};

EState Robot::getState()
{
	return state;
};

void Robot::setState(EState n_state)
{
	state = n_state;
};

void Robot::reverse(double n_angle)
{	
	setAngle(n_angle);
	cout << "Robot turned to " << getAngle() << " degree" << endl;
};

void Robot::moveStraight(double n_distance)
{
	cout << "Enter distance:\n";
	setDistance(n_distance);
	cout << "Robot moved straight to " << getDistance() << endl;
};

void Robot::clean()
{
	cout << "Robot cleaned the area" << endl;
};

int Robot::R(const string& com)
{
	if (com == "Wait_cmd")
	{
		return WAIT_CMD;
	}
	else if (com == "Reverse")
	{
		return REVERSE;
	}
	else if (com == "Clean")
	{
		return CLEAN;
	}
	else if (com == "On")
	{
		return ON;
	}
	else
	{
		return OFF;
	}
};

void Robot::Wait_cmdEventProcessing(const string& cmd)
{
	if (cmd == "Wait_cmd") {
		cout << "Robot is on. Enter command:\n";
		string com;
		cin >> com;
		processEvent(com);
	}
};

void Robot::processEvent(const string& command) {
	string com;
	cin >> com;
	switch (R(com))
	{
	case WAIT_CMD:
		Wait_cmdEventProcessing(command);
		break;
	case REVERSE:
		double angl;
		cout << "Enter angle:\n";
		cin >> angl;
		reverse(angl);
		setState(EState::Wait_cmd);
		break;
	case CLEAN:
		clean();
		setState(EState::Wait_cmd);
		break;
	default:
		cout << "Incorrect command. Try again";
		break;
	}
};

int main()
{
	Robot paintRobot(new ConsoleCommandStrategy());
	paintRobot.setState(EState::Wait_cmd);
	while (paintRobot.getState() == EState::Wait_cmd)
	{
		string cmd = paintRobot.getCommand();
		paintRobot.processEvent(cmd);
	}
	return 0;
}
