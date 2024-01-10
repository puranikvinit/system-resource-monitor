#ifndef MEM_MAP_PARSER
#define MEM_MAP_PARSER

#include <strings.h>
#include <limits.h>

// Line contains other columns, whose number of characters sums up to 100 at max
#define MAX_LINE_LENGTH (PATH_MAX + 100)


typedef struct mem_map_parser_struct {
    // void pointer rather than storing as a string to calculate the length of the area
    void* start_addr;
    void* end_arr;
    unsigned long area_length;

    // The types of Permissions enforced on a Memory Map are as follows:
    // r = read
    // w = write
    // x = execute
    // s = shared with other processes
    // p = private (after copy-on-write)
    char permissions[5];
    unsigned short read;
    unsigned short write;
    unsigned short execute;
    unsigned short shared;
    unsigned short private_area;

    unsigned long offset;

    char* device_major_id;
    char* device_minor_id;

    int inode_number;

    char path_to_file[PATH_MAX];

    struct mem_map_parser_struct* next_map;
} mem_map_parser_struct;

typedef struct mem_map_iterator_struct{
    mem_map_parser_struct* head_node;
    mem_map_parser_struct* current_node;
} mem_map_iterator;


// Member APIs

mem_map_iterator* parse_mem_map(
    int pid
);

void _populate_mem_map_struct(
    char* read_buffer,
    char* start_addr,
    char* end_addr,
    char* permissions,
    char* offset,
    char* device_id,
    char* inode_number,
    char* path_to_file
);

void print_mem_map(
    mem_map_parser_struct* head_node
);

void free_mem_map_alloc(
    mem_map_iterator* map_iterator
);

mem_map_parser_struct* get_next_mem_map(
    // The entire iterator needs to be passed so as to update the iterator's current node after
    // getting the next node in the map list.
    mem_map_iterator* map_iterator
);

#endif