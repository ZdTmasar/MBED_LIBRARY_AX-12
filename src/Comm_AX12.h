#include "mbed.h"
#include "constantes.h"
//#include <string>



class Comm_AX12
{
public:
	Comm_AX12(PinName _PinCommRx, PinName _PinCommTx); // Baudrate par défaut
	Comm_AX12(PinName _PinCommRx, PinName _PinCommTx, int _Baudrate); // Baudrate décidé par l'utilisateur
	~Comm_AX12();
	int Send(char _length, char _instr, char _parameters[8]); //En broadcast
	int Send(char _ID, char _length, char _instr, char _parameters[8]); //à un AX12 précis
	char* Receive();
	bool getStatus();

private:
	Serial *port_com;
	Serial *debug;
	char Checksum(char _stream[10]); //stream = ID + Stream + Instruction + Parameter1 + etc...

	bool *busy;
	PinName Tx;
	PinName Rx;
	int Baud;
};