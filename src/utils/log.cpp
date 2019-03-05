#include "log.h"

std::string path_to_filename(std::string path) 
{
    return path.substr(path.find_last_of("/\\")+1);
}
