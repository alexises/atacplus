#ifndef DAEMONIZE_H
#define DAEMONIZE_H
#include <string>

/**
 * daemonize : fork and drop privileges
 *
 * @param[in] uid : uid to drop privileges
 * @param[in] gid : gid to drop privileges
 *
 * the parents process will be shuted down automaticaly and on the return 
 * of this function you will be properly daemonized
 */
void daemonize(std::string uid, std::string gid);

#endif
