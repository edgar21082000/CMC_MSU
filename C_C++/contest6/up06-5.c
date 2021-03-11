#include <sys/stat.h>
#include <sys/types.h>

enum
{
    UBS = 6, // user bits shift
    GBS = 3, // gid bits shift
    BMASK = 0x7, //bits mask
};

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int myaccess(const struct stat *stb, const struct Task *task, int access);

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (task->uid == 0) {
        return 1;
    }
    
    if (task->uid == stb->st_uid) {
        return ((stb->st_mode >> UBS) & BMASK) >= access;
    }
    
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return ((stb->st_mode >> GBS) & BMASK) >= access;
        }
    }

    return (stb->st_mode & BMASK) >= access;
}
