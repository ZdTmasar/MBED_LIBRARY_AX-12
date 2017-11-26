#include "Comm_AX12.h"

Comm_AX12 test_com(PE_7, PE_8, 115200);

int main() {

	char parameters[8] = { 0x1E, 0x00, 0x02, 0x00, 0x05 };

		test_com.Send(0x07, WRITE_DATA, parameters);
	
}