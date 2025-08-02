#ifndef BASIC_H
#define BASIC_H

// 輸出單個字元
void printchar(char c);

// 輸出字串
void printstr(const char *str);

// 輸出整數
void printint(int num);

// 自定義 printf
void print(const char *format, int num, const char *str);


// 定义 EOF (如果没有引入 stdio.h)
#ifndef EOF
#define EOF (-1)
#endif

// 声明 getchar_no_stdio 函数
char getchar_no_stdio();

// 自定义的 scanf 函数
int scan(const char *format, int *num, char *str);

// 定义 EOF (如果没有引入 stdio.h)




#endif // SCAN_H