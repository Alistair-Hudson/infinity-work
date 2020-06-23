#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "parsing.h"

struct HEADER
{
        int Num_Files;
        int File_Start[100];
        int File_length[100];
};

#define BASE_OFFSET (1024)

int main()
{
    struct ext2_super_block super;
    struct ext2_group_desc group;

    int fd = open("/dev/ram0", O_RDONLY);
    
    if (-1 == fd)
    {
        perror("failed to open:");
        return 1;
    }
    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

    size_t block_size = 1024 << super.s_log_block_size;

    lseek(fd, BASE_OFFSET+block_size, SEEK_SET);
    read(fd, &group, sizeof(group));
    
    printf("%d\n", group.bg_used_dirs_count);
    
    return 0;
}

