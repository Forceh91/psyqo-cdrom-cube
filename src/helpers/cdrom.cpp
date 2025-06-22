#include "psyqo/alloc.h"
#include "psyqo/xprintf.h"
#include "cdrom.hh"

psyqo::CDRomDevice CDRomHelper::m_cdrom;
psyqo::ISO9660Parser CDRomHelper::m_isoParser = psyqo::ISO9660Parser(&m_cdrom);
psyqo::paths::CDRomLoader CDRomHelper::m_cdromLoader;

void CDRomHelper::init()
{
    m_cdrom.prepare();
}

// reads a file off of the cd rom into memory (most likely a file full of binary data)
// dont forget to free the returned data when you're done with it
void CDRomHelper::load_file(const char *file_name, eastl::function<void(psyqo::Buffer<uint8_t> &&)> callback)
{
    printf("CD ROM: Attempting to read %s...\n", file_name);

    // read the file off of the disc
    m_cdromLoader.readFile(file_name, m_isoParser,
                           [file_name, callback](psyqo::Buffer<uint8_t> &&buffer)
                           {
                               printf("CD ROM: Finished reading file (%d bytes) from cd rom.\n", buffer.size());

                               // the file isnt there or its empty
                               if (buffer.empty())
                               {
                                   buffer.clear();
                                   printf("CD ROM: File %s not found on CD or file is empty\n", file_name);
                                   return;
                               }

                               // callback to the loader
                               callback(eastl::move(buffer));
                           });
}

void CDRomHelper::get_iso_file_name(const char *file_name, char *iso_filename)
{
    // modify the given file name into the correct format for the ps1 to read it
    snprintf(iso_filename, MAX_CDROM_FILE_NAME_LEN, "%s;1", file_name);
}
