
#include "Comm_AX12.h"
#include "AX12.h"



int main() {
	Comm_AX12 test_com(PG_9, PG_14);
	//Comm_AX12 port_com(DEFAULT_RX, DEFAULT_TX);

	AX12 number1(0x04, &test_com);
	//AX12 number2(0x08, &test_com);

	//char parameter[] = { ID, 0x04 };
	//test_com.Send(0x04, WRITE_DATA, parameter);
	//char parameters[] = { 0x1E, 0x00, 0x02, 0x00, 0x02 };
	//test_com.Send(0x04, 0x07, WRITE_DATA, parameters);

	//test_com.debuggage(0x00);
	//test.SetID(0x01);
	//wait(1);
	//port_com.debuggage(0x00);

	/*unsigned short _DesiredPos = 0;
	unsigned short position = _DesiredPos / 0.3;
	port_com.debuggage((char)(position & LOW_MASK));
	port_com.debuggage((char)((position & HIGH_MASK) >> 8));
	char parameters[8] = { GOAL_POSITION_L, (char)(position & LOW_MASK), (char)((position & HIGH_MASK) >> 8), NORMAL_SPEED_LOW, NORMAL_SPEED_HIGH };
	test_com.Send(0x04, 0x07, WRITE_DATA, parameters);*/

	number1.EndlessTurn(1, 10);
	wait(2);
	number1.EndlessTurn(1, 50);
	wait(2);
	number1.EndlessTurn(0, 20);
	wait(5);

	
	//wait(3);
	//number2.GoToPosition(120, 0);

	
	//port_com.debuggage(0xAA);
	//test_com.Send(0x01, 0x07, WRITE_DATA, parameterss);
	//wait(5);
	//port_com.debuggage(0xBB);
	//test_com.Send(0x01, 0x07, WRITE_DATA, parameters);


	
	
	return 0;
}