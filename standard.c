// 自訂 sleep 函數，單位為秒（使用忙等待模擬延遲）
void my_sleep(unsigned int seconds) {
    // 忙等待：粗略模擬延遲，循環次數根據系統性能調整
    unsigned long long cycles = seconds * 1000000; // 假設每秒 100 萬次循環
    for (unsigned long long i = 0; i < cycles; i++) {
        volatile int dummy = 0; // 防止編譯器優化掉循環
    }
}

// 自訂 getpid 函數，使用內聯彙編調用 macOS 系統調用
// macOS 系統調用號：SYS_getpid = 20
int my_getpid(void) {
    int pid;
#ifdef __x86_64__
    __asm__ volatile (
        "mov $20, %%rax\n"     // SYS_getpid = 20
        "syscall\n"            // 調用系統調用
        "mov %%eax, %0\n"      // 將返回值存入 pid
        : "=r" (pid)           // 輸出
        :                      // 無輸入
        : "%rax", "%rcx", "%r11" // 使用的寄存器
    );
#elif defined(__arm64__)
    __asm__ volatile (
        "mov x0, #20\n"        // SYS_getpid = 20
        "svc #0\n"             // 系統調用
        "mov %w0, w0\n"        // 將返回值存入 pid
        : "=r" (pid)           // 輸出
        :                      // 無輸入
        : "x0", "x1"           // 使用的寄存器
    );
#else
    #error "Unsupported architecture"
#endif
    return pid;
}