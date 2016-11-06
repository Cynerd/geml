/* geml - General extendable macro language
 *   utils.h Various utility functions
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
#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

static enum Verbosity verbosity = V_INFO;

void verbosity_set(enum Verbosity level) {
	if (level > V_DIE)
		level = V_DIE;
	else if (level < V_DEVEL)
		level = V_DEVEL;
	verbosity = level;
}

void verbosity_inc(void) {
	verbosity--;
	verbosity_set(verbosity);
}

void verbosity_dec(void) {
	verbosity++;
	verbosity_set(verbosity);
}

// TODO colors if terminal supports them
static const char *v_name[] = {
	"DEVEL",
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"DIE"
};

void print_message(const char *file, const int line, enum Verbosity level, const char *msg, ...) {
	ASSERT(level <= V_DIE && level >= V_DEVEL);
	if (level < verbosity)
		return;
	fputs(v_name[level + 2], stderr);
	if (verbosity <= V_DEBUG)
		fprintf(stderr, ":%s:%d", file, line);
	fputs(":", stderr);
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	fputs("\n", stderr);
}
