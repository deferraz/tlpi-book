#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fd, new_fd, new2_fd;
	int flags;

	fd = open(argv[1], O_RDONLY);

	new_fd = dup_new(fd);

	new2_fd = dup2_new(fd, 10);

	lseek(fd, 10, SEEK_SET);

	flags = fcntl(fd, F_GETFL);
	flags |= O_APPEND | O_RDWR;
	fcntl(fd, F_SETFL, flags);

	printf("From original fd %d offset: %lld\n", fd, (long long)lseek(fd, 0, SEEK_CUR));
	printf("From original fd %d flags: %ld\n", fd, (long)fcntl(fd, F_GETFL));
	printf("From Dupped fd %d offset: %lld\n", new_fd, (long long)lseek(new_fd, 0, SEEK_CUR));
	printf("From Dupped fd %d flags: %ld\n", new_fd, (long)fcntl(new_fd, F_GETFL));

	lseek(fd, 20, SEEK_SET);

	printf("From original fd %d offset: %lld\n", fd, (long long)lseek(fd, 0, SEEK_CUR));
	printf("From original fd %d flags: %ld\n", fd, (long)fcntl(fd, F_GETFL));
	printf("From Dupped fd %d offset: %lld\n", new2_fd, (long long)lseek(new2_fd, 0, SEEK_CUR));
	printf("From Dupped fd %d flags: %ld\n", new2_fd, (long)fcntl(new2_fd, F_GETFL));

	return(EXIT_SUCCESS);
}
