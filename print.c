#include "print.h"  // 引入自定義的標頭檔案
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
