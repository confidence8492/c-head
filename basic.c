#include "basic.h"  // 引入自定義的標頭檔案
#include "standard.h"  // 使用 write 系統呼叫

// 輸出單個字元
void printchar(char c) {
    write(1, &c, 1);
}

// 輸出整數
void printint(int num) {
    if (num == 0) {
        printchar('0');
        return;
    }

    // 處理負數
    if (num < 0) {
        printchar('-');
        num = -num;
    }

    // 輸出較高位數
    if (num >= 10) {
        printint(num / 10);
    }

    // 輸出當前數位
    printchar('0' + (num % 10));
}

// 輸出字串
void printstr(const char *str) {
    while (*str) {
        printchar(*str++);
    }
}

// 自定義 printf，處理格式符號
void print(const char *format, int num, const char *str) {
    while (*format) {
        if (*format == '%') {
            format++;  // 跳過 '%'
            if (*format == 'd') {
                printint(num);  // 輸出整數
            } else if (*format == 's') {
                printstr(str);  // 輸出字串
            } else {
                printchar('%');
                printchar(*format);  // 輸出未知符號
            }
        } else {
            printchar(*format);  // 輸出普通字符
        }
        format++;  // 移動到下一個字符
    }
}

// 定义 EOF，如果没有包含 stdio.h
#ifndef EOF
#define EOF (-1)
#endif

// 读取一个字符
char getchar_no_stdio() {
    char c;
    read(0, &c, 1);  // 读取一个字符
    return c;
}

// 自定义的简化版 scanf 函数
int scan(const char *format, int *num, char *str) {
    const char *ptr = format;
    int successful_reads = 0;

    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;  // 跳过 '%'

            if (*ptr == 'd') {
                // 读取整型数字
                int result = 0, sign = 1;
                char c;

                // 跳过空白字符
                while ((c = getchar_no_stdio()) == ' ' || c == '\t' || c == '\n' || c == '\r');

                // 处理负号
                if (c == '-') {
                    sign = -1;
                    c = getchar_no_stdio();
                }

                // 解析数字
                if (c >= '0' && c <= '9') {
                    do {
                        result = result * 10 + (c - '0');
                    } while ((c = getchar_no_stdio()) >= '0' && c <= '9');
                    *num = sign * result;
                    successful_reads++;
                }
            } 
            else if (*ptr == 's') {
                // 读取字符串
                char c;
                int i = 0;

                // 跳过空白字符
                while ((c = getchar_no_stdio()) == ' ' || c == '\t' || c == '\n' || c == '\r');

                // 读取字母直到遇到空白字符或换行
                while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r' && i < 99) {
                    str[i++] = c;
                    c = getchar_no_stdio();
                }
                str[i] = '\0';  // 结束字符串
                if (i > 0) successful_reads++;
            }
        }
        ptr++;
    }
    return successful_reads;  // 返回成功读取的项数
}




/* 計算字串長度（不含結束符 '\0'） */
unsigned int len(const char *str) {
    const char *p = str;
    while (*p) {
        p++;
    }
    return p - str; /* 指標差值即為長度 */
}

/* 將 src 字串複製到 dest（含結束符 '\0'），返回 dest */
char *cpy(char *dest, const char *src) {
    char *start = dest;
    while ((*dest++ = *src++)) {
        /* 複製字符直到遇到 '\0'，同時複製結束符 */
    }
    return start;
}

/* 將 src 追加到 dest 後（含結束符 '\0'），返回 dest */
char *cat(char *dest, const char *src) {
    char *start = dest;
    /* 移到 dest 的末尾 */
    while (*dest) {
        dest++;
    }
    /* 複製 src 到 dest 末尾 */
    while ((*dest++ = *src++)) {
        /* 複製字符直到遇到 '\0'，同時複製結束符 */
    }
    return start;
}

/* 比較 str1 和 str2，返回 0（相等）、正數（str1 > str2）或負數（str1 < str2） */
int cmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

/* 在 str 中查找 sub 的第一次出現，返回指向該位置的指標或 NULL */
char *str(const char *str, const char *sub) {
    if (!*sub) {
        return (char *)str; /* 空子字串返回原字串 */
    }
    for (; *str; str++) {
        const char *s = str;
        const char *p = sub;
        /* 檢查從當前位置開始是否匹配 */
        while (*s && *p && *s == *p) {
            s++;
            p++;
        }
        if (!*p) {
            return (char *)str; /* 找到完整匹配 */
        }
    }
    return NULL; /* 未找到 */
}