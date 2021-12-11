#pragma once

#include "core.h"
#define SIGN_EXTEND_NUM 20

/**
  * Enumerate pipeline stages
  */
typedef enum PipelineStages {
	FETCH,
	DECODE,
	EXECUTE,
	MEMORY,
	WRITE_BACK
} PipelineStages;

/* pipeline variable if\id */
typedef struct IF_ID {
	int PC;
	int New_PC; /*the new PC */
	Instruction* IR;/*instruction which contains the opcode to check for branch*/
	int delaySlotPC;
} IF_ID;


/*pipeline variable id\ex */
typedef struct ID_EX {
	int PC;
	int A;
	int B;
	Instruction* IR;
} ID_EX;

/* pipeline variable ex\mem */
typedef struct EX_MEM {
	int PC;
	Instruction* IR;
	int ALUOutput;/*the output to be written back to the registers */
	bool isStall;/*check for stall in the pipeline */
} EX_MEM;

/* pipeline variable mem\wb */
typedef struct MEM_WB {
	int PC;
	Instruction* IR;
	int ALUOutput;/*the output to be written back to the registers */
	int LMD;/*the data to be written back to the registers array*/
	bool isStall;/*check for stall in the pipeline */
} MEM_WB;

/*struct for holding information about the stall in each core */
typedef struct StallData {
	int cyclesToStall; /*number of cycles we want to stall in the pipeline */
	bool active; /*is stall exists */
} StallData;