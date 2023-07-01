/* Opinionated wrapper around libdwarf. */

#pragma once

#ifndef _SPRAY_SPRAY_DWARF_H_
#define _SPRAY_SPRAY_DWARF_H_

#include "libdwarf.h"
#include "ptrace.h"

#include <stdbool.h>

/* Initialized debug info. Returns NULL on error. */
Dwarf_Debug dwarf_init(const char *restrict filepath, Dwarf_Error *error);

/* Get the name of the function which the given PC is part of.
   The string that's returned must be free'd be the caller. */
char *get_function_from_pc(Dwarf_Debug dbg, x86_addr pc);

typedef struct {
  const int ln;
  const int cl;
  const char *filepath;
} LineEntry;

/* Returns `ln=-1` if there is no line entry for the PC. */
LineEntry get_line_entry_from_pc(Dwarf_Debug dbg, x86_addr pc);

/* Returns `true` if the line entry can be used.
   Otherwise returns `false` if it signals an error. */
bool line_entry_is_ok(LineEntry line_entry);

/* Get the `low_pc` and `high_pc` attributes for the
   subprogram with the given name. Returns `true` if
   attribute was found. */
bool get_at_low_pc(Dwarf_Debug dbg, const char* fn_name, x86_addr *low_pc_dest);
bool get_at_high_pc(Dwarf_Debug dbg, const char *fn_name, x86_addr *high_pc_dest);

#endif  // _SPRAY_DWARF_H_
