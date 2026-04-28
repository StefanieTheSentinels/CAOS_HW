#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#define PAGE_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 2) {
        const char msg[] = "Usage: program file\n";
        write(2, msg, sizeof(msg) - 1);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return 1;
    }

    off_t pos = st.st_size / 2;

    if (lseek(fd, pos, SEEK_SET) < 0) {
        perror("lseek");
        close(fd);
        return 1;
    }

    char buf[PAGE_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        for (ssize_t i = 0; i < bytes_read; ++i) {
            write(1, buf + i, 1);

            if (buf[i] == '\n') {
                close(fd);
                return 0;
            }
        }
    }

    close(fd);
    return 0;
}