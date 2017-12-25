#include "Comm_AX12.h"


Comm_AX12::Comm_AX12()
{
}

Comm_AX12::Comm_AX12(PinName _PinCommRx, PinName _PinCommTx)
{
	port_com_out = new Serial(_PinCommTx, _PinCommRx, DEFAULT_BAUD);
	//port_com_in = new Serial(NC, _PinCommRx, DEFAULT_BAUD);

	
	debug = new Serial(USBTX, USBRX, 115200);
	Tx = _PinCommTx;
	Rx = _PinCommRx;
	Baud = DEFAULT_BAUD;
	busy = false;
}


Comm_AX12::Comm_AX12(PinName _PinCommRx, PinName _PinCommTx, int _Baudrate)
{
	port_com_out = new Serial(_PinCommTx, NC, _Baudrate);
	//port_com_in = new Serial(NC, _PinCommRx, _Baudrate);
	debug = new Serial(USBTX, USBRX, 115200);
	Tx = _PinCommTx;
	Rx = _PinCommRx;
	Baud = _Baudrate;
	busy = false;
}


Comm_AX12::~Comm_AX12()
{
	delete port_com_in;
	delete port_com_out;
	delete debug;
}


int Comm_AX12::Send(char _length, char _instr, char *_parameters)
{
	char Cks = Checksum(_length, _instr, _parameters);

	busy = true;


	port_com_out->putc(0xFF);
	port_com_out->putc(0xFF);
	port_com_out->putc(BROADCAST_ID);
	port_com_out->putc(_length);
	port_com_out->putc(_instr);
		

	for (int i = 0; i < _length - 2; i++) {
		port_com_out->putc(_parameters[i]);
	}
	port_com_out->putc(Cks);


	busy = false;

	//DEBUG
	debug->printf("trame envoyee : ");
	debug->printf("%02X ", STARTER_PACKAGE);
	debug->printf("%02X ", BROADCAST_ID);
	debug->printf("%02X ", _length);
	debug->printf("%02X ", _instr);
	for (int i = 0; i < _length - 2; i++) {
		debug->printf("%02X ", _parameters[i]);
	}
	debug->printf("%02X", Cks);
	debug->printf("\n\r");
		
	return 1;
}


int Comm_AX12::Send(char _ID, char _length, char _instr, char *_parameters)
{
	if (getStatus() == true) {
		return 0;
	}
	else {
		
		char Cks = Checksum(_ID, _length, _instr, _parameters);

		busy = true;

		//SEND
		port_com_out->putc(0xFF);
		port_com_out->putc(0xFF);
		port_com_out->putc(_ID);
		port_com_out->putc(_length);
		port_com_out->putc(_instr);
		for (int i = 0; i < _length - 2; i++) {
			port_com_out->putc(_parameters[i]);
		}
		port_com_out->putc(Cks);



		busy = false;

		//DEBUG
		debug->printf("trame envoyee : ");
		debug->printf("%02X", STARTER_PACKAGE);
		debug->printf("%02X", _ID);
		debug->printf("%02X", _length);
		debug->printf("%02X", _instr);
		for (int i = 0; i < _length - 2; i++) {
			debug->printf("%02X", _parameters[i]);
		}
		debug->printf("%02X", Cks);
		debug->printf("\n\r");

		return 1;
	}
}

	int Comm_AX12::Receive(char *reponse)
	{
		wait(0.00004);
	
		int i = 0, j = 0;
		debug->printf("trame recue : ");
		while ((i < 50) && (j < 100000)) {
			if (port_com_in->readable()) {
				reponse[i] = port_com_in->getc();
				debug->printf("%02X", reponse[i]);
				i++;
			}
			else {
				wait(0.00001);
				j++;
			}
		}
		if (j >= 100000) {
			debug->printf("TIMEDOUT\n\r");
			return 0;
		}
			debug->printf("\n\r");
			return 1;
	}


bool Comm_AX12::getStatus()
{
	return busy;
}

void Comm_AX12::debuggage(char msg)
{

	debug->printf("debug : %02X", msg);
	debug->printf("\n\r");
}

char Comm_AX12::Checksum(char _length, char _instr, char * parameter)
{
	char CKS = BROADCAST_ID + _length + _instr;
	for (int i = 0; i < _length - 2; i++) {
		CKS = CKS + parameter[i];
	}
	return ~CKS;
}

char Comm_AX12::Checksum(char _ID, char _length, char instr, char * parameter)
{
	char CKS = _ID + _length + instr;
	for (int i = 0; i < _length - 2; i++) {
		CKS = CKS + parameter[i];
	}
	return ~CKS;
}

