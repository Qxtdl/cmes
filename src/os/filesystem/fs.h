
#pragma once


#include "../../taulib/globals.h"
#include "../../taulib/memorymap.h"
#include "../../taulib/string.h"
#include "../../taulib/stdio.h"

#define HEADER_SIZE 2048
#define DATA_REGION_START HEADER_SIZE + 32
#define DISK_END 65535

#define HEADER_LAST_CREATED_FILE_NODE_ADDRESS_PTR HEADER_SIZE - 4
#define FS_FORMATTED 2047

#define ROOT_NODE 0

#define MAX_FILE_NAME_SIZE 32
#define MAX_FILE_EXTENSION_NAME_SIZE 4

#define FS_BAD 0
#define FS_OK 1

typedef struct {
    char name[MAX_FILE_NAME_SIZE];
    char extension[MAX_FILE_EXTENSION_NAME_SIZE];
    u32 self_addr;
    u16 size;
    u16 data_ptr;
    u32 next_file_node_addr;
    u32 folder_next_file_node_addr;
} file_node_t; 

extern file_node_t g_returned_file;
extern u32 g_dir_addr, g_old_dir_addr;

u8 read_disk(u32 addr);
void read_n_disk(u32 addr, u32 n, u8* target);
void disk_write(u32 addr, u8 byte);
void disk_n_write(u32 start_addr, u32 size, u8* data);
errcode_t fs_format_disk(void);
void fs_set_dir(u32 addr);
errcode_t fs_create_new_file(const char *folder, const char *filename, const char *extension, u32 size, u8 *data);
errcode_t fs_modify_file(const char *filename);
errcode_t fs_find(const char *filename);
errcode_t fs_loop_dir(bool init);
errcode_t fs_get_file_at(u32 index);
u32 fs_read(void *dest, const char *filename);
void print_errcode(errcode_t code);
