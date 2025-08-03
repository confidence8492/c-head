#ifndef STANDARD_H
#define STANDARD_H

// 定義 size_t、ssize_t 和 int64_t
#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#ifndef SSIZE_T_DEFINED
#define SSIZE_T_DEFINED
typedef long ssize_t;
#endif

#ifndef INT64_T_DEFINED
#define INT64_T_DEFINED
typedef long long int64_t;
#endif

// macOS 系統調用號
#ifdef __APPLE__
#define SYS_WRITE   4
#define SYS_READ    3
#define SYS_GETPID  20
#else
#error "Unsupported platform"
#endif

// 函數聲明
void my_sleep(unsigned int seconds);
int my_getpid(void);
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);

#endif // STANDARD_H