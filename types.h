/* stolen from Eskil */
#if !defined(TYPES_H)
  #define TYPES_H

  #ifndef NULL
    #ifdef __cplusplus
      #define NULL 0
    #else
      #define NULL ((void *)0)
    #endif
  #endif

  #if !defined(TRUE)
    #define TRUE 1
  #endif

  #if !defined(FALSE)
    #define FALSE 0
  #endif

  #if defined _WIN32
    typedef unsigned int    uint;
  #else
    #include <sys/types.h>
  #endif

  #if !defined(VERSE_TYPES)
    typedef signed char     int8;
    typedef unsigned char   uint8;
    typedef signed short    int16;
    typedef unsigned short  uint16;
    typedef signed int      int32;
    typedef unsigned int    uint32;
    typedef float           real32;
    typedef double          real64;
    typedef unsigned char   boolean;
  #endif

  #if defined(_MSC_VER)
    typedef signed __int64      int64;
    typedef unsigned __int64    uint64;
  #elif defined(__GNUC__)
    typedef signed long long    int64;
    typedef unsigned long long  uint64;
  #else
    /* no 64-bit type available in strict C89 */
  #endif

  #define F_DOUBLE_PRECISION
  /* if F_DOUBLE_PRECISION is defined the type "freal" is defined as double otherwhise it will be defined as float. This is very usefull if you want to write an application that can be compiled to use either 32 or 64 bit floating point math. Forges entire match librarie are defined in both 32 and 64 bit precission and all functionality can be accessed using the freal type, a macro will replace all freal calls with the aropriate funtion using either 32 or 64 bit depending on if F_DOUBLE_PRECISION is defined*/

  #ifdef F_DOUBLE_PRECISION
    typedef double freal;
  #else
    typedef float  freal;
  #endif
#endif /* TYPES_H */
