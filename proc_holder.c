/* $Id: proc_holder.c,v 1.3 2023/03/23 08:12:28 leavens Exp $ */
#include "proc_holder.h"
#include "machine_types.h"

// The next address to use for a procedure's start.
// (This is initialized to 1 to save space for the initial jump around
// the code for the procedures, which goes to the start of
// the program's statement.)
static address next_addr = 1;

// The sequence of all the procedure code registered
static code_seq proc_code;

// initialize the proc_holder data structures
void proc_holder_initialize()
{
    proc_code = code_seq_empty();
}

// Register the procedure with the given code;
// this returns the address in the code array
// that can be used to call the procedure
address proc_holder_register(code_seq pcode)
{
    unsigned int plen = code_seq_size(pcode);
    proc_code = code_seq_concat(proc_code, pcode);
    address start_addr = next_addr;
    next_addr += plen;
    return start_addr;
}

// Return the code for all registered procedures
// with an initial jump around all that code
code_seq proc_holder_code_for_all()
{
    if (!code_seq_is_empty(proc_code)) {
	// fix up any labels in CAL instructions (needed for recursion)
	code_seq_fix_labels(proc_code);
	unsigned int total_length = code_seq_size(proc_code);
	address start_of_main = 1 + total_length;
	code_seq initial_jump = code_seq_singleton(code_jmp(start_of_main));
	return code_seq_concat(initial_jump, proc_code);
    } else {
	return code_seq_empty();
    }
}
