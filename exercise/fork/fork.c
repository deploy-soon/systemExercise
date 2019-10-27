#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pid_t Fork(void){
	pid_t pid;
	if ((pid = fork()) < 0){
		printf("Fork error\n");
	}
	return pid;
}

int main() {
	pid_t pid;
	int x = 1;

	pid = Fork();
	if ( pid == 0) {
		printf("child : x=%d\n", x++);
		exit(0);
	}
	printf("parent: x=%d\n", --x);
	exit(0);
}
