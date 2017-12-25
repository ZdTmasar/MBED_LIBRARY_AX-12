#pragma once
#include "mbed.h"
#include "constantes.h"




class Comm_AX12
{
public:
	Comm_AX12();
	Comm_AX12(PinName _PinCommRx, PinName _PinCommTx); // Baudrate par défaut
	Comm_AX12(PinName _PinCommRx, PinName _PinCommTx, int _Baudrate); // Baudrate décidé par l'utilisateur
	~Comm_AX12();
	int Send(char _length, char _instr, char *_parameters); //En broadcast
	int Send(char _ID, char _length, char _instr, char *_parameters); //à un AX12 précis
	int Receive(char *reponse);
	bool getStatus();
	void debuggage(char msg);

private:
	Serial *port_com_in;
	Serial *port_com_out;
	Serial *debug;
	char Checksum(char _length, char _instr, char *parameter);
	char Checksum(char _ID, char _length, char instr, char *parameter);

	// Attributs
	bool busy;
	PinName Tx;
	PinName Rx;
	int Baud;
};