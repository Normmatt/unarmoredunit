#ifndef TYPES_H
#define TYPES_H

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed long int32_t;

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;

typedef volatile u8   vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile s8   vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;

/* define a function pointer type */
typedef void (*void_pointer)(void);
typedef void (*task_pointer)(u16);
typedef void (*task_pointer2)(u16, u16);

/* LSI-C Inline ASM */
#define ASM_DB(c) _asm_c("\tDB\t" _q_(__eval__(c)))
#define ASM_DW(c) _asm_c("\tDW\t" _q_(__eval__(c)))
#define ASM_DD(c) _asm_c("\tDD\t" _q_(__eval__(c)))

#endif