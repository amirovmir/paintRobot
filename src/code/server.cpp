#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

enum EState { WAIT_CMD, MOVE_STRAIGHT, REVERSE, CLEAN, EOFF };

class  CommandStrategy
{
public:
	virtual string getCommand() = 0;
	virtual ~CommandStrategy() {}
};

class  ConsoleCommandStrategy : public CommandStrategy
{
public:
	string getCommand() override
	{
		string cmd;
		cout << "Enter command.\t Command list:\n MoveStraight,\t Reverse,\t Clean\n";
		cin >> cmd;
		return cmd;
	}
};

class NetCommandStrategy : public CommandStrategy
{
public:
    int sock;
    struct sockaddr_in addr;
    char buf[10];
    int bytes_read;
    NetCommandStrategy()
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        addr.sin_family = AF_INET;
        addr.sin_port = htons(3425);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
        {
            perror("bind");
        }
    }

	string getCommand() override
	{
		cout << "Waiting for a command\n";
		string cmd;
		bytes_read = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
        buf[bytes_read + 1] = '\0';
        cmd = buf;
		return cmd;
	}
};

class  OnTestCommandStrategy : public CommandStrategy
{
public:
	virtual string getCommand() override
	{
		return string("On");
	}
};

class Robot
{
	int angle;
	int distance;
	EState state;
	CommandStrategy *commandprocessor;	
public:
	Robot(CommandStrategy *pcommandprocessor) : state(WAIT_CMD), commandprocessor(pcommandprocessor) {};

	~Robot()
	{
		delete commandprocessor;
	}

	void processEvent(string command);
	void Wait_cmdEventProcessing(string cmd);

	void setAngle(int n_angle);
	void setDistance(int n_distance);
	EState getState();
	void setState(EState n_state);
	void reverse(int n_angle);
	void moveStraight(int n_distance);
	void clean();
	int R(const string& com);

	string getCommand()
	{
		return commandprocessor->getCommand();
	}
};

EState Robot::getState()
{
	return state;
};

void Robot::setState(EState n_state)
{
	state = n_state;
};

void Robot::reverse(int n_angle)
{	
	angle = n_angle;
	cout << "Robot turned to " << angle << " degree" << endl;
};

void Robot::moveStraight(int n_distance)
{
	distance = n_distance;
	cout << "Robot moved straight to " << distance << endl;
};

void Robot::clean()
{
	cout << "Robot cleaned the area" << endl;
};

void Robot::Wait_cmdEventProcessing(string cmd)
{
	if (cmd == "Wait_cmd") 
	{
		cout << "Robot is on. Enter command:\n";
	}
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
	else if (com == "MoveStraight")
	{
		return MOVE_STRAIGHT;
	}
	else
	{
		return EOFF;
	}
};

void Robot::processEvent(string command) {
	istringstream cmd(command);
	string response;
	cmd >> response;

	switch (state)
	{
	case WAIT_CMD:
		switch (R(response)) 
		{
			case MOVE_STRAIGHT:
				state = MOVE_STRAIGHT;
				break;
			case REVERSE:
				state = REVERSE;
				break;
			case CLEAN:
				state = CLEAN;
				break;
			case EOFF:
				state = EOFF;
				break;
		}
		break;

	case MOVE_STRAIGHT:
		int distance;
		cmd >> distance;
		moveStraight(distance);
		state = WAIT_CMD;
		break;

	case REVERSE:
		double angl;
		cout << "Enter angle:\n";
		cin >> angl;
		reverse(angl);
		state = WAIT_CMD;
		break;

	case CLEAN:
		clean();
		state = WAIT_CMD;
		break;

	case EOFF:
		state = EOFF;
		break;

	default:
		cout << "Incorrect command. Try again";
		state = WAIT_CMD;
		break;
	}
};

int main(void)
{
	Robot *paintRobot;
	char bind;
	cout << "Choose a way to receive commands: c - console,\tn-network\n";
	cin >> bind;
	if (bind == 'c')
		paintRobot = new Robot(new ConsoleCommandStrategy());
	else if (bind == 'n')
		paintRobot = new Robot(new NetCommandStrategy());

	string cmd;
	while (paintRobot->getState() != EOFF)
	{
		if (paintRobot->getState() == WAIT_CMD)
			cmd = paintRobot->getCommand();
		paintRobot->processEvent(cmd);
	}
	return 0;
}
