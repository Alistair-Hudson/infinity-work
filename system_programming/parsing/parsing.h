#ifndef __OL85_PARSING_H__
#define __OL85_PARSING_H__

/*******************************************************************************
                                 * API FOR PARSING
                                 * version 23.06.2020.0
 ******************************************************************************/

#include <ext2fs/ext2fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/statfs.h>
#include <string.h>

void FindFirstGroupDecriptor(int fd,struct ext2_group_desc* ret_group);

// Remember that root directory is in 1’st group’s node number 2:
void read_inode(int fd, 
                const struct ext2_group_desc *group_descriptor,
                int inode_number, 
                struct  ext2_inode *ret_inode);

// Given a path of a directory, find its corresponding inode:
void search_directory_by_path(int fd, 
                            const struct ext2_group_desc *group_descriptor, 
                            const struct ext2_inode *inode,
                            const char *path,
                            struct ext2_inode *ret_inode);

// Given inode of a directory, find inode to the requested file name:
void find_filein_dir(int fd, 
                    const struct ext2_group_desc *group_descriptor, 
                    const struct ext2_inode *inode,
                    const char *file_name_to_search,
                    struct ext2_inode *ret_inode);

// Given an inode of a file, print the file:
void print_file(int fd, 
                struct ext2_inode *inode, 
                int level /*= 0/*recursive call support*/);


#endif /*__OL85_PARSING_H__ */
