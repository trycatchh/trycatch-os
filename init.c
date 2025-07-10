#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

int main() {
    char buf[BUF_SIZE];

    int fd = open("/dev/console", O_RDWR);
    if (fd < 0) {
        _exit(1);
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2) close(fd);

    while (1) {
        write(1, "avenger-shell> ", 15);
        ssize_t len = read(0, buf, BUF_SIZE - 1);
        if (len <= 0) continue;
        buf[len] = '\0';

        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == 0) {
            char *args[] = {"/bin/sh", "-c", buf, NULL};
            execvp(args[0], args);
            _exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            write(2, "fork failed\n", 12);
        }
    }

    _exit(0);
}