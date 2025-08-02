#include "str.h"

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