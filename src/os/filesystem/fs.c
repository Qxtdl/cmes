#include "fs.h"
#include "../../taulib/globals.h"
#include "../../taulib/memorymap.h"

file_t g_returned_file;
u16 returned_file_address;

u8 read_disk(u16 addr) 
{
    *DISK_ADDRESS = addr;
    return *DISK_OUT;
}

void read_n_disk(u16 addr, u16 n, u8* target)
{
    for (u16 i = 0; i < n; i++) 
    {
        target[i] = read_disk(i+addr); 
    }
}

void disk_write(u16 addr, u8 byte)
{
    *DISK_ADDRESS = addr;
    *DISK_DATA = byte;
    *DISK_WRITE = true;
}

void disk_n_write(u16 start_addr, u16 size, u8* data)
{
    for (u16 i = 0; i <= size; i++)
    {
        *DISK_ADDRESS = start_addr + i;
        *DISK_DATA = data[i];
        *DISK_WRITE = true;
    }
}

errcode_t fs_create_new_file(const char *filename, const char *extension, u16 size, u8 *data)
{
    bool is_disk_formatted = read_disk(FS_FORMATTED);

    u16 last_created_file_header_address;
    read_n_disk(HEADER_LAST_FILE_HEADER_CREATED_PTR, sizeof(u16), (u8 *)&last_created_file_header_address);

    file_t last_created_file;
    read_n_disk(last_created_file_header_address, sizeof(file_t), (u8 *)&last_created_file);

    u16 free_data_region;
    if (is_disk_formatted)
        free_data_region = last_created_file.data_ptr + last_created_file.size;
    else free_data_region = HEADER_SIZE + 32;

    disk_n_write(free_data_region, size, data);

    // now create the file header

    file_t new_file;
    strcpy(new_file.name, filename);
    strcpy(new_file.extension, extension);
    new_file.size = size;
    new_file.data_ptr = free_data_region;
    last_created_file_header_address += sizeof(file_t);

    disk_n_write(last_created_file_header_address, sizeof(file_t), (u8 *)&new_file);
    disk_n_write(HEADER_LAST_FILE_HEADER_CREATED_PTR, sizeof(u16), (u8 *)&last_created_file_header_address);

    if (!is_disk_formatted)
        disk_write(FS_FORMATTED, true);

    return FS_OK;
}   

errcode_t fs_modify_file(const char *filename)
{
    return 0;
}

errcode_t fs_find(const char *filename) 
{
    for (u16 i = sizeof(file_t); i < HEADER_SIZE; i += sizeof(file_t)) {
        file_t target;
        read_n_disk(i,sizeof(file_t), (u8 *)&target);
        if (target.data_ptr == 0)
            break;
        if (!strcmp(target.name, filename))  {
            g_returned_file = target;
            return FS_OK;
        }
    }
    return FS_BAD;
}

errcode_t fs_get_file_at(u32 index) 
{
    read_n_disk(index * sizeof(file_t) ,sizeof(file_t), (u8 *)&g_returned_file);
    if (g_returned_file.data_ptr == 0)
        return FS_BAD;
    return FS_OK;
}

u16 fs_read(void *dest, const char *filename) 
{
    if (!fs_find(filename))
        return 0;
    read_n_disk(g_returned_file.data_ptr, sizeof(g_returned_file.size), dest);
    return g_returned_file.size;
}

void print_errcode(errcode_t code)
{
    putc('\n');
    switch (code) {
        case FS_OK: puts("FS_OK\n"); break;
        case FS_BAD: puts("FS_BAD\n"); break;
        default: puts("Unknown FS code\n"); break;
    }
}
