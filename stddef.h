#ifndef _STDDEF_H
#define _STDDEF_H

/* 定義 size_t，通常是無符號整數類型，用於表示物件大小 */
typedef unsigned long size_t;

/* 定義 ptrdiff_t，通常是有符號整數類型，用於指針差值 */
typedef long ptrdiff_t;

/* 定義 wchar_t，用於寬字元 */
typedef unsigned short wchar_t;

/* 定義 NULL 為空指針常數 */
#ifndef NULL
#define NULL ((void *)0)
#endif

/* 定義 offsetof 宏，用於計算結構體成員的偏移量 */
#define offsetof(type, member) ((size_t)&(((type *)0)->member))

#endif /* _STDDEF_H */