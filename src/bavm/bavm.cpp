// BAVM - Basic Arithmetic Virtual Machine
// Compile Command: g++ src/bavm/bavm.cpp -o bin/bavm.exe
#include <stdio.h>
#include <stdint.h>

// Registers
uint64_t rx[32];

void print_registers()
{
	for (int i=0; i<32; i++)
	{
		printf("rx[%d]\t %d\n", i, rx[i]);
	}
}

// Instruction Queue
uint64_t queue[] = {
	261168, 131152, 34870, 0,
};

// Program Counter
uint8_t counter = 0;

uint8_t ret_op(uint64_t inst);
uint8_t ret_r1(uint64_t inst);
uint8_t ret_r2(uint64_t inst);
uint8_t ret_r3(uint64_t inst);
uint64_t ret_imm(uint64_t inst);

int main()
{
	while (counter < 10)
	{
		uint64_t inst = queue[counter];
		
		// Instruction Variables
		uint8_t op = ret_op(inst);
		uint8_t r1 = ret_r1(inst);
		uint8_t r2 = ret_r2(inst);
		uint8_t r3 = ret_r3(inst);
		uint64_t imm = ret_imm(inst);
		
		// Debugging
		//printf("r1 %d, r2 %d, r3 %d, imm %d\n", r1, r2, r3, imm);
		
		// -- Instructions --
		switch (op)
		{
			case 0:
				// [...00000] none/eof
				// Exit Program / Stop Execution
				print_registers();
				return 0;
			break;
			case 16:
				// [...10000] store - r1, imm
				rx[r1] = imm;
			break;
			case 20:
				// [...10100] add - r1, r2, r3
				rx[r3] = uint64_t(rx[r1]+rx[r2]);
				rx[0] = 0;
			break;
			case 21:
				// [...10101] sub - r1, r2, r3
				rx[r3] = uint64_t(rx[r1]-rx[r2]);
				rx[0] = 0;
			break;
			case 22:
				// [...10110] mul - r1, r2, r3
				rx[r3] = uint64_t(rx[r1]*rx[r2]);
				rx[0] = 0;
			break;
			case 23:
				// [...10111] div - r1, r2, r3
				rx[r3] = uint64_t(rx[r1]/rx[r2]);
			break;
		}
		
		counter += 1;
		
		// Ensure zero register stays at zero
		//rx[0] = 0;
	}
	
	return 0;
}

uint8_t ret_op(uint64_t inst) { return uint8_t((inst & 31)); }
uint8_t ret_r1(uint64_t inst) { return uint8_t((inst & 992) >> 5); }
uint8_t ret_r2(uint64_t inst) { return uint8_t((inst & 31744) >> 10); }
uint8_t ret_r3(uint64_t inst) { return uint8_t((inst & 1015808) >> 15); }
uint64_t ret_imm(uint64_t inst) { return ((inst & 4193280) >> 10); }
