#pragma once


#define NUM_OF_BLOCK (256)

/* Cache structure:*/
typedef struct cache {
	int dsram[NUM_OF_BLOCK];
	struct Tsram** tsram;
	int coreID;
	int read_hit;
	int read_miss;
	int write_hit;
	int write_miss;
	int mem_stall;
}Cache;