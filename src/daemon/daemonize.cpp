#include "daemonize.h"
#include <pwd.h>
#include <grp.h>
#include <cstdlib>
#include <unistd.h>

void daemonize(std::string uid, std::string gid)
{
    // drop privilege
    if (gid != "")
    {
        struct group* gidStruct = getgrnam(gid.c_str());
        setgid(gidStruct->gr_gid);
    }
    if (uid != "")
    {
        struct passwd* uidStruct = getpwnam(uid.c_str());
        setuid(uidStruct->pw_uid);
    }
    if (fork() != 0)
    {
        //we use exit here, it could be not recommanded on other use
        //but for double forking we don't need to return on main function
        exit(0);
    }
    if (fork() != 0)
    {
        exit(0);
    }
}
