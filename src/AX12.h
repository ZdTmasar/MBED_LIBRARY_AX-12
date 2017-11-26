#ifndef DEFAX12_H
#define DEFAX12_H


#include "Comm_AX12.h"


class AX12{
public:
	AX12(); //On ne connait pas l'ID de l'AX
	AX12(char _ID, PinName _RX, PinName _TX); //Avec le baudrate par défaut
	AX12(char _ID, char _Baud, PinName _RX, PinName _TX); //Avec baudrate décidé
	~AX12();
	char GetID();
	short GetVoltage();
	short GetPosition(); //1 bit = 0.293 deg
	short GetSpeed();  //1 bit = 0.112 RPM
	bool GoToPosition(short _DesiredPos, short _DesiredSpeed);
	bool GoToPosition(short _DesiredPos);

private:

	bool Moving();
	char Status();
	void MaJ();
	bool InPosition(short _DesiredPos);
	void Receive();

	bool AtSpeed(short _DesiredSpeed);
	bool SetTorqueMax(short _TorqueLim);

	//Attributs 

	char ID;
	int CW_limit_angle;
	int CCW_limit_angle;
	int MaxTorque;
	int GoalPosition;
	int MovingSpeed;
	int TorqueLimit;
	int PresentPosition;
	int PresentSpeed;
	int PresentVoltage;
	Comm_AX12 *port_com;
};

#endif