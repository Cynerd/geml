/* geml - General extendable macro language
 *   args_parser.c Program arguments parser
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
#include <unistd.h>
#include <getopt.h>
#include "args_parser.h"
#include "utils.h"
#include "io.h"

const char *help_text = 
	"Usage: geml [OPTIONS]... INPUT_FILE\n"
	"  General extendable macro language processing tool.\n"
	"\n"
	"Options:\n"
	"  -v, --verbose\n"
	"    Increases vebosity of output.\n"
	"  -q, --quiet\n"
	"    Dcreases verbosity of output.\n"
	"  -o, --output OUTPUT_FILE\n"
	"    Sets file in which output is going to be stored\n"
	"  -h, --help\n"
	"    Prints this text.\n"
	"  --version\n"
	"    Prints geml version\n"
	"\n"
	"Report bugs to: <" GEML_CONTACT ">\n"
	;

const char *version_text = "geml " GEML_VERSION "\n";

enum ARGS_ENUM {
	ARGS_ENUM_VERSION = 260
};

const struct option long_options[] = {
	{"verbose", no_argument, NULL, 'v'},
	{"quiet", no_argument, NULL, 'q'},
	{"output", required_argument, NULL, 'o'},
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, ARGS_ENUM_VERSION}
};

bool args_parse(int argc, char *argv[]) {
	char *output = NULL;

	int index = 1;
	int c;
	while((c = getopt_long(argc, argv, "vqo:h;", long_options, &index)) != -1) {
		switch (c) {
		case 'v': // verbose
			verbosity_inc();
			break;
		case 'q': // quiet
			verbosity_dec();
			break;
		case 'o': // output
			output = optarg;
			break;
		case 'h': // help
			fputs(help_text, stderr);
			return true;
		case ARGS_ENUM_VERSION:
			fputs(version_text, stderr);
			return true;
		default:
			abort();
		}
	}

	if (optind < argc) {
		if (!set_input(argv[optind]))
			abort();
		if ((argc - optind) > 1)
			WARN("Only first input file is accepted, rest is dropped.");
	}
	if (output != NULL && !set_output(output))
		abort();

	return false;
}
