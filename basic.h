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







#ifndef NULL
#define NULL ((void *)0)
#endif
unsigned int len(const char *str);

/* 將 src 字串複製到 dest（含結束符 '\0'），返回 dest */
char *cpy(char *dest, const char *src);

/* 將 src 追加到 dest 後（含結束符 '\0'），返回 dest */
char *append(char *dest, const char *src);

/* 比較 str1 和 str2，返回 0（相等）、正數（str1 > str2）或負數（str1 < str2） */
int cmp(const char *str1, const char *str2);

/* 在 str 中查找 sub 的第一次出現，返回指向該位置的指標或 NULL */
char *str(const char *str, const char *sub);

