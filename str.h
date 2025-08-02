#ifndef STR_H
#define STR_H

/* 計算字串長度（不含結束符 '\0'） */



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

#endif /* MYSTRING_H */