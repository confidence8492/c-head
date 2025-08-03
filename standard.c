#include "standard.h"

// 自訂 sleep 函數，單位為秒（使用忙等待模擬延遲）
void my_sleep(unsigned int seconds) {
    unsigned long long cycles = seconds * 1000000;
    for (unsigned long long i = 0; i < cycles; i++) {
        volatile int dummy = 0;
    }
}

// 自訂 getpid 函數
int my_getpid(void) {
    int pid;
#ifdef __x86_64__
    __asm__ volatile (
        "mov %1, %%rax\n"
        "syscall\n"
        "mov %%eax, %0\n"
        : "=r" (pid)
        : "i" (SYS_GETPID)
        : "%rax", "%rcx", "%r11"
    );
#elif defined(__arm64__)
    __asm__ volatile (
        "mov x0, %1\n"
        "svc #0\n"
        "mov %w0, w0\n"
        : "=r" (pid)
        : "i" (SYS_GETPID)
        : "x0", "x1"
    );
#else
    #error "Unsupported architecture"
#endif
    return pid;
}

// 自訂 write 函數
ssize_t write(int fd, const void *buf, size_t count) {
    ssize_t ret;
#ifdef __x86_64__
    __asm__ volatile (
        "mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0\n"
        : "=r" (ret)
        : "i" (SYS_WRITE), "r" ((int64_t)fd), "r" (buf), "r" ((int64_t)count)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11"
    );
#elif defined(__arm64__)
    __asm__ volatile (
        "mov x0, %2\n"
        "mov x1, %3\n"
        "mov x2, %4\n"
        "mov x16, %1\n"
        "svc #0\n"
        "mov %0, x0\n"
        : "=r" (ret)
        : "i" (SYS_WRITE), "r" ((int64_t)fd), "r" (buf), "r" ((int64_t)count)
        : "x0", "x1", "x2", "x16"
    );
#else
    #error "Unsupported architecture"
#endif
    return ret;
}

// 自訂 read 函數
ssize_t read(int fd, void *buf, size_t count) {
    ssize_t ret;
#ifdef __x86_64__
    __asm__ volatile (
        "mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0\n"
        : "=r" (ret)
        : "i" (SYS_READ), "r" ((int64_t)fd), "r" (buf), "r" ((int64_t)count)
        : "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11"
    );
#elif defined(__arm64__)
    __asm__ volatile (
        "mov x0, %2\n"
        "mov x1, %3\n"
        "mov x2, %4\n"
        "mov x16, %1\n"
        "svc #0\n"
        "mov %0, x0\n"
        : "=r" (ret)
        : "i" (SYS_READ), "r" ((int64_t)fd), "r" (buf), "r" ((int64_t)count)
        : "x0", "x1", "x2", "x16"
    );
#else
    #error "Unsupported architecture"
#endif
    return ret;
}