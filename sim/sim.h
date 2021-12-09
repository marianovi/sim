#ifndef sim
#define sim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

//---------------constsants defenitions-------------

#define MAX_IMEM_SIZE 1024
#define MAX_DMEM_SIZE 2^20
#define NUM_OF_REGS 16
#define BLOCK_WORD_SIZE 4
#define CACHE_SIZE 256
#define NUMBER_OF_BLOCKS 64
#define IMEM_LINE_SIZE 12       // 10 bits +  \n + \'0'

//--------------Files decleration:---------------------

FILE *imem0;
FILE *imem1;
FILE *imem2;
FILE *imem3;
FILE *memin;
FILE *memout;
FILE *regout0;
FILE *regout1;
FILE *regout2;
FILE *regout3;
FILE *core0trace;
FILE *core1trace;
FILE *core2trace;
FILE *core3trace;
FILE *bustrace;
FILE *dsram0;
FILE *dsram1;
FILE *dsram2;
FILE *dsram3;
FILE *tsram0;
FILE *tsram1;
FILE *tsram2;
FILE *tsram3;
FILE *stats0;
FILE *stats1;
FILE *stats2;
FILE *stats3;

//---------------Static variables:---------

static int files_counter = 1;

//-------------- Structures -------------

//Core structure:
typedef struct core {
	int core_number;
	int PC;
	Reg Regs_array[NUM_OF_REGS];  //holds registers values 
	int jumpFlag;                 // indicates if jump occured
	instruction instructionsArray[MAX_IMEM_SIZE]; //holds all instructions read from imemin, PC is array's index
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

typedef struct bus {
	
};

int DMEM_array[MAX_DMEM_SIZE];          //holds the data Memory stack




//--------------- Opcode functions -----------------------

void update_PC_if_jumped(unsigned int rd);

void add(unsigned int rd, unsigned int rs, unsigned int rt);
void sub(unsigned int rd, unsigned int rs, unsigned int rt);
void and(unsigned int rd, unsigned int rs, unsigned int rt);
void or (unsigned int rd, unsigned int rs, unsigned int rt);
void xor (unsigned int rd, unsigned int rs, unsigned int rt);
void mul (unsigned int rd, unsigned int rs, unsigned int rt);
void sll(unsigned int rd, unsigned int rs, unsigned int rt);
void sra(unsigned int rd, unsigned int rs, unsigned int rt);
void srl(unsigned int rd, unsigned int rs, unsigned int rt);
void beq(unsigned int rd, unsigned int rs, unsigned int rt);
void bne(unsigned int rd, unsigned int rs, unsigned int rt);
void blt(unsigned int rd, unsigned int rs, unsigned int rt);
void bgt(unsigned int rd, unsigned int rs, unsigned int rt);
void ble(unsigned int rd, unsigned int rs, unsigned int rt);
void bge(unsigned int rd, unsigned int rs, unsigned int rt);
void jal(unsigned int rd, unsigned int rs, unsigned int rt);
void lw(unsigned int rd, unsigned int rs, unsigned int rt);
void sw(unsigned int rd, unsigned int rs, unsigned int rt);
void halt(unsigned int rd, unsigned int rs, unsigned int rt);

void(*inst_Func_Array[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int);


#endif