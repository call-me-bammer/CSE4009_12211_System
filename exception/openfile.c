#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    char* pathname = "asdf";
    int fd = open(pathname, O_RDWR | O_CREAT, 0666);
    printf("file opened!\n");

    close(fd);
    printf("file closed...\n");

    return 0;
}