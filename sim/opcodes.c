#define _CRT_SECURE_NO_WARNINGS
#include "sim.h"
// Opcode instructions functions:


//if jump occured -jumpFlag =1
//PC=R[rd][low bits 11:0]
void update_PC_if_jumped(unsigned int rd, core* current_core)
{
	current_core->PC = current_core->Regs_array[rd].val & 0x3FF;
	current_core->jumpFlag = 1;
}

//opcode - 0
// R[rd] = R[rs] + R[rt]
void add(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val + current_core->Regs_array[rt].val;
}

//opcode - 1
// R[rd] = R[rs] - R[rt]
void sub(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val - current_core->Regs_array[rt].val;
}

//opcode - 2
// R[rd] = R[rs] & R[rt]
void and(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val & current_core->Regs_array[rt].val;
}

//opcode - 3
// R[rd] = R[rs] | R[rt]
void or (unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val | current_core->Regs_array[rt].val;
}

//opcode - 6
// R[rd] = R[rs] << R[rt]
void sll(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val << current_core->Regs_array[rt].val;
}

//opcode - 7
// R[rd] = R[rs] >> R[rt]
void sra(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->Regs_array[rs].val >> current_core->Regs_array[rt].val;
}

//opcode - 8
// R[rd] = R[rs] >> R[rt], logical shift
void srl(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = current_core->(unsigned)Regs_array[rs].val >> current_core->Regs_array[rt].val;
}

//opcode - 9
//if (R[rs] == R[rt]) pc = R[rd][low bits 9:0]
void beq(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val == current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 10
//if (R[rs] != R[rt]) pc = R[rd][low bits 9:0]
void bne(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val != current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 11
//if (R[rs] < R[rt]) pc = R[rd][low bits 9:0]
void blt(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val < current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 12
//if (R[rs] > R[rt]) pc = R[rd][low bits 9:0]
void bgt(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val > current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 13
//if (R[rs] <= R[rt]) pc = R[rd][low bits 9:0]
void ble(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val <= current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 14
//if (R[rs] >= R[rt]) pc = R[rd][low bits 9:0]
void bge(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	if (current_core->Regs_array[rs].val >= current_core->Regs_array[rt].val)
		update_PC_if_jumped(rd, current_core);
}

//opcode - 15
//R[15] = pc + 1 (next instruction address), pc = R[rd][9:0]
void jal(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[15].val = current_core->PC;
	update_PC_if_jumped(rd, current_core);
}

//opcode - 16
//R[rd] = MEM[R[rs]+R[rt]]
void lw(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->Regs_array[rd].val = DMEM_array[current_core->Regs_array[rs].val + current_core->Regs_array[rt].val];
}

//opcode - 17
//MEM[R[rs]+R[rt]] = R[rd]
void sw(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	DMEM_array[current_core->Regs_array[rs].val + current_core->Regs_array[rt].val] = current_core->Regs_array[rd].val;
}


//opcode - 20
//Halt execution, exit simulator
void halt(unsigned int rd, unsigned int rs, unsigned int rt, core* current_core)
{
	current_core->PC = MAX_IMEM_SIZE + 1;
}

//sets the values of the instruction functions pointers in an array
void(*inst_Func_Array[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int) = {
	{&add},
	{&sub},
	{&and},
	{&or },
	{&xor},
	{&mul},
	{&sll},
	{&sra},
	{&srl},
	{&beq},
	{&bne},
	{&blt},
	{&bgt},
	{&ble},
	{&bge},
	{&jal},
	{&lw},
	{&sw},
	{&halt}
};
