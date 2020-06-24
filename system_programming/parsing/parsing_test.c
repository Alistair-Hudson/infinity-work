#include <stdlib.h>
#include <stdio.h>


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
    
    struct ext2_group_desc group;
    struct ext2_inode inode;
    struct ext2_inode inode2;
    char* path;

    int fd = open("/dev/ram0", O_RDONLY);
    if (-1 == fd)
    {
        perror("failed to open:");
        return 1;
    }
    
    FindFirstGroupDecriptor(fd, &group);
    read_inode(fd, 
                &group,
                11, 
                &inode);
    search_directory_by_path(fd, 
                            &group, 
                            &inode,
                            path,
                            &inode2);
    //printf("%d\n", group.bg_used_dirs_count);
    
    return 0;
}

