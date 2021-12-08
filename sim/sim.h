#ifndef sim
#define sim

#define _CRT_SECURE_NO_WARNINGS

//---------------constsants defenitions-------------

#define MAX_IMEM_SIZE 1024
#define MAX_DMEM_SIZE 2^20
#define NUM_OF_REGS 16



//-------------- Structures -------------

//Core structure:
typedef struct core {
	int PC;
	Reg Regs_array[NUM_OF_REGS];  //holds registers values 
	int jumpFlag;                 // indicates if jump occured
}core;

//Instructions structure:
typedef struct imemin_command {
	unsigned int opcode; // 8 bits
	unsigned int rd; // 4 bits
	unsigned int rs; // 4 bits
	unsigned int rt; // 4 bits
	int imm; // 12 bits
	void(*Inst_Func)(unsigned int rd, unsigned int rs, unsigned int rt);	//Pointer to execution function
}instruction;

//Registers structure:
typedef struct Registers {
	unsigned int val;
	char name[6];
}Reg;

int DMEM_array[MAX_DMEM_SIZE];          //holds the data Memory stack

#endif