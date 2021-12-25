#include "prog_path.h"

#include "linux/limits.h"
#include "unistd.h"

#include "filesystem"

std::string ProgPath::Get()
{
    char* path_cstr = (char*)malloc(PATH_MAX);
    unsigned code = readlink("/proc/self/exe", path_cstr, PATH_MAX);

    std::filesystem::path path = path_cstr;
    free(path_cstr);

    return path.parent_path().generic_string();
}
