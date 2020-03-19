/**
 * Created by J.R(jujin1324@daum.net)
 * Created Date : 2020/03/19
*/

#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>

static void child() {
    char *args[] = {"/bin/echo", "hello", NULL};
    printf("I'm child! my pid is %d.\n", getpid());
    fflush(stdout);
    execve("/bin/echo", args, NULL);
    /* never progressed this below */
    err(EXIT_FAILURE, "exec() failed");
}

static void parent(pid_t child_pid) {
    printf("I'm parent! my pid is %d and the pid of my child is %d.\n", getpid(), child_pid);
    exit(EXIT_SUCCESS);
}

int main() {
    pid_t ret;
    ret = fork();
    if (ret == -1)
        err(EXIT_FAILURE, "fork() failed");
    if (ret == 0) {
        /* child process came here because fork() returns 0 for child process */
        child();
    } else {
        /* parent process cam here because fork() returns the pid of newly created child process (> 1) */
        parent(ret);
    }
    /* shouldn't reach here */
    err(EXIT_FAILURE, "shouldn't reach here");
}