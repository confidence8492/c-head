#ifndef PRINT_H
#define PRINT_H

// 輸出單個字元
void printchar(char c);

// 輸出字串
void printstr(const char *str);

// 輸出整數
void printint(int num);

// 自定義 printf
void print(const char *format, int num, const char *str);

#endif
