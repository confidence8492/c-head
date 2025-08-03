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















// 字符分類表（位陣列）
#define CT_ALNUM  0x01  // 字母或數字
#define CT_ALPHA  0x02  // 字母
#define CT_DIGIT  0x04  // 數字
#define CT_LOWER  0x08  // 小寫
#define CT_UPPER  0x10  // 大寫
#define CT_SPACE  0x20  // 空白
#define CT_PRINT  0x40  // 可列印
#define CT_PUNCT  0x80  // 標點
#define CT_CTRL   0x100 // 控制字符
#define CT_XDIGIT 0x200 // 十六進制數字

// 靜態查找表，涵蓋 ASCII 0-127 和 EOF (-1)
static const unsigned short ctype_table[128] = {
    // 0-31: 控制字符
    CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL,
    CT_CTRL, CT_CTRL | CT_SPACE, CT_CTRL | CT_SPACE, CT_CTRL | CT_SPACE,
    CT_CTRL | CT_SPACE, CT_CTRL | CT_SPACE, CT_CTRL, CT_CTRL,
    CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL,
    CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL, CT_CTRL,
    // 32-47: 空格和標點
    CT_SPACE | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    // 48-57: 數字
    CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT, CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT,
    CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT, CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT,
    CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT, CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT,
    CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT, CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT,
    CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT, CT_DIGIT | CT_ALNUM | CT_PRINT | CT_XDIGIT,
    // 58-64: 標點
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    // 65-90: 大寫字母
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // A
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // B
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // C
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // D
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // E
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT | CT_XDIGIT, // F
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT, // G-Z
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_UPPER | CT_PRINT,
    // 91-96: 標點
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    // 97-122: 小寫字母
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // a
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // b
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // c
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // d
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // e
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT | CT_XDIGIT, // f
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT, // g-z
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    CT_ALPHA | CT_ALNUM | CT_LOWER | CT_PRINT,
    // 123-126: 標點
    CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT, CT_PUNCT | CT_PRINT,
    // 127: 控制字符
    CT_CTRL
};

// 分類函數實現
#define CHECK_CTYPE(c, type) ((c) >= 0 && (c) < 128 ? (ctype_table[(unsigned char)(c)] & (type)) != 0 : 0)

int my_isalnum(int c) { return CHECK_CTYPE(c, CT_ALNUM); }
int my_isalpha(int c) { return CHECK_CTYPE(c, CT_ALPHA); }
int my_isdigit(int c) { return CHECK_CTYPE(c, CT_DIGIT); }
int my_islower(int c) { return CHECK_CTYPE(c, CT_LOWER); }
int my_isupper(int c) { return CHECK_CTYPE(c, CT_UPPER); }
int my_isspace(int c) { return CHECK_CTYPE(c, CT_SPACE); }
int my_isprint(int c) { return CHECK_CTYPE(c, CT_PRINT); }
int my_ispunct(int c) { return CHECK_CTYPE(c, CT_PUNCT); }
int my_iscntrl(int c) { return CHECK_CTYPE(c, CT_CTRL); }
int my_isxdigit(int c) { return CHECK_CTYPE(c, CT_XDIGIT); }

// 字符轉換函數
int my_tolower(int c) {
    if (my_isupper(c)) {
        return c + ('a' - 'A'); // ASCII 中，a-A = 32
    }
    return c;
}

int my_toupper(int c) {
    if (my_islower(c)) {
        return c - ('a' - 'A'); // ASCII 中，a-A = 32
    }
    return c;
}


































/* 輔助函數：模範化角度到 [-π, π] */
static double normalize_angle(double x) {
    while (x > MY_PI) x -= 2.0 * MY_PI;
    while (x < -MY_PI) x += 2.0 * MY_PI;
    return x;
}

/* 三角函數：sin 使用泰勒展開 */
double my_sin(double x) {
    x = normalize_angle(x); /* 將角度規範化 */
    double result = x, term = x;
    int n = 1;
    while (my_fabs(term) > 1e-10) { /* 精度控制 */
        term *= -x * x / ((2 * n) * (2 * n + 1)); /* 泰勒展開項：(-1)^n * x^(2n+1) / (2n+1)! */
        result += term;
        n++;
    }
    return result;
}

/* 三角函數：cos 使用泰勒展開 */
double my_cos(double x) {
    x = normalize_angle(x);
    double result = 1.0, term = 1.0;
    int n = 1;
    while (my_fabs(term) > 1e-10) {
        term *= -x * x / ((2 * n - 1) * (2 * n)); /* 泰勒展開項：(-1)^n * x^(2n) / (2n)! */
        result += term;
        n++;
    }
    return result;
}

/* 三角函數：tan = sin/cos */
double my_tan(double x) {
    double cos_x = my_cos(x);
    if (my_fabs(cos_x) < 1e-10) return MY_NAN; /* 避免除以零 */
    return my_sin(x) / cos_x;
}

/* 反三角函數：asin 使用泰勒展開 */
double my_asin(double x) {
    if (x < -1.0 || x > 1.0) return MY_NAN;
    double result = x, term = x;
    int n = 1;
    while (my_fabs(term) > 1e-10) {
        term *= (x * x * (2 * n - 1) * (2 * n - 1)) / (2 * n * (2 * n + 1));
        result += term;
        n++;
    }
    return result;
}

/* 反三角函數：acos = π/2 - asin */
double my_acos(double x) {
    if (x < -1.0 || x > 1.0) return MY_NAN;
    return MY_PI / 2.0 - my_asin(x);
}

/* 反三角函數：atan 使用泰勒展開 */
double my_atan(double x) {
    if (x < -1.0 || x > 1.0) {
        return x > 0 ? MY_PI / 2.0 : -MY_PI / 2.0;
    }
    double result = x, term = x;
    int n = 1;
    while (my_fabs(term) > 1e-10) {
        term *= -x * x * (2 * n - 1) / (2 * n + 1);
        result += term;
        n++;
    }
    return result;
}

/* atan2：考慮象限 */
double my_atan2(double y, double x) {
    if (x > 0) return my_atan(y / x);
    if (x < 0 && y >= 0) return my_atan(y / x) + MY_PI;
    if (x < 0 && y < 0) return my_atan(y / x) - MY_PI;
    if (x == 0 && y > 0) return MY_PI / 2.0;
    if (x == 0 && y < 0) return -MY_PI / 2.0;
    return MY_NAN;
}

/* 指數函數：exp 使用泰勒展開 */
double my_exp(double x) {
    double result = 1.0, term = 1.0;
    int n = 1;
    while (my_fabs(term) > 1e-10) {
        term *= x / n;
        result += term;
        n++;
    }
    return result;
}

/* 自然對數：log 使用牛頓迭代法 */
double my_log(double x) {
    if (x <= 0) return MY_NAN;
    double result = 0.0;
    if (x != 1.0) {
        double guess = 1.0;
        for (int i = 0; i < 20; ++i) { /* 迭代次數 */
            guess -= (my_exp(guess) - x) / my_exp(guess); /* 牛頓法 */
        }
        result = guess;
    }
    return result;
}

/* 常用對數：log10 = log(x)/log(10) */
double my_log10(double x) {
    return my_log(x) / MY_LN10;
}

/* 冪函數：pow(x, y) = exp(y * log(x)) */
double my_pow(double x, double y) {
    if (x < 0 && y != (int)y) return MY_NAN; /* 負數的非整數次冪無定義 */
    if (x == 0 && y <= 0) return MY_NAN;
    return my_exp(y * my_log(x));
}

/* 平方根：使用牛頓迭代法 */
double my_sqrt(double x) {
    if (x < 0) return MY_NAN;
    if (x == 0) return 0.0;
    double guess = x;
    for (int i = 0; i < 20; ++i) {
        guess = 0.5 * (guess + x / guess); /* 牛頓法 */
    }
    return guess;
}

/* 向上取整 */
double my_ceil(double x) {
    int i = (int)x;
    return (x > i) ? (double)(i + 1) : (double)i;
}

/* 向下取整 */
double my_floor(double x) {
    return (double)((int)x);
}

/* 絕對值 */
double my_fabs(double x) {
    return (x < 0) ? -x : x;
}

/* 模運算 */
double my_fmod(double x, double y) {
    if (y == 0) return MY_NAN;
    int quotient = (int)(x / y);
    return x - quotient * y;
}