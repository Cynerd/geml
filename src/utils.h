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
#include <stdlib.h>

#ifndef _UTILS_H_
#define _UTILS_H_

enum Verbosity {
	V_DEVEL = -2,
	V_DEBUG,
	V_INFO, // = 0
	V_WARN,
	V_ERROR,
	V_DIE
};

// Sets verbosity level
void verbosity_set(enum Verbosity level);
void verbosity_inc(void);
void verbosity_dec(void);

// Prints given message if it isn't lower than chosen verbosity level
void print_message(const char *file, const int line, enum Verbosity level, const char *msg, ...);
#define _PRINT_MESSAGE(LEVEL, ...) print_message(__FILE__, __LINE__, LEVEL, __VA_ARGS__)
#define DIE(...) do { _PRINT_MESSAGE(V_DIE, __VA_ARGS__); abort(); } while(0)
#define ERROR(...) _PRINT_MESSAGE(V_ERROR, __VA_ARGS__)
#define WARN(...) _PRINT_MESSAGE(V_WARN, __VA_ARGS__)
#define INFO(...) _PRINT_MESSAGE(V_INFO, __VA_ARGS__)
#define DBG(...) _PRINT_MESSAGE(V_DEBUG, __VA_ARGS__)
#ifdef DEBUG
#define DVL(...) _PRINT_MESSAGE(V_DEVEL, __VA_ARGS__)
#else /* DEBUG */
#define DEVEL(...)
#endif /* DEBUG */

#define ASSERT(CHECK) do { if (!(CHECK)) { printf("Assertion failed on %s:%d\n", __FILE__, __LINE__); } } while(0)

// Secure versions of malloc and calloc. They just wraps malloc and calloc and
// checks return value. Returned NULL causes program to die.
#define smalloc(SIZE) smalloc_internal(__FILE__, __LINE__, SIZE)
#define scalloc(NMEMB, SIZE) scalloc_internal(__FILE__, __LINE__, NMEMB, SIZE)
#define srealloc(PTR, SIZE) srealloc_internal(__FILE__, __LINE__, PTR, SIZE)
#define error_out_of_memmory error_out_of_memmory_internal(__FILE__, __LINE__)
void *smalloc_internal(const char *file, const int line, size_t size);
void *scalloc_internal(const char *file, const int line, size_t nmemb, size_t size);
void *srealloc_internal(const char *file, const int line, void *ptr, size_t size);
void error_out_of_memmory_internal(const char *file, const int line);

#endif /* _UTILS_H_ */
