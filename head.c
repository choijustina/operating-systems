/*
Justina Choi (jc8415)
Operating Systems - HW1
February 26, 2018
*/

#include "types.h"
#include "user.h"

char buffer[512];

void head (int fd, int maxLines) {
	int n, i, line;
	n = line = 0;

	if (maxLines == 0)
		maxLines = 10; /* set default to 10 */
	
	while ( (n = read(fd, buffer, sizeof(buffer))) > 0) {
		for (i = 0; i < n; i++) {
			if (line >= maxLines)
				exit();
			printf(1, "%c", buffer[i]);
			if (buffer[i] == '\n')
				line++;
		}
	}
}


int main (int argc, char *argv[]) {
/* usage: head -NUM filename */

	int fd;
	int maxLines = 0;

	if (argc <= 1) { 			/* reading from stdin without NUM */
		head(0, 0);
		exit();
	}

	if (argv[1][0] == '-') {		/* reading from stdin/file WITH NUM */
		char *p = argv[1];
		p = p + 1;
		maxLines = atoi(p);
		if (argc == 3)
			fd = open(argv[2], 0);
	
	} else { 				/* reading from file without NUM */
		fd = open(argv[1], 0);
	}

	if (fd < 0) {
		printf(2, "head: cannot open file\n");
		exit();
	}
	head(fd, maxLines);
	exit();
}
