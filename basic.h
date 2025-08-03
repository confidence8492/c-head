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



// 字符分類函數
int my_isalnum(int c);
int my_isalpha(int c);
int my_isdigit(int c);
int my_islower(int c);
int my_isupper(int c);
int my_isspace(int c);
int my_isprint(int c);
int my_ispunct(int c);
int my_iscntrl(int c);
int my_isxdigit(int c);

// 字符轉換函數
int my_tolower(int c);
int my_toupper(int c);



/* 數學常數 */
#define MY_PI 3.14159265358979323846      /* π */
#define MY_E 2.71828182845904523536       /* e */
#define MY_SQRT2 1.41421356237309504880   /* 根號2 */
#define MY_LN2 0.69314718055994530942     /* ln(2) */
#define MY_LN10 2.30258509299404568402    /* ln(10) */

/* 無窮大和非數值 */
#define MY_INFINITY (1.0 / 0.0)
#define MY_NAN (0.0 / 0.0)

/* 函數原型 */
double my_sin(double x);
double my_cos(double x);
double my_tan(double x);
double my_asin(double x);
double my_acos(double x);
double my_atan(double x);
double my_atan2(double y, double x);
double my_exp(double x);
double my_log(double x);
double my_log10(double x);
double my_pow(double x, double y);
double my_sqrt(double x);
double my_ceil(double x);
double my_floor(double x);
double my_fabs(double x);
double my_fmod(double x, double y);



#include "stddef.h"

/* 定義常見的宏 */
#define NULL ((void *)0)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX 32767

/* 記憶體管理函數 */
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

/* 字串轉換函數 */
int atoi(const char *str);
long atol(const char *str);
double atof(const char *str);

/* 隨機數生成 */
void srand(unsigned int seed);
int rand(void);

/* 程式終止 */
void exit(int status);
void abort(void);

/* 環境變數 */
char *getenv(const char *name);
