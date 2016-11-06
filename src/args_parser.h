/* geml - General extendable macro language
 *   args_parser.h Program arguments parser
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
#include <stdbool.h>

#ifndef _ARGS_PARSE_
#define _ARGS_PARSE_

/* Parse arguments from command line
 * Arguments are as arguments as they are in main function
 * Returns true if program should exit
 */
bool args_parse(int argc, char *argv[]);

#endif /* _ARGS_PARSE_ */
