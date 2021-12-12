#include "cache.h"
#include "core.h"
#include<stdbool.h>
#include <stdio.h>


int request(Cache* cache, int opcode, int address, int rd_value, int coreID, int cycle, bool* isStall);

typedef struct Bridge {
	Cache cache_array[4];
	struct bus* main_bus;
	int** stalls; // [0] --> taking care (1), occupied(-1), free(0), [1] --> number of stalls to update (subtract) each time
	FILE* bus_trace;
}Bridge;

typedef struct Cache_instruction {
	int coreID;
	int opcode;
	int rd; //To store values of these registers
	int address;
	int tag;
	int index;
	int msi_state;
	char* msi_transaction;
}Cache_inst;

Cache_inst current_request;
Bridge* main_bridge;