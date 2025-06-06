#ifndef _MESH_H
#define _MESH_H

#include <stdint.h>
#include <EASTL/fixed_string.h>
#include "psyqo/vector.hh"
#include "../helpers/file_defs.hh"

#define MAX_LOADED_MESHES 32
#define MAX_FACES_PER_MESH 1024

typedef struct _INDEX
{
    int16_t v0, v1, v2, v3;
} INDEX;

typedef struct _VERTEX_PAINT
{
    int16_t r, g, b;
} VERTEX_PAINT;

typedef struct _UV
{
    int16_t u, v;
} UV;

typedef struct _MESH
{
    psyqo::Vec3 *vertices;
    VERTEX_PAINT *vertex_paint;
    INDEX *indices;
    psyqo::Vec3 *normals;
    INDEX *normal_indices;
    UV *uvs;
    INDEX *uv_indices;
    int vertex_count;
    int indices_count;
    int faces_num;
} MESH;

typedef struct _LOADED_MESH
{
    eastl::fixed_string<char, MAX_CDROM_FILE_NAME_LEN> mesh_name;
    bool is_loaded;
    MESH mesh;
} LOADED_MESH;

class MeshManager
{
    static LOADED_MESH m_loaded_meshes[MAX_LOADED_MESHES];

    static MESH *is_mesh_loaded(const char *mesh_name);
    static int8_t find_space_for_mesh(void);

public:
    static void load_mesh_from_cdrom(const char *mesh_name, eastl::function<void(MESH *mesh_out)> onComplete);
    static void unload_mesh(const char *mesh_name);
};

#endif
