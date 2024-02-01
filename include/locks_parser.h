#ifndef LOCKS_PARSER
#define LOCKS_PARSER

#include <stdio.h>

typedef enum file_lock_types {
    // older style UNIX file locks, from a ``flock`` syscall
    FLOCK,

    // newer style POSIX file locks, from a ``lockf`` syscall
    POSIX
} file_lock_types;

typedef enum file_lock_levels {
    // does not prevent other processes from data read, only blocks new lock creation
    ADVISORY,

    // block data reads as well
    MANDATORY
} file_lock_levels;

typedef enum access_types {
    READ,
    WRITE
} access_types;

typedef struct lock_parser_struct {
    unsigned int lock_id;

    file_lock_types lock_type;
    file_lock_levels lock_level;
    access_types access_type;

    unsigned long lock_holder_pid;

    char* device_major_id;
    char* device_minor_id;

    unsigned long inode_number;

    char* lock_region_start;
    char* lock_region_end;

    struct lock_parser_struct* next_lock;
} lock_parser_struct;

typedef struct lock_parser_iterator {
    lock_parser_struct* head_node;
    lock_parser_struct* current_node;
} lock_parser_iterator;


// Member APIs

lock_parser_iterator* parse_all_locks();

void _populate_lock_parser_struct(
    char* read_buffer,
    char* lock_id,
    char* lock_type,
    char* lock_level,
    char* access_type,
    char* lock_holder_pid,
    char* device_major_id,
    char* device_minor_id,
    char* inode_number,
    char* lock_region_start,
    char* lock_region_end
);

void print_all_locks(
    lock_parser_struct* head_node
);

void free_locks_alloc(
    lock_parser_iterator* locks_iterator
);

lock_parser_struct* get_next_lock(
    // The entire iterator needs to be passed so as to update the iterator's current node after
    // getting the next node in the map list.
    lock_parser_iterator* locks_iterator
);

#endif