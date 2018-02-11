#ifndef DEFAX12_H
#define DEFAX12_H


#include "Comm_AX12.h"


class AX12{
public:
	AX12();
	AX12(Comm_AX12 *_port_com); //If we don't know the adress
	AX12(char _ID, Comm_AX12 *_port_com); //with default baudrate
	AX12(char _ID, char _Baud, Comm_AX12 *_port_com); //with specific baudrate
	~AX12();
	void FindID();
	char GetID();
	void SetID(char _ID);
	int GetVoltage(); //(value / 10) = temp
	int GetPosition(); 
	int GetTemperature();
	int GetLoad();
	bool GetMovement();
	bool GoToPosition(short _DesiredPos, short _DesiredSpeed); //just use angle and RPM  (1 bit = 0.112 RPM //1 bit = 0.293 deg)
	bool GoToPosition(short _DesiredPos);
	bool EndlessTurn(char _direction, short _DesiredSpeed);
	bool Init();

private:

	void Moving();
	char Status();
	void MaJ();
	bool InPosition(short _DesiredPos);
	bool SetTorqueMax(short _TorqueLim);

	//Attributs 

	char ActualID;
	bool moving;
	int CW_limit_angle;
	int CCW_limit_angle;
	int MaxTorque;
	short GoalPosition;
	short MovingSpeed;
	int TorqueLimit;
	short *PresentPosition;
	short *PresentSpeed;
	short PresentVoltage;
	short *PresentLoad;
	char PresentTemperature;
	Comm_AX12 *port_com;
};

#endif