/* $Id: proc_holder.h,v 1.2 2023/03/23 01:38:43 leavens Exp $ */
#ifndef _PROC_HOLDER_H
#define _PROC_HOLDER_H
#include "machine_types.h"
#include "code.h"

// initialize the proc_holder data structures
extern void proc_holder_initialize();

// Register the procedure with the given code;
// this returns the address in the code array
// that can be used to call the procedure
extern address proc_holder_register(code_seq code);

// Return the code for all registered procedures
// with an initial jump around all that code
extern code_seq proc_holder_code_for_all();

#endif
