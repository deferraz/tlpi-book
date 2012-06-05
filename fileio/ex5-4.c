#include <fcntl.h>
#include <errno.h>

int
dup_new(int oldfd)
{
	int newfd;
	newfd = fcntl(oldfd, F_DUPFD, oldfd);
	return newfd;
}


int
dup2_new(int oldfd, int newfd)
{
	if (fcntl(oldfd, F_GETFL) <= 0)
	{
		errno = EBADF;
		return -1;
	}
	if (oldfd == newfd)
		return newfd;
	if (fcntl(newfd, F_GETFL) > 0)
		close(newfd);
	newfd = fcntl(oldfd, F_DUPFD, newfd);
	return newfd;
}
