#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int puts(const char *s) {
	int (*putsp)(const char *s);
	char *error;

	putsp = dlsym(RTLD_NEXT, "puts");
	if((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}

	int status = putsp("you win!");
	return status;
}
