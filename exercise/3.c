#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int n = argc > 1 ? atoi(argv[1]) : 10;
	char str[16];
	snprintf(str, sizeof(str), "%d", 2*n);
	
	pid_t pid = fork();
	if (pid == 0) {
		char *child_argv[] = {"./producer", str, NULL};
		execve("./producer", child_argv, NULL);
		perror("Cannot execute child.");
	} else if (pid > 0) {
		int status, exitcode;
		pid_t retpid;
		if ( (retpid = wait(&status)) > 0){
			exitcode = WEXITSTATUS(status);
			printf("Child terminated with exit code %d.\n", exitcode);
		} else {
			perror("Cannot wait for child.");
		}
	}
	return 0;
}
