//last read:<Unix network programming - volumn 1> page 50
//last read:<Unix network programming - volumn 2> page 0
#ifndef __ALL_H__
#define __ALL_H__
/* used in dir unixNetWorkProgramming */
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

typedef struct sockaddr_in SA4;
typedef struct sockaddr SA;

#define MAXLINE 128

/*error number*/
#define ERR_BIND        -100
#define ERR_SOCKET      -101










#endif
