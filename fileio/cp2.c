#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define MAX_READ 20


int
main(int argc, char *argv[])
{
	int numRead, numWritten, srcFd, dstFd;
	char buffer[MAX_READ];


	if (argc < 3) {
		fprintf(stderr, "Usage %s source-file dst-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	srcFd = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	dstFd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	
	while ((numRead = read(srcFd, buffer, MAX_READ)) > 0) {
		printf("numRead %d\n", numRead);
		numWritten = write(dstFd, buffer, numRead);
		if (numWritten == -1)
			errExit("write");
	}

	exit(EXIT_SUCCESS);
}
