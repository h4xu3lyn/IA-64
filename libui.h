#ifndef _LIBUI_H
#define _LIBUI_H

#include <unistd.h>

ssize_t sysWrite(int fd, void *buf, size_t len);
BOOL elfSymLoad(const char *file_name);
char *getSimID(void);

#endif
