#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "core.h"

/* Initializing the Core registers, both private and pipeline
Returnes - initialized CoreRegister object*/
CoreRegisters* Core_Registers_Initiation() {
	CoreRegisters* registers = NULL;
	IF_ID* if_id = NULL;
	ID_EX* id_ex = NULL;
	EX_MEM* ex_mem = NULL;
	MEM_WB* mem_wb = NULL;

	registers = (CoreRegisters *)calloc(1, sizeof(CoreRegisters));
	if (registers == NULL) {
		printf("Un error occurred while allocating memory for the core registers");
		exit(1); /*exiting the program after an error occured */
	}

	// init pipeline registers
	if_id = calloc(1, sizeof(IF_ID));
	id_ex = calloc(1, sizeof(ID_EX));
	ex_mem = calloc(1, sizeof(EX_MEM));
	mem_wb = calloc(1, sizeof(MEM_WB));
	if (if_id == NULL || id_ex == NULL || ex_mem == NULL || mem_wb == NULL) {
		printf("Un error occurred while allocating memory for the pipeline registers");
		exit(1);/*exiting the program after an error occured */
	}
	registers->if_id = if_id;
	registers->id_ex = id_ex;
	registers->ex_mem = ex_mem;
	registers->mem_wb = mem_wb;

	return registers;
}

/*Initiation of given core parameters
input - Core type pointer to be initiate*/
void Core_status_initiation(Core* current_core) {
	current_core->state.doFetch = true;
	current_core->state.doDecode = current_core->state.doExecute = current_core->state.doMemory = current_core->state.doWriteBack = false;
	current_core->state.fetchExecuted = current_core->state.decodeExecuted = current_core->state.executeExecuted = current_core->state.memoryExecuted = current_core->state.writeBackExecuted = false;
	current_core->state.PC = 0;
	current_core->state.haltPipeline = false;
	current_core->state.haltProgram = false;
	current_core->state.haltNextOperation = false;
	current_core->state.isDelaySlot = false;
	for (int i = 0; i < PIPLINE_LENGTH; i++) {//init stall data
		current_core->stallData[i].active = false;
		current_core->stallData[i].cyclesToStall = 0;
	}
}


/* Initializing all Core parameters
input - Cache type array, holds the given Core cache
output - creates Core array that holds all cores initiate values and returns it*/
Core* Core_parameters_initiation(Cache** cache_array) {
	Core* cores_array = NULL;
	cores_array = (Core *)malloc(sizeof(Core) * CORE_NUM);
	if (cores_array == NULL) {
		printf("Allocation memory error occured, exit program");
		exit(1); /*exiting the program after an error occured */
	}

	for (int i = 0; i < CORE_NUM; i++) {
		// Init core and core registers
		cores_array[i].coreID = i;
		cores_array[i].new_state_Reg = initCoreRegisters();
		cores_array[i].current_state_Reg = initCoreRegisters();
		cores_array[i].Cache = cache_array[i];
		initCoreStatus(&(cores_array[i]));
		initCoreStatistics(&(cores_array[i]));
		cores_array[i].new_state_Reg->if_id->New_PC = 1;
		memset(cores_array[i].instructions, 0, NUMBER_OF_INSTRUCTIONS * sizeof(Instruction));
	}

	return cores_array;
}
