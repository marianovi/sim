#define _CRT_SECURE_NO_WARNINGS
#include "sim.h"


// read lines from imemin and translate to hexadecimal didgits
// fills the instructionArray[pc] according to [opcode, rd, rs, rt, imm1, imm2]
void inst_arr_initation(FILE *current_imem, core *current_core)
{
	int localPC = 0;
	unsigned long long int temp_val;
	long int temp_imm;
	char current_line[IMEM_LINE_SIZE];


	while (fgets(current_line, IMEM_LINE_SIZE, current_imem) != NULL)
	{
		temp_val = (unsigned long long int)strtoll(current_line, NULL, 16); //change to int according to hexa
		current_core->instructionsArray[localPC].opcode = 0xFF & (temp_val >> 24);
		current_core->instructionsArray[localPC].rd = 0xF & (temp_val >> 20);
		current_core->instructionsArray[localPC].rs = 0xF & (temp_val >> 16);
		current_core->instructionsArray[localPC].rt = 0xF & (temp_val >> 12);

		if ((0XFFF & (temp_val >> 11)) == 1) //imm < 0
		{
			temp_imm = (0xFFF & (temp_val >> 12)) - 0xFFF - 1;
			current_core->instructionsArray[localPC].imm = temp_imm;
		}
		else
			current_core->instructionsArray[localPC].imm = 0xFFF & (temp_val >> 12);

		


		current_core->instructionsArray[localPC].Inst_Func = inst_Func_Array[current_core->instructionsArray[localPC].opcode];


		localPC++;
	}
}

//builds a 32 bits instruction code for given core and its PC
unsigned long long int create_inst_code(unsigned int opcd, core *current_core)
{
	unsigned long long int rd, rs, rt, opcode_val = 0;
	long long int imm;
	opcode_val += opcd;
	rd = current_core->instructionsArray[current_core->PC].rd;
	rs = current_core->instructionsArray[current_core->PC].rs;
	rt = current_core->instructionsArray[current_core->PC].rt;
	imm = 0xFFF & current_core->instructionsArray[current_core->PC].imm;
	return (opcode_val << 24) | (rd << 20) | (rs << 16) | (rt << 12) | (imm);
}