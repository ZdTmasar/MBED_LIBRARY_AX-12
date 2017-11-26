#include "Comm_AX12.h"


Comm_AX12::Comm_AX12(PinName _PinCommRx, PinName _PinCommTx)
{
	port_com = new Serial(_PinCommTx, _PinCommRx, DEFAULT_BAUD);
	debug = new Serial(USBTX, USBRX, 115200);
	Tx = _PinCommTx;
	Rx = _PinCommRx;
	Baud = DEFAULT_BAUD;
	*busy = false;
}


Comm_AX12::Comm_AX12(PinName _PinCommRx, PinName _PinCommTx, int _Baudrate)
{
	port_com = new Serial(_PinCommTx, _PinCommRx, _Baudrate);
	debug = new Serial(USBTX, USBRX, 115200);
	Tx = _PinCommTx;
	Rx = _PinCommRx;
	Baud = _Baudrate;
	*busy = false;
}


Comm_AX12::~Comm_AX12()
{
	delete	port_com;
}


int Comm_AX12::Send(char _length, char _instr, char _parameters[8])
{
	/*if (getStatus() == true) {
		return 0;
	}
	else {*/

		char Cks = 0;
		//vector<char> msg;
		char msg[10] = { 0xFF, 0xFF, 0xFE, _length, _instr };
		int i = 0;
		while (i < _length - 2) {
			msg[i + 5] = _parameters[i];
			i++;
		}
		Cks = Checksum(msg);
		msg[i + 5] = Cks;
		*busy = true;
		for (int j = 0; j < i + 6; j++) {
			port_com->putc(msg[j]);
			debug->printf("%02X", msg[j]);
		}
		debug->printf("\n\r");
		*busy = false;
		return 1;
	//}
}


int Comm_AX12::Send(char _ID, char _length, char _instr, char _parameters[8])
{
	/*if (getStatus() == true) {
		return 0;
	}
	else {*/
		debug->printf("ID: %02X\n\r", _ID);
		debug->printf("Length :%02X\n\r", _length);
		debug->printf("Instr :%02X\n\r", _instr);

		debug->printf("Parameters :", _instr);

		for (int r = 0; r < 8; r++) {
			port_com->printf("%02X\n\r", _parameters[r]);
		}
		
		char Cks = 0;
		//vector<char> msg;
		char msg[10] = { 0xFF, 0xFF, _ID, _length, _instr };
		int i = 0;
		while (i < _length - 2) {
			msg[i + 5] = _parameters[i];
			i++;
		}
		Cks = Checksum(msg);
		msg[i + 5] = Cks;
		*busy = true;
		for (int j = 0; j < i + 6; j++) {
			port_com->putc(msg[j]);
			//debug
			debug->printf("%02X", msg[j]);
		}
		debug->printf("\n\r");
		*busy = false;
		return 1;
	//}
}

	char* Comm_AX12::Receive()
	{
		return 0;
	}


bool Comm_AX12::getStatus()
{
	return *busy;
}


char Comm_AX12::Checksum(char _stream[10])
{
	char check = 0;

	for (int i = 2; i < 4 + _stream[3] - 1; i++) {
		check = check +_stream[i];
	}

	//port_com->printf("%X", check);

	return ~check;
}

