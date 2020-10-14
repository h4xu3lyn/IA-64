#ifndef _NETDEV_H
#define _NETDEV_H

extern int isnetio (void);
extern int netdev_open (char *name, unsigned char *macaddr);
extern int netdev_attach (int fd, unsigned int ipaddr);
extern int netdev_detach (int fd);
extern void netdev_cleanup (void);

#endif
