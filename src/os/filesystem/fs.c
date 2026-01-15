#include "fs.h"
#include "../../taulib/globals.h"
#include "../../taulib/memorymap.h"

file_node_t g_returned_file;
static file_node_t i_returned_file; // like g_returned_file but for the filesystem's internals itsself
u16 returned_file_address;

u8 read_disk(u32 addr) 
{
    *DISK_ADDRESS = addr;
    return *DISK_OUT;
}

void read_n_disk(u32 addr, u32 n, u8* target)
{
    for (u32 i = 0; i < n; i++) 
        target[i] = read_disk(i+addr); 
}

void disk_write(u32 addr, u8 byte)
{
    *DISK_ADDRESS = addr;
    *DISK_DATA = byte;
    *DISK_WRITE = true; //$8310
}

void disk_n_write(u32 start_addr, u32 size, u8* data)
{
    for (u32 i = 0; i <= size; i++)
    {
        *DISK_ADDRESS = start_addr + i;
        *DISK_DATA = data[i];
        *DISK_WRITE = true;
    }
}

errcode_t fs_format_disk(void) {
    file_node_t root = {
        .name = "/",
        .extension = "f",
        .self_addr = 0,
        .size = 0,
        .data_ptr = DATA_REGION_START,
        .next_file_node_addr = 0
    };

    disk_n_write(ROOT_NODE, sizeof(root), (u8 *)&root);

    disk_write(FS_FORMATTED, 1);

    return FS_OK;
}

static bool search_node_for_file(u32 node_addr, const char *filename) {
    file_node_t node;
    // Read initial node addr into disk
    read_n_disk(node_addr, sizeof(file_node_t), (u8 *)&node);

    while (1) {
        if (!strncmp(node.name, filename, MAX_FILE_NAME_SIZE)) {
            i_returned_file = node;
            return true;
        }

        if (*node.extension == 'f' && node.folder_next_file_node_addr)
            read_n_disk(node.folder_next_file_node_addr, sizeof(file_node_t), (u8 *)&node);
        else if (*node.extension == 'f' && !node.folder_next_file_node_addr) {
            i_returned_file = node;
            return false;
        }
        else if (node.next_file_node_addr) {
            read_n_disk(node.next_file_node_addr, sizeof(file_node_t), (u8 *)&node);
        } else {
            // END OF THIS LINKED LIST
            i_returned_file = node;
            return false;
        }
    }
}

u32 g_old_dir_addr;
u32 g_dir_addr = ROOT_NODE; 

void fs_set_dir(u32 addr) {
    g_old_dir_addr = g_dir_addr;
    g_dir_addr = addr;
}

errcode_t fs_create_new_file(const char *folder, const char *filename, const char *extension, u32 size, u8 *data)
{
    // Does the folder even exist?
    if (!search_node_for_file(g_dir_addr, folder))
        return FS_BAD;

    // Put file data into free data region
    u32 last_created_file_node_address;
    read_n_disk(HEADER_LAST_CREATED_FILE_NODE_ADDRESS_PTR, sizeof(u16), (u8 *)&last_created_file_node_address);

    file_node_t last_created_file;
    read_n_disk(last_created_file_node_address, sizeof(file_node_t), (u8 *)&last_created_file);

    u32 free_data_region;
    if (read_disk(FS_FORMATTED))
        free_data_region = last_created_file.data_ptr + last_created_file.size;
    else free_data_region = DATA_REGION_START;

    disk_n_write(free_data_region, size, data);

    // Create file and put it in the header
    last_created_file_node_address += sizeof(file_node_t);
    file_node_t new_file;
    strcpy(new_file.name, filename);
    strcpy(new_file.extension, extension);
    new_file.size = size;
    new_file.data_ptr = free_data_region;
    new_file.self_addr = last_created_file_node_address;
    new_file.next_file_node_addr = 0;

    // We searched for the folder earlier now use it
    search_node_for_file(i_returned_file.self_addr, NULL);
    i_returned_file.next_file_node_addr = new_file.self_addr;

    // BUGGY
    disk_n_write(i_returned_file.self_addr, sizeof(file_node_t) - 1, (u8 *)&i_returned_file);

    if (i_returned_file.folder_next_file_node_addr == 0) {
        i_returned_file.folder_next_file_node_addr = new_file.self_addr;
        disk_n_write(i_returned_file.self_addr, sizeof(file_node_t) - 1, (u8 *)&i_returned_file);
    }

    disk_n_write(last_created_file_node_address, sizeof(file_node_t), (u8 *)&new_file);
    disk_n_write(HEADER_LAST_CREATED_FILE_NODE_ADDRESS_PTR, sizeof(u16), (u8 *)&last_created_file_node_address);

    return FS_OK;
}   

errcode_t fs_modify_file(const char *filename)
{
    return 0;
}

errcode_t fs_find(const char *filename) 
{
    if (!search_node_for_file(g_dir_addr, filename))
        return FS_BAD;
    g_returned_file = i_returned_file;
    return FS_OK;
}

errcode_t fs_loop_dir(bool init) 
{
    static file_node_t node;
    if (init) {
        read_n_disk(g_dir_addr, sizeof(file_node_t), (u8 *)&node);
        return FS_OK;
    }

    if (!node.next_file_node_addr)
        return FS_BAD;

    read_n_disk(node.next_file_node_addr, sizeof(file_node_t), (u8 *)&g_returned_file);
    node = g_returned_file;

    return FS_OK;
}

errcode_t fs_get_file_at(u32 index) 
{
    read_n_disk(index * sizeof(file_node_t) ,sizeof(file_node_t), (u8 *)&g_returned_file);
    if (g_returned_file.data_ptr == 0)
        return FS_BAD;
    return FS_OK;
}

u32 fs_read(void *dest, const char *filename) 
{
    if (!fs_find(filename))
        return 0;
    read_n_disk(g_returned_file.data_ptr, sizeof(g_returned_file.size), dest);
    return g_returned_file.size;
}

void print_errcode(errcode_t code)
{
    switch (code) {
        case FS_OK: puts("FS_OK\n"); break;
        case FS_BAD: puts("FS_BAD\n"); break;
        default: puts("Unknown FS code\n"); break;
    }
}
