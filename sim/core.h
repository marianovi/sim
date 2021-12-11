#pragma once
#include "cache.h"
#include "pipeline.h"

#define LINE_LENGTH 9
#define NUMBER_OF_INSTRUCTIONS 1024
#define CACHE_FILE_MAX_SIZE 256
#define NUM_OF_REGISTERS 16
#define PIPLINE_LENGTH 5
#define CORE_NUM 4

//Instructions structure:
typedef struct imemin_command {
	unsigned int opcode; // 8 bits
	unsigned int rd; // 4 bits
	unsigned int rs; // 4 bits
	unsigned int rt; // 4 bits
	int imm; // 12 bits
	void(*Inst_Func)(unsigned int rd, unsigned int rs, unsigned int rt);	//Pointer to execution function
}Instruction;

/*Holds the registers values - private and pipeline registers*/
typedef struct CoreRegisters {
	int privateRegisters[NUM_OF_REGISTERS];
	IF_ID* if_id;
	ID_EX* id_ex;
	EX_MEM* ex_mem;
	MEM_WB* mem_wb;
} CoreRegisters;


//Core structure:
typedef struct CoreState {
	int PC;
	bool isDelaySlot;/*check if it is a delay slot instruction*/
	bool haltPipeline;
	bool haltProgram;/*check if we finished the cycles for all the cores */
	bool haltNextOperation;
	bool doFetch, doDecode, doExecute, doMemory, doWriteBack; /*flags for checking if we execute each of the pipeline stages */
	bool fetchExecuted, executeExecuted, decodeExecuted, memoryExecuted, writeBackExecuted;/*flags for printing the pc of the stage or --- for stall */
} CoreState;



/* struct that holds information about the core statistics that will be written to the stats files */
typedef struct Statistics {
	int cycles; /*number of clock cycles the core was running till halt*/
	int instructions;/*number of instructions executed*/
	int decode_stall;/*number of cycles a pipeline stall was inserted in decode stage*/
}Statistics;

/*Core structure: */
typedef struct Core {
	int coreID; /*identifier of the cores - 0 to 3 */
	Cache* Cache; /*the cache of each core */
	Instruction instructions[NUMBER_OF_INSTRUCTIONS]; /*the instructions to be executed on the core */
	CoreRegisters* current_state_Reg; /*the current state register*/
	CoreRegisters* new_state_Reg; /*the new registers that will be entered */
	CoreState state; /*the current state of the core flags parameters */
	Statistics coreStatistics; /*the statistics of the core */
	StallData stallData[PIPLINE_LENGTH]; /*data about the stalls in the core pipeine */
} Core;