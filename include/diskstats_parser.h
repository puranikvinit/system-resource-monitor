#ifndef DISKSTATS_PARSER
#define DISKSTATS_PARSER

#include <stdlib.h>

typedef struct diskstats_parser_struct {
    char* device_major_id;
    char* device_minor_id;

    char* device_name;

    unsigned long success_completed_reads;
    unsigned long merged_reads;
    unsigned long sectors_read;
    // Total time spent by disk in reads (ms)
    unsigned long total_read_time;

    unsigned long success_completed_writes;
    unsigned long merged_writes;
    unsigned long sectors_written;
    // Total time spent by disk in writes (ms)
    unsigned long total_write_time;

    unsigned long io_in_progress;
    // Total time spent by disk in I/Os (ms)
    unsigned long total_io_time;
    /*  Total weighted time spent by disk in I/Os (ms)
    *
    *   This field is incremented at each I/O start, I/O completion, I/O
    *   merge, or read of these stats by the number of I/Os in progress
    *   times the number of milliseconds spent doing I/O since the
    *   last update of this field.
    */
    unsigned long weighted_total_io_time;

    // fields appended from Linux kernel v4.18 for discard tracking
    unsigned long success_completed_discards;
    unsigned long merged_discards;
    unsigned long sectors_discarded;
    // Total time spent by disk in discards (ms)
    unsigned long total_discard_time;

    // fields appended from Linux kernel v5.5 for flush requests
    unsigned long success_completed_flushes;
    // Total time spent by disk in flushes (ms)
    unsigned long total_flush_time;

    diskstats_parser_struct* next_device;
} diskstats_parser_struct;

typedef struct diskstats_parser_iterator_struct {
    diskstats_parser_struct* head_node;
    diskstats_parser_struct* current_node;
} diskstats_parser_iterator;


// Member APIs

diskstats_parser_iterator* parse_all_diskstats();

void _populate_diskstats_parser_struct(
    char* read_buffer,
    char* device_major_id,
    char* device_minor_id,
    char* device_name,
    char* success_completed_reads,
    char* merged_reads,
    char* sectors_read,
    char* total_read_time,
    char* success_completed_writes,
    char* merged_writes,
    char* sectors_written,
    char* total_write_time,
    char* io_in_progress,
    char* total_io_time,
    char* weighted_total_io_time,
    char* success_completed_discards,
    char* merged_discards,
    char* sectors_discarded,
    char* total_discard_time,
    char* success_completed_flushes,
    char* total_flush_time
);

void print_all_diskstats(
    diskstats_parser_struct* head_node
);

void free_diskstats_alloc(
    diskstats_parser_iterator* diskstats_iterator
);

diskstats_parser_struct* get_next_device(
    // The entire iterator needs to be passed so as to update the iterator's current node after
    // getting the next node in the map list.
    diskstats_parser_iterator* diskstats_iterator
);

#endif