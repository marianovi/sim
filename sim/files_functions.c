#define _CRT_SECURE_NO_WARNINGS
#include "sim.h"




// Check if the given file exists, if NULL prints error and exit the simulator
// input- file name , mode -"w"/"r", output- file adress.
//counts the files opened
FILE *get_file(char *file_name, char *file_mode)
{
	FILE *temp_file = NULL;
	temp_file = fopen(file_name, file_mode);
	if (temp_file == NULL) {
		printf("Error occurred while attempting to open file number - %d, named as %s", files_counter, file_name);
		exit(1);
	}
	files_counter++;
	return temp_file;
}

// initializing all of the files, using get file:
void files_initiation(char *argv[])
{
	// input files:
	imem0 = get_file(argv[files_counter], "r");
	imem1 = get_file(argv[files_counter], "r");
	imem2 = get_file(argv[files_counter], "r");
	imem3 = get_file(argv[files_counter], "r");
	memin = get_file(argv[files_counter], "r");


	// output files:
	memout = get_file(argv[files_counter], "w");
	regout0 = get_file(argv[files_counter], "w");
	regout1 = get_file(argv[files_counter], "w");
	regout2 = get_file(argv[files_counter], "w");
	regout3 = get_file(argv[files_counter], "w");
	core0trace = get_file(argv[files_counter], "w");
	core1trace = get_file(argv[files_counter], "w");
	core2trace = get_file(argv[files_counter], "w");
	core3trace = get_file(argv[files_counter], "w");
	bustrace = get_file(argv[files_counter], "w");
	dsram0 = get_file(argv[files_counter], "w");
	dsram1 = get_file(argv[files_counter], "w");
	dsram2 = get_file(argv[files_counter], "w");
	dsram3 = get_file(argv[files_counter], "w");
	tsram0 = get_file(argv[files_counter], "w");
	tsram1 = get_file(argv[files_counter], "w");
	tsram2 = get_file(argv[files_counter], "w");
	tsram3 = get_file(argv[files_counter], "w");
	stats0 = get_file(argv[files_counter], "w");
	stats1 = get_file(argv[files_counter], "w");
	stats2 = get_file(argv[files_counter], "w");
	stats3 = get_file(argv[files_counter], "w");

}

