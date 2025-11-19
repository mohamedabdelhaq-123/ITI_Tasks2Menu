


#ifndef TYPES_H
#define TYPES_H



/*==========================================================
 *  Integer Types
 *==========================================================*/

// 8-bit types
typedef signed char        s8;
typedef unsigned char      u8;

// 16-bit types
typedef signed short int   s16;
typedef unsigned short int u16;

// 32-bit types
typedef signed int         s32;
typedef unsigned int       u32;

// 64-bit types
typedef signed long long   s64;
typedef unsigned long long u64;

// Standard floating-point types
typedef float              f32;   // 32-bit float
typedef double             f64;   // 64-bit double
typedef long double        f128;  // 80–128-bit (depending on compiler)

// Generic short/long aliases
typedef signed short       short_t;
typedef unsigned short     ushort_t;
typedef signed long        long_t;
typedef unsigned long      ulong_t;



typedef unsigned char      bool_t;
#define TRUE  1
#define FALSE 0


enum Color {
    RED = 31,
    GREEN = 32,
    BLUE = 34
};

////////////////////////////////////////////////////////Configuration///////////////////////////////////////////////

#define InitRowValue 0
#define InitColumnValue 0
#define InitColor RED
#define InitDelay 3








#endif
