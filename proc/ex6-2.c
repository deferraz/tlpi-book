#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

void
testFunc(void)
{
	if (setjmp(env) == 0) {
		printf("Calling setjmp\n");

	}
	else {

		printf("Jumped back\n");

	}
}

int
main(int argc, char *argv[])
{
	printf("main()\n");
	testFunc();
	longjmp(env, 1);


	exit(EXIT_SUCCESS);
}
