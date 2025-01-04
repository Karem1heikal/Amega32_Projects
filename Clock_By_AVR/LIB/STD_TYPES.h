#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short int u16;
typedef signed short int s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef float f32;
typedef double f64;
typedef union {
    struct
    {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    }bitaccess;
    u8 byteaccess;
}regist;
#define NULL 0
#define OK		0
#define NOTOK	1

#define NULL_POINTER 	2
#define BUSY_FUNC		3

#endif // STD_TYPES_H_
