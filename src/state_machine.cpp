#include <iostream>

using namespace std;

enum EState 
{
    Off,
    Wait_cmd,
    Reverse,
    Move_straight,
    Clean,
    Error
};

class Robot 
{
    EState state;
    double angle;
    double distance;
public:
    Robot() 
    {
        state = Off;
    }
    ~Robot();
    void processEvent(int state);
    void getCoordinates();
    void reverse(double angle);
    void moveStraight(double distance);
    void clean();
};

void Robot::reverse(double angle) 
{
    cout << "Robot turned to " << angle << " degree\n";
};

void Robot::moveStraight(double distance) 
{
    cout << "Robot moved straight to " << distance << endl;
};

void Robot::clean() 
{
    cout << "Robot cleaned the area\n";
};

void Robot::processEvent(int state) 
{
    while (state != Off) 
    {
        cin >> state;
        switch (state) 
        {
            case Wait_cmd:
                cin >> state;
                break;

            case Reverse:
                double angl;
                cin >> angl;
                Robot::reverse(angl);
                state = Wait_cmd;
                break;

            case Move_straight:
                double dist;
                cin >> dist;
                Robot::moveStraight(dist);
                state = Wait_cmd;
                break;

            case Clean:
                Robot::clean();
                state = Wait_cmd;
                break;

            case Error:
                state = Off;
                break;

            default:
                state = Wait_cmd;
                break;
        }
    }
}

int main() 
{
    int states = Wait_cmd;
    Robot paintRobot;
    
    while (states != Off) 
    {
        cin >> states;
        paintRobot.processEvent(states);
    }

    return 0;
}
