#pragma once 

#include <stdbool.h>
#include "pipeline.h"


//Private functions:

int sign_extention(int immediate) {
	immediate <<= SIGN_EXTEND_NUM;
	immediate >>= SIGN_EXTEND_NUM;
	return immediate;
}


void branchResolution(Core *core) {
	bool isJump = false;
	bool isLink = false;
	int left_condition_reg_val;
	int right_condition_reg_val;
	/*calculating the two variables which we compare in jump instructions*/
	int immidiate_value = sign_extention(core->current_state_Reg->if_id->IR->imm);
	right_condition_reg_val = core->current_state_Reg->if_id->IR->rt == 1 ? immidiate_value : core->current_state_Reg->privateRegisters[core->current_state_Reg->if_id->IR->rt];
	left_condition_reg_val = core->current_state_Reg->if_id->IR->rs == 1 ? immidiate_value : core->current_state_Reg->privateRegisters[core->current_state_Reg->if_id->IR->rs];
	/*Branch Resolution*/
	if (isBranchOpcode(core->current_state_Reg->if_id->IR->opcode) || core->current_state_Reg->if_id->IR->opcode == 15) {/*jump instructions*/
		if (core->current_state_Reg->if_id->IR->opcode == 9) /*BEQ*/
			isJump = left_condition_reg_val == right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 10)/*BNE*/
			isJump = left_condition_reg_val != right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 11)/*BLT*/
			isJump = left_condition_reg_val < right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 12)/*BGT*/
			isJump = left_condition_reg_val > right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 13)/*BLE*/
			isJump = left_condition_reg_val <= right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 14)/*BGE*/
			isJump = left_condition_reg_val >= right_condition_reg_val;
		else if (core->current_state_Reg->if_id->IR->opcode == 15) {/*JAL*/
			isJump = true;
			isLink = true;
		}
	}
	if (core->state.isDelaySlot) {
		core->new_state_Reg->if_id->New_PC = core->new_state_Reg->if_id->delaySlotPC;
		core->state.isDelaySlot = false;
	}
	if (isJump) {
		if (isLink) {
			core->new_state_Reg->privateRegisters[15] = core->state.PC + 1;
		}
		int newPC = core->current_state_Reg->if_id->IR->rd == 1 ?
			immidiate_value & 0x000003FF :
			core->current_state_Reg->privateRegisters[core->current_state_Reg->if_id->IR->rd] & 0x000003FF; /*Low bits 9:0 of Rd*/
		if (!core->state.isDelaySlot) {
			core->state.isDelaySlot = true;
			core->new_state_Reg->if_id->New_PC = newPC;
			core->new_state_Reg->if_id->delaySlotPC = newPC + 1;
		}
		else {
			core->new_state_Reg->if_id->New_PC = newPC;
		}
	}
	else /*jump not taken*/
		core->new_state_Reg->if_id->New_PC = core->state.PC + 1;
}

void loadRegsForExecute(Core* core) {
	core->current_state_Reg->if_id->IR->imm = sign_extention(core->current_state_Reg->if_id->IR->imm);
	if (core->current_state_Reg->if_id->IR->rs == 1)/*gets the value of immediate*/
		core->new_state_Reg->id_ex->A = core->current_state_Reg->if_id->IR->imm;
	else
		core->new_state_Reg->id_ex->A = core->current_state_Reg->privateRegisters[core->current_state_Reg->if_id->IR->rs];
	if (core->current_state_Reg->if_id->IR->rt == 1)/*gets the value of immediate*/
		core->new_state_Reg->id_ex->B = core->current_state_Reg->if_id->IR->imm;
	else
		core->new_state_Reg->id_ex->B = core->current_state_Reg->privateRegisters[core->current_state_Reg->if_id->IR->rt];
}


//Public functions:


void Fetch(CoreRegisters* current_Reg, Core* current_core, StallData* stall) {
	if (!current_core->state.doFetch || current_core->state.PC == -1) { // reached end of program (halt in decode -> PC = -1)
		current_core->new_state_Reg->if_id->PC = current_core->state.PC;
		current_core->state.fetchExecuted = false;/*for the trace printing*/
		return;
	}
	if (stall[EXECUTE].active || stall[MEMORY].active) {
		current_core->state.fetchExecuted = true;
		return;
	}
	current_core->new_state_Reg->if_id->PC = current_core->state.PC;
	current_core->new_state_Reg->if_id->IR = &(current_core->instructions[current_core->state.PC]);
	current_core->state.fetchExecuted = true;
	if (current_core->new_state_Reg->if_id->New_PC != -1) {
		current_core->state.doDecode = true;
		current_core->coreStatistics.instructions++; // number of instructions executed
	}
}


void Decode(CoreRegisters* currentRegisters, Core* current_core, StallData* stallData) {
	if (!current_core->state.doDecode) {
		current_core->state.decodeExecuted = false;
		return;
	}
	if (stallData[EXECUTE].active || stallData[MEMORY].active) {
		current_core->state.decodeExecuted = true;
		return;
	}
	current_core->new_state_Reg->id_ex->PC = currentRegisters->if_id->PC;
	current_core->new_state_Reg->id_ex->IR = currentRegisters->if_id->IR;
	if (currentRegisters->if_id->PC == -1) { // empty pipeline
		current_core->state.decodeExecuted = false;
		return;
	}
	current_core->state.doExecute = true;
	current_core->state.decodeExecuted = true;
	if (currentRegisters->if_id->IR->opcode == 20) { // reached halt
		current_core->new_state_Reg->if_id->New_PC = -1;
		current_core->state.doDecode = false;
		return;
	}

	loadRegsForExecute(current_core);
	branchResolution(current_core);
}