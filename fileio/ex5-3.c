#include <fcntl.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	int fd;
	off_t off;
	
	if (argc == 4 && (strcmp(argv[3], "x") == 0))
		fd = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	else
		fd = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);

	if (fd == -1)
		errExit("open");

	off = atoll(argv[2]);
	if (lseek(fd, off, SEEK_SET) == -1)
		errExit("lseek");

	if (write(fd, "foobar\n", 7) == -1)
		errExit("write");
	exit(EXIT_SUCCESS);
}
