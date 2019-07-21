#include"../all.h"
int main(){
	printf("/************* sysconf **************/\n");
#ifdef _SC_ARG_MAX
	printf("_SC_ARG_MAX          = %ld\n",sysconf(_SC_ARG_MAX));
#endif
#ifdef _SC_ATEXIT_MAX
	printf("_SC_ATEXIT_MAX       = %ld\n",sysconf(_SC_ATEXIT_MAX));
#endif
#ifdef _SC_CHILD_MAX
	printf("_SC_CHILD_MAX        = %ld\n",sysconf(_SC_CHILD_MAX));
#endif
#ifdef _SC_CLK_TCK
	printf("_SC_CLK_TCK          = %ld\n",sysconf(_SC_CLK_TCK));
#endif
#ifdef _SC_COLL_WEIGHTS_MAX
	printf("_SC_COLL_WEIGHTS_MAX = %ld\n",sysconf(_SC_COLL_WEIGHTS_MAX));
#endif
#ifdef	 _SC_DELAYTIMER_MAX
	printf("_SC_DELAYTIMER_MAX   = %ld\n",sysconf(_SC_DELAYTIMER_MAX));
#endif
#ifdef	_SC_HOST_NAME_MAX
	printf("_SC_HOST_NAME_MAX    = %ld\n",sysconf(_SC_HOST_NAME_MAX));
#endif
#ifdef	_SC_IOV_MAX
	printf("_SC_IOV_MAX          = %ld\n",sysconf(_SC_IOV_MAX));
#endif
#ifdef	_SC_LINE_MAX
	printf("_SC_LINE_MAX         = %ld\n",sysconf(_SC_LINE_MAX));
#endif
#ifdef	_SC_LOGIN_NAME_MAX
	printf("_SC_LOGIN_NAME_MAX   = %ld\n",sysconf(_SC_LOGIN_NAME_MAX));
#endif
#ifdef	_SC_NGROUPS_MAX
	printf("_SC_NGROUPS_MAX      = %ld\n",sysconf(_SC_NGROUPS_MAX));
#endif
#ifdef	_SC_OPEN_MAX
	printf("_SC_OPEN_MAX         = %ld\n",sysconf(_SC_OPEN_MAX));
#endif
#ifdef	_SC_PAGESIZE
	printf("_SC_PAGESIZE         = %ld\n",sysconf(_SC_PAGESIZE));
#endif
#ifdef	_SC_RTSIG_MAX
	printf("_SC_RTSIG_MAX        = %ld\n",sysconf(_SC_RTSIG_MAX));
#endif
#ifdef	_SC_SEM_NSEMS_MAX
	printf("_SC_SEM_NSEMS_MAX    = %ld\n",sysconf(_SC_SEM_NSEMS_MAX));
#endif
#ifdef	_SC_SEM_VALUE_MAX
	printf("_SC_SEM_VALUE_MAX    = %ld\n",sysconf(_SC_SEM_VALUE_MAX));
#endif
#ifdef	_SC_SIGQUEUE_MAX
	printf("_SC_SIGQUEUE_MAX     = %ld\n",sysconf(_SC_SIGQUEUE_MAX));
#endif
#ifdef	_SC_STREAM_MAX
	printf("_SC_STREAM_MAX       = %ld\n",sysconf(_SC_STREAM_MAX));
#endif
#ifdef	_SC_SYMLOOP_MAX
	printf("_SC_SYMLOOP_MAX      = %ld\n",sysconf(_SC_SYMLOOP_MAX));
#endif
#ifdef	_SC_TIMER_MAX
	printf("_SC_TIMER_MAX        = %ld\n",sysconf(_SC_TIMER_MAX));
#endif
#ifdef	_SC_TTY_NAME_MAX
	printf("_SC_TTY_NAME_MAX     = %ld\n",sysconf(_SC_TTY_NAME_MAX));
#endif
#ifdef	_SC_TZNAME_MAX
	printf("_SC_TZNAME_MAX       = %ld\n",sysconf(_SC_TZNAME_MAX));
#endif
	printf("/************* pathconf **************/\n");
#ifdef		_PC_FILESIZEBITS
	printf("_PC_FILESIZEBITS         = %ld\n",pathconf("./a.out",_PC_FILESIZEBITS));
#endif                               
#ifdef	_PC_LINK_MAX                 
	printf("_PC_LINK_MAX             = %ld\n",pathconf("./a.out",_PC_LINK_MAX));
#endif                               
#ifdef _PC_MAX_CANON                 
	printf("_PC_MAX_CANON            = %ld\n",pathconf("./a.out",_PC_MAX_CANON));
#endif                               
#ifdef	_PC_MAX_INPUT                
	printf("_PC_MAX_INPUT            = %ld\n",pathconf("./a.out",_PC_MAX_INPUT));
#endif                               
#ifdef	_PC_NAME_MAX                 
	printf("_PC_NAME_MAX             = %ld\n",pathconf("/dev",_PC_NAME_MAX));
#endif                               
#ifdef	_PC_PATH_MAX                 
	printf("_PC_PATH_MAX             = %ld\n",pathconf("/dev",_PC_PATH_MAX));
#endif                               
#ifdef	_PC_PIPE_BUF                 
	printf("_PC_PIPE_BUF             = %ld\n",pathconf("/dev",_PC_PIPE_BUF));
#endif
#ifdef	_PC_TIMESTAMP_RESOLUTION
	printf("_PC_TIMESTAMP_RESOLUTION = %ld\n",pathconf("./a.out",_PC_TIMESTAMP_RESOLUTION));
#endif
#ifdef	_PC_SYMLINK_MAX
	printf("_PC_SYMLINK_MAX          = %ld\n",pathconf("/dev",_PC_SYMLINK_MAX));
#endif
	exit(0);
}

