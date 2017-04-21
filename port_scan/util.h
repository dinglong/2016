#ifndef _UTIL_H_
#define _UTIL_H_

typedef void sigfunc(int);
sigfunc* signal(int signo, sigfunc* func);

#endif

