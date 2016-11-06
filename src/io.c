/* geml - General extendable macro language
 *   io.c Hadndles input and output for parser
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
#include "io.h"

FILE *outf;
const char *outf_name;

FILE *inf;
const char *inf_name;

void io_init(void) {
	outf = stdout;
	outf_name = "stdout";
	inf = stdin;
	inf_name = "stdin";
}

bool set_output(const char *file) {
    FILE *f;
    f = fopen(file, "w");
    if (f == NULL) {
		ERROR("Output file \"%s\" couldn't be opened: %s", file,
				strerror(errno));
		return false;
	}
    if (outf != stdout)
        fclose(outf);
    outf = f;
    outf_name = file;
	return true;
}

bool set_input(const char *file) {
    FILE *f;
    f = fopen(file, "r");
    if (f == NULL) {
		ERROR("Input file \"%s\" couldn't be opened: %s", file,
				strerror(errno));
		return false;
	}
    if (inf != stdin)
        fclose(inf);
    inf = f;
    inf_name = file;
	return true;
}
