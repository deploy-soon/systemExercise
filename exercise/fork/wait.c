#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

pid_t Fork(void){
	pid_t pid;
	if ((pid = fork()) < 0){
		printf("Fork error\n");
	}
	return pid;
}

int main() {
	int status, i;
	pid_t pid;
	int N = 20;

	for(i = 0; i < N; i++){
		if ((pid = Fork()) == 0){
			exit(100+i);
		}
	}

	while((pid=waitpid(-1, &status, 0)) > 0) {
		if(WIFEXITED(status)){
			printf("child %d terminated normally with exit status=%d\n",
			       pid, WEXITSTATUS(status));
		}
		else {
			printf("child %d terminated abnormally", pid);
		}
	}
	if(errno != ECHILD) {
		puts("waitpid error\n");
	}
	exit(0);
}

