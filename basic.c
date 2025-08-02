#include "basic.h"  // 引入自定義的標頭檔案
#include <unistd.h>  // 使用 write 系統呼叫

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
