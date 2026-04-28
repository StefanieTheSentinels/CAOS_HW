#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#define PAGE_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 4) {
        const char msg[] = "Usage: program file I N\n";
        write(2, msg, sizeof(msg) - 1);
        return 1;
    }

    const char *filename = argv[1];
    long start_line = strtol(argv[2], NULL, 10);
    long lines_to_print = strtol(argv[3], NULL, 10);

    if (start_line <= 0 || lines_to_print <= 0) {
        const char msg[] = "I and N must be positive\n";
        write(2, msg, sizeof(msg) - 1);
        return 1;
    }

    int fd = open(filename, O_RDONLY);
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

    size_t buf_size = PAGE_SIZE;
    if (st.st_size > 0 && st.st_size < PAGE_SIZE) {
        buf_size = st.st_size;
    }

    char *buf = malloc(buf_size);
    if (buf == NULL) {
        close(fd);
        return 1;
    }

    long current_line = 1;
    long printed_lines = 0;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buf, buf_size)) > 0) {
        ssize_t segment_start = 0;

        for (ssize_t i = 0; i < bytes_read; ++i) {
            if (buf[i] == '\n') {
                if (current_line >= start_line &&
                    printed_lines < lines_to_print) {
                    write(1, buf + segment_start, i - segment_start + 1);
                    printed_lines++;
                }

                current_line++;
                segment_start = i + 1;

                if (printed_lines >= lines_to_print) {
                    free(buf);
                    close(fd);
                    return 0;
                }
            }
        }

        if (current_line >= start_line &&
            printed_lines < lines_to_print &&
            segment_start < bytes_read) {
            write(1, buf + segment_start, bytes_read - segment_start);
        }
    }

    free(buf);
    close(fd);
    return 0;
}