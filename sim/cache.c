#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> 

#include "core.h"
#include "cache.h"
#pragma warning(disable:4996)




int translate_address(int address) {
	return address & LEFT_MOST_20;
}

int translate_tag(int address) {
	return (address & RIGHT_MOST_12) >> 8;
}

int translate_index(int address) {
	return address & LEFT_MOST_8;
}

char* translate_mesi_transaction(int opcode) {
	if (opcode == LW) {
		return READ;
	}
	else if (opcode == SW) {
		return WRITE;
	}
	else {
		printf("Error_Chace_3: Opcode given to cache is not legal");
		exit(1);
	}
}

int get_mesi_state(Cache* cache, int index, int tag, bool* tagConflict) {
	if (cache->tsram[index]->mesi_state == I) {
		return I;
	}

	if (cache->tsram[index]->tag == tag) {
		return cache->tsram[index]->mesi_state;
	}

	*tagConflict = true;

	return I;
}