#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

extern int optind, optopt;
extern char *optarg;

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')

static void
usageError(char *progName, char *msg, int opt)
{
	if (msg != NULL && opt != 0)
		fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
	fprintf(stderr, "Usage: %s [-a] file\n", progName);
}


int
main(int argc, char *argv[])
{
	int opt, fd, numRead, teeFd;
	char buf[BUF_SIZE];
	char *appendFile;

	appendFile = NULL;
	

	while ((opt = getopt(argc, argv, "+:a")) != -1) {
		switch (opt) {
		case 'a': appendFile = optarg; break;
		case '?': usageError(argv[0], "Unrecognized option", optopt);
		}
	}
	if (optind > argc) {
		fprintf(stderr, "File not specified\n");
		exit(EXIT_FAILURE);
	}

	if (appendFile != NULL) {
		teeFd = open(appendFile, O_RDWR | O_CREAT | 
			O_TRUNC, S_IRUSR | S_IWUSR);
	} else {
		teeFd = open(argv[optind], O_RDWR | O_CREAT | 
			O_APPEND, S_IRUSR | S_IWUSR);
	}

	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)  {
		if (write(STDOUT_FILENO, buf, numRead) != numRead)
			fatal("Couldnt write whole buffer");
		if (write(teeFd, buf, numRead) != numRead)
			fatal("Couldnt write whole buffer");
		fflush(stdout);
	}

	exit(EXIT_SUCCESS);
}
