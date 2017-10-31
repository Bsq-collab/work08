#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<time.h>

const char *FILE_PATH = "stat.c";//"original_file_name


void print_errno() { 
    int err = errno;
    printf("You done goofed\n");
    printf("error: %s\n", strerror(err));
    exit(0);
}

 
char *readable_file_size(char *buffer, off_t bytes) {
    if (bytes > 1024*1024*1024) {
        sprintf(buffer, "%f gB", (float)bytes/(1024*1024*1024));
        return buffer;
    }
    if (bytes > 1024*1024) {
        sprintf(buffer, "%f mB", (float)bytes/(1024*1024));
        return buffer;
    }
    if (bytes > 1024) {
        sprintf(buffer, "%f kB", (float)bytes/1024);
        return buffer;
    }
    sprintf(buffer, "%d Bytes", bytes);
    return buffer;
}

// Get the nth bit of an integer (returns 1 or 0)
int get_nth_bit(int number, int bit) {
    // Remove all bits after first bit
    return (number >> bit) & 1;
}

char *readable_permissions(char *buffer, int permissions) {
    int i;
    char a_method; // access method (read, write or execute)
    buffer[0] = '-'; // we're dealing with files here.
    for(i = 0; i < 9; i++) {
        if (i % 3 == 0) a_method = 'r';
        else if (i % 3 == 1) a_method = 'w';
        else if (i % 3 == 2) a_method = 'x';

        if (get_nth_bit(permissions, 8 - i)) {
            buffer[i+1] = a_method;
        } else {
            buffer[i+1] = '-';
        }
    }
    buffer[10] = 0;
    return buffer;
}


int main() {

    // Open the file to update its last-read time
    /*
    int fd = open(FILE_PATH, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        print_errno();
    }
    //write(fd, "wat\n", 4);
    close(fd);
    */
    struct stat stats;
    if (stat(FILE_PATH, &stats)) {
        print_errno();
    }
    printf("Got stats from file %s!\n", FILE_PATH);
    printf("Time Accessed: %s\n", ctime( &stats.st_atime ));

    char *size_buffer[50];
    printf("File Size: %s\n", readable_file_size(size_buffer, stats.st_size));

    char *perm_buffer[11];
    printf("Permissions: %s\n", readable_permissions(perm_buffer, stats.st_mode));

    return 0;
}

