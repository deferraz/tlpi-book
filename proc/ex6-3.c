#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int
new_unsetenv(const char *name)
{
	extern char **environ;
	char **ep, **sp;
	size_t len;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
		errno = EINVAL;
		return -1;
	}

	len = strlen(name);

	for (ep = environ; *ep != NULL ; ) {
		if (strncmp(*ep, name, len) == 0 && (*ep)[len] == '=') {
			for (sp = ep; *sp != NULL; sp++) {
				*sp = *(sp + 1);	
			}
		}
		else {
			ep++;
		}
	}
	return 0;

}

int 
new_setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
		value == NULL) {
		errno = EINVAL;
		return -1;
	}
	char *tempname = NULL;
	tempname = getenv(name);
	char *newenv;
	newenv = malloc(strlen(name) + strlen(value) + 2);
	if (newenv == NULL)
		return -1;
	strncpy(newenv, name, strlen(name));
	strncat(newenv, "=", strlen("="));
	strncat(newenv, value, strlen(value));
	if (tempname != NULL) {
		if (overwrite == 1) {
			return putenv(newenv);
		}
		else {
			return -1;
		}
	}
	else {
		return putenv(newenv);
	}
}


int
main(int argc, char *argv[]) 
{
	char *name = "FOO";
	char *value = "BAR";	
	char *value2 = "PLANK";

	printf("new_setenv with overwrite = 0\n");
	new_setenv(name, value, 0);
	printf("Result of getenv(%s) = %s\n", name, getenv(name));

	printf("new_setenv with overwrite = 1\n");
	new_setenv(name, value2, 1);
	printf("Result of getenv(%s) = %s\n", name, getenv(name));

	printf("running new_unsetenv of FOO\n");
	new_unsetenv("FOO");
	if (getenv("FOO") == NULL) {
		printf("FOO does not exists anymore\n");
	} else {
		printf("FOO still exists\n");
	}





	exit(EXIT_SUCCESS);
}
