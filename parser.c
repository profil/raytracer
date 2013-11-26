#include <stdio.h>

struct scene parse(char *filename) {
	FILE *fd;
	struct scene sc;
	fd = fopen(filename, "r");
	if(fd == NULL) {
		/* something bad happened */
		fprintf(stderr, "Could not open file: '%s'\n", filename);
		/* return something */
	}

	/* parsa filen på nåt sätt som inte är bestämt ännu.. */
}
