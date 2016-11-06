/* geml - General extendable macro language
 *   io.h Hadndles input and output for parser
 *
 * Copyright (C) 2016 Karel Kočí
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#ifndef _IO_H_
#define _IO_H_
#include "utils.h"

// Call this function as soon as possible after program start before outf  or inf
// are used.
void io_init(void);

// Current output file is closed and opens specified file. When NULL is passed,
// current file is closed and stdout is used.
bool set_output(const char *file) __attribute__ ((nonnull));

extern FILE *outf;
extern const char *outf_name;

// Curent input file is closed and opens specified file. When NULL is passed,
// current file is closed and stdin is used.
bool set_input(const char *file) __attribute__ ((nonnull));

extern FILE *inf;
extern const char *inf_name;

#endif /* _IO_H_ */
