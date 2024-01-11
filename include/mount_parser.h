#ifndef MOUNT_PARSER
#define MOUNT_PARSER

#include <stdlib.h>
#include <limits.h>

typedef struct mount_parser_struct {
    char* filesys_name;
    char* mount_dir;
    
    // All filesystem types are present in `/proc/filesystems` file.
    char* filesys_type;

    // defaults -> Use all the default options
    // ro -> Read-Only filesystem
    // rw -> Read-Write filesystem
    // suid -> Set UID allowed
    // nosuid -> Set UID not allowed
    // noauto -> Auto Mount disabled
    // and many others...
    char* filesys_options;

    // determines if a filesystem needs to be dumped by the ``dump`` command.
    // it contains the frequency (in days) for the dump to take place.
    // if filesys_dump = 0, then filesystem need not be dumped.
    unsigned short filesys_dump;

    // filesys_check_order = 0 -> filesystem doesn't need any checks
    // filesys_check_order = 1, 2, ... -> the order in which the filesystems need to be checked on boot by ``fsck`` command.
    unsigned short filesys_check_order;

    mount_parser_struct* next_mount;
} mount_parser_struct;

typedef struct mount_parser_iterator_struct {
    mount_parser_struct* head_node;
    mount_parser_struct* current_node;
} mount_parser_iterator;


// Member APIs

mount_parser_iterator* parse_all_mounts();

void _populate_mount_parser_struct(
    char* read_buffer,
    char* filesys_name,
    char* mount_dir,
    char* filesys_type,
    char* filesys_options,
    char* filesys_dump,
    char* filesys_check_order
);

void print_all_mounts(
    mount_parser_struct* head_node
);

void free_mount_alloc(
    mount_parser_iterator* mount_iterator
);

mount_parser_struct* get_next_mount(
    // The entire iterator needs to be passed so as to update the iterator's current node after
    // getting the next node in the map list.
    mount_parser_iterator* mount_iterator
);

#endif