#undef TARGET_DAYOS
#define TARGET_DAYOS 1
 
#define LIB_SPEC "-ldayos -lm -lgcc" // -lg" /* link against C standard libraries */
                               /* modify this based on your needs */
 
/* Don't automatically add extern "C" { } around header files. */
#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C 1
 
/* Additional predefined macros. */
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__dayos__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=dayos");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);
  
//#undef STANDARD_STARTFILE_PREFIX
//#define STANDARD_STARTFILE_PREFIX "/usr/lib/"
  
//#undef STANDARD_INCLUDE_DIR
//#define STANDARD_INCLUDE_DIR "/include"