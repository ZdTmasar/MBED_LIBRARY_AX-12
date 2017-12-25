#include "AX12.h"

AX12::AX12()
{
}

AX12::AX12(Comm_AX12 *_port_com)
{
	port_com = _port_com;
	MaJ();
}

AX12::AX12(char _ID, Comm_AX12 *_port_com)
{

	port_com = _port_com;
	ActualID = _ID;
	MaJ();
}

AX12::AX12(char _ID, char _Baud, Comm_AX12 *_port_com)
{
	port_com = _port_com;
	ActualID = _ID;
	MaJ();
}


void AX12::Moving()
{
}

char AX12::Status()
{
	return 0;
}
void AX12::MaJ()
{
}

bool AX12::GoToPosition(short _DesiredPos, short _DesiredSpeed){

	short position = _DesiredPos / 0.3;
	short speed = _DesiredSpeed / 0.1;
	char parameters[] = { GOAL_POSITION_L, (position & LOW_MASK), (position & HIGH_MASK) >> 8, (char)(speed & LOW_MASK), (char)((speed & HIGH_MASK) >> 8) };
	port_com->Send(ActualID, 0x07, WRITE_DATA, parameters);

	return 0;
}

bool AX12::GoToPosition(short _DesiredPos) {
	short position = _DesiredPos / 0.3;
	char parameters[] = { GOAL_POSITION_L, (char)(position & LOW_MASK), (char)(position >> 8), NORMAL_SPEED_LOW, NORMAL_SPEED_HIGH};
	
	port_com->Send(ActualID, 0x07, WRITE_DATA, parameters);

	return 0;
}
bool AX12::EndlessTurn(char _direction, short _DesiredSpeed)
{
	char parameter[] = { CW_ANGLE_LIMIT_L , 0x00, 0x00, 0x00, 0x00 };
	port_com->Send(ActualID, 0x07, WRITE_DATA, parameter);
	short speed = _DesiredSpeed / 0.1;
	char Low = (char)(speed & LOW_MASK);
	char High = (((char)((speed & 0b000000110000000) >> 8)) + (0b00000100 & (_direction << 2)));
	char parameters[] = { GOAL_SPEED_L, Low, High };
	port_com->Send(ActualID, 0x05, WRITE_DATA, parameters);
	return 0;
}
bool AX12::Init()
{
	char parameters1[] = { CW_ANGLE_LIMIT_H, 0x00, 0x00, 0x9B, 0x02 };
	port_com->Send(0x07, WRITE_DATA, parameters1); //Set limit angle of 0° to 200°
	char parameters2[] = { LIMIT_TEMPERATURE, TEMP_MAX, VOLT_L, VOLT_H, TORQUE_L, TORQUE_H, RETURN_STATUS, LED_BLINK, SHUTDOWN };
	port_com->Send(0x0B, WRITE_DATA, parameters2); //Set Temperature lvl to maximum, set maximum torque, set LED to blink only for overweight, never shutdown torque

	return 0;
}
bool AX12::InPosition(short _DesiredPos)
{
	return 0;
}

bool AX12::SetTorqueMax(short _TorqueLim){

	char TorqueLow = (char)(LOW_MASK & _TorqueLim);
	char TorqueHigh = (char)(_TorqueLim >> 8);

	char parameters[] = { TORQUE_LIMIT_L, TorqueLow, TorqueHigh };
	port_com->Send(ActualID, 0x04, WRITE_DATA, parameters);

	return 0;
}

void AX12::FindID(){
	char *rep;
	int i = 0;
	char ID_test = 0x00;
	ActualID = 0xFF;
	char *parameters;
	//port_com->debuggage(ID_test);
	while (ActualID == 0xFF) {
		port_com->debuggage(ID_test);
		rep = &(port_com->Send(ID_test, 0x02, PING, parameters)[0]);
		port_com->debuggage(ActualID);
		
		if (*rep != 0) {
			ActualID = ID_test;
			port_com->debuggage(0xAB);
			port_com->debuggage((char)i);
		}
		ID_test++;
		if (ID_test > 50) {
			port_com->debuggage(0xFE);
			ActualID = 0xFE;
		}
	}
}

char AX12::GetID()
{
	return ActualID;
}

void AX12::SetID(char _ID)
{
	char parameter[] = { ID, _ID };
	port_com->Send(0x04, WRITE_DATA, parameter);
	ActualID = _ID;
}

int AX12::GetVoltage()
{
	return PresentVoltage/10;
}

int AX12::GetPosition()
{
	return 0;
}

int AX12::GetTemperature()
{
	return PresentTemperature;
}

int AX12::GetLoad()
{
	return 0;
}

bool AX12::GetMovement()
{
	return moving;
}

AX12::~AX12()
{

}