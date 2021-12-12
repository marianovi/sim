#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cache.h"
#define NUM_OF_CORES 4

typedef enum bus_state {
	NO_COMMAND,
	BUSRD,
	BUSRDX,
	FLUSH
}bus_state;

typedef enum bus_device {
	CORE_0,
	CORE_1,
	CORE_2,
	CORE_3,
	MEMORY_4
}bus_device;

typedef struct bus {
	int* main_memory;
	int*** memory_state;  //[0] is for msi operation, [1] is for storing type of opcoding in case of LL or SC
	int bus_origid;
	int bus_cmd;
	int bus_addr;
	int bus_data;
}bus;
