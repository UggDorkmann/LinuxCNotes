#ifndef __ALL_H__
#define __ALL_H__
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"unistd.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#include <signal.h>

#include <time.h>

#include <limits.h>

typedef struct sockaddr_in SA4;
typedef struct sockaddr SA;

#define GamePort 15251

typedef struct{
    int fd;
    int heartStopCount;
    time_t checkOnlineTime;
}cliInfo;
#endif
