#include "AX12.h"


#define LOW_MASK 0b0000000011111111
#define HIGH_MASK ~LOW_MASK
#define NORMAL_SPEED_LOW 0x2C
#define NORMAL_SPEED_HIGH 0x01

AX12::AX12(){
	Comm_AX12 port_com(PE_7, PE_8, 115200);
	GetID();
	MaJ();
}

AX12::AX12(char _ID, PinName _RX, PinName _TX)
{
	Comm_AX12 port_com(_RX, _TX, 115200);
	MaJ();
}

AX12::AX12(char _ID, char _Baud, PinName _RX, PinName _TX)
{
	Comm_AX12 port_com(_RX, _TX, _Baud);
	ID = _ID;
	MaJ();
}


bool AX12::Moving(){
	return 0;
}

char AX12::Status(){
	return 0;

}
void AX12::MaJ(){
	char parameters[8] = { PRESENT_POSITION_L, 0x08 };
	char 

	port_com->Send(ID, 0x04, READ_DATA, parameters);
	port_com->Receive();
	

}
bool AX12::GoToPosition(short _DesiredPos, short _DesiredSpeed){

	short position = _DesiredPos / 0.3;
	short speed = _DesiredSpeed / 0.1;
	char parameters[8] = { GOAL_POSITION_L, (position & LOW_MASK), (position & HIGH_MASK) >> 8, (speed & LOW_MASK), (speed & HIGH_MASK) >> 8 };
	port_com->Send(ID, 0x07, WRITE_DATA, parameters);

	return 0;
}

bool AX12::GoToPosition(short _DesiredPos) {

	short position = _DesiredPos / 0.3;

	char parameters[8] = { GOAL_POSITION_L, (position & LOW_MASK), (position & HIGH_MASK) >> 8, NORMAL_SPEED_LOW, NORMAL_SPEED_HIGH};
	port_com->Send(ID, 0x07, WRITE_DATA, parameters);

	return 0;
}
bool AX12::InPosition(short _DesiredPos){
	return 0;
}
void AX12::Receive()
{
}

bool AX12::AtSpeed(short _DesiredSpeed){
	return 0;
}
bool AX12::SetTorqueMax(short _TorqueLim){
	return 0;
}

char AX12::GetID(){
	//char test_ID = 0;

	return 0;
}
short AX12::GetVoltage(){
	return 0;
}
short AX12::GetPosition(){
	return 0;
}
short AX12::GetSpeed(){
	return 0;
}

AX12::~AX12() {

}