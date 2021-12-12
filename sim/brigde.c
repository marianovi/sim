#include "bridge.h"

#pragma warning(disable:4996)

// First we need to write al bus and cache functions
int request(Cache* cache, int opcode, int address, int rd_value, int coreID, int cycle, bool* isStall) {
	int result = 0;
	int stall_counter = 0;
	bool tagConflict = false;
	if ((opcode != LW) && !(opcode == SW)) {
		printf("Error_Bridge _3 : Trying to access cache with invalid instruction");
		return 1;
	}
	current_request.coreID = coreID;
	current_request.opcode = opcode;
	current_request.rd = rd_value;
	current_request.address = translate_address(address);
	current_request.tag = translate_tag(current_request.address);
	current_request.index = translate_index(current_request.address);
	current_request.msi_transaction = translate_mesi_transaction(opcode);
	current_request.msi_state = get_mesi_state(cache, current_request.index, current_request.tag, &tagConflict);


	int stall = cycles_to_wait(current_request, coreID);

	if (stall != 0) {
		*isStall = true;
		if (check_if_bus_free()) {
			update_stall_list(coreID, false);
			first_bus_trace(current_request, coreID, cycle);
			main_bridge->stalls[coreID][1] += stall;
			return 0;
		}
		else {
			if (main_bridge->stalls[coreID][0] == 1) {
				main_bridge->stalls[coreID][1]--;
				if (main_bridge->stalls[coreID][1] != 0) {
					return 0;
				}
			}
			else {
				main_bridge->stalls[coreID][1] = -1;
				return 0;
			}
		}
	}

	result = handle_request(cache, current_request, coreID, cycle, &stall_counter, tagConflict);
	if (main_bridge->stalls[coreID][0] == 1) {
		update_stall_list(coreID, true);
	}

	*isStall = false;

	if (!strcmp(current_request.msi_transaction, READ)) {
		if (stall_counter == 0) {
			cache->read_hit++;
		}
		else {
			cache->read_miss++;
			cache->mem_stall += stall_counter;
		}
	}
	else {
		if (stall_counter == 0) {
			cache->write_hit++;
		}
		else {
			cache->write_miss++;
			cache->mem_stall += stall_counter;
		}
	}
	return result;

}