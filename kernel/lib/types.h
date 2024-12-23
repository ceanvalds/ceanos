#pragma once
#include <stdint.h>

typedef long off_t;
typedef long time_t;
typedef int mode_t;
typedef uint64_t uid_t;
typedef uint64_t gid_t;
typedef long ssize_t;

struct dirrent {
    char name[256];
};