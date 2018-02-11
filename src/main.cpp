
#include "Comm_AX12.h"
#include "AX12.h"


//Exemple code
int main() {
	Comm_AX12 test_com(PD_6, PD_5);

	
	AX12 number1(0x04, &test_com);
	AX12 number2(0x01, &test_com);
	AX12 all(&test_com); //a object that will control all the AX12 on the bus because his adress by default is BROADCAST


	number1.Init();
	number2.Init();

	number1.EndlessTurn(1, 50);
	number2.EndlessTurn(0, 50);
	//Both motors will turn at the same speed (50rpm) but on in CW and the other in CCW

	wait(5);

	number1.GoToPosition(0, 10); //the first one will go to the angle 0° at the speed of 10RPM
	number2.GoToPosition(200); //the second one will go to the angle 200° at the maximum speed available

	wait(5);

	all.EndlessTurn(1, 40); //both of the AX12 will turn at the same speed and in the same direction

	wait(5);
	
	return 0;
}