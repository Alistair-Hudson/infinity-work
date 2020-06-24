/******************************************************************************
 *	Title:		Parsing
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	23.06.2020.0
 ******************************************************************************/

#include "parsing.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define BASE_OFFSET             (1024)
#define BLOCK_OFFSET(block)     (BASE_OFFSET+((block)-1)*block_size)

/******TYPEDEFS******/

/******GLOBAL VARIABLES******/
size_t block_size = 0;
/******INTERNAL FUNCTIONS******/

/******FUNCTIONS******/

void FindFirstGroupDecriptor(int fd, struct ext2_group_desc* ret_group)
{
    struct ext2_super_block super;

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

    block_size = 1024 << super.s_log_block_size;

    lseek(fd, BASE_OFFSET+block_size, SEEK_SET);
    read(fd, ret_group, sizeof(struct ext2_group_desc));

}

// Remember that root directory is in 1’st group’s node number 2:
void read_inode(int fd, 
                const struct ext2_group_desc *group_descriptor,
                int inode_number, 
                struct  ext2_inode *ret_inode)
{
	lseek(fd, 
            BLOCK_OFFSET(group_descriptor->bg_inode_table)+(inode_number-1)*sizeof(struct ext2_inode), 
	        SEEK_SET);
	read(fd, ret_inode, sizeof(struct ext2_inode));
}

// Given a path of a directory, find its corresponding inode:
void search_directory_by_path(int fd, 
                            const struct ext2_group_desc *group_descriptor, 
                            const struct ext2_inode *inode,
                            const char *path,
                            struct ext2_inode *ret_inode)
{

    struct ext2_dir_entry_2* entry;
    void* block;
    size_t size = 0;
    char file_name[EXT2_NAME_LEN+1];

    if (!S_ISDIR(inode->i_mode))
    {
        printf("not a directory\n");
        return;
    }

    if ((block = malloc(block_size)) == NULL) 
    {
        perror("Memory error:");
        close(fd);
        exit(1);
    }

    lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
    read(fd, block, block_size);
    
    entry = (struct ext2_dir_entry_2* )block;
    printf("inode size = %d\n", inode->i_size);

    while((size < inode->i_size) && entry->inode) 
    {
        char file_name[EXT2_NAME_LEN+1];
        memcpy(file_name, entry->name, entry->name_len);
        file_name[entry->name_len] = 0;
        printf("%10u %s\n", entry->inode, file_name);
        entry = (void*) entry + entry->rec_len;
        size += entry->rec_len;
    }
    free(block);
}

// Given inode of a directory, find inode to the requested file name:
void find_filein_dir(int fd, 
                    const struct ext2_group_desc *group_descriptor, 
                    const struct ext2_inode *inode,
                    const char *file_name_to_search,
                    struct ext2_inode *ret_inode)
{

}

// Given an inode of a file, print the file:
void print_file(int fd, 
                struct ext2_inode *inode, 
                int level/* = 0/*recursive call support*/)
{
    
}
/*
static void read_dir(int fd, const struct ext2_inode *inode, const struct ext2_group_desc *group)
{
	void *block;

	if (S_ISDIR(inode->i_mode)) {
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk/

		entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory /
                /* Notice that the list may be terminated with a NULL
                   entry (entry->inode == NULL)/
		

		free(block);
	}
} /* read_dir() */