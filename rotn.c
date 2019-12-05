#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHAUPPERA 65
#define ALPHAUPPERZ 90
#define ALPHALOWERA 97
#define ALPHALOWERZ 122

static int verbose = 0;

void usage(void) {
	fprintf(stderr, "Usage: ./rotn -r <rotamount> -i <(optional)input> -v (for verbose)\n");
	exit(1);
}

void rot_string(char *str, int amount);

int main(int argc, char **argv) {
	if (argc < 3) {
		usage();
	}

	int ch;
	char *inv;
	char *input = NULL;
	int rot = -1;
	/* Parse flags and arguments using getopt */
	while ((ch = getopt(argc, argv, ":r:i:v")) != -1) {
		switch(ch) {
		case 'r':
			/* Make sure the rotation amount is a valid integer */
			rot = strtol(optarg, &inv, 10);
			if (*inv || rot < 1) {
				fprintf(stderr, "Invalid rotation amount: Enter positive integer\n");
				usage();
			}
			break;
		case 'i':
			input = optarg;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			fprintf(stderr, "Unknown tag\n");
			usage();
		}
	}

	if (rot == -1) {
		fprintf(stderr, "No rotamount set\n");
		usage();
	}

	if (input) {
		rot_string(input, rot);
	} else {
		char *lineptr = NULL;
		size_t linelen = 0;
		ssize_t nread = 0;

		while ((nread = getline(&lineptr, &linelen, stdin)) > 0) {
			lineptr[nread-1] = '\0';
			rot_string(lineptr, rot);

			free(lineptr); lineptr = NULL;
			linelen = 0;
		}

		free(lineptr);
	}

	return 0;
}

void rot_string(char *str, int amount) {
	char *output = (char*) malloc(strlen(str) + 1);

	for (size_t i = 0; i < strlen(str); i++) {
		if (islower(str[i])) {
			int ch_idx = str[i] - ALPHALOWERA;
			ch_idx = (ch_idx + amount) % 26;
			output[i] = ALPHALOWERA + ch_idx;
		} else if (isupper(str[i])) {
			int ch_idx = str[i] - ALPHAUPPERA;
			ch_idx = (ch_idx + amount) % 26;
			output[i] = ALPHAUPPERA + ch_idx;
		} else {
			output[i] = str[i];
		}
	}

	if (verbose) {
		printf("-------------------------INPUT-------------------------\n");
		printf("%s\n", str);
		printf("-------------------------OUTPUT------------------------\n");
	}

	printf("%s\n", output);
	free(output);
}
