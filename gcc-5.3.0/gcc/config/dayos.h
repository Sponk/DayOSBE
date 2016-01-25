#undef TARGET_DAYOS
#define TARGET_DAYOS 1
 
#define LIB_SPEC "-ldayos -lm" // -lg" /* link against C standard libraries */
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
  
#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{!shared: %{!symbolic: %{pg:gcrt0.o%s}%{!pg:%{p:mcrt0.o%s}%{!p:crt0.o%s}}}} crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

//#undef STANDARD_STARTFILE_PREFIX
//#define STANDARD_STARTFILE_PREFIX "/lib/"
  
/*#ifdef HAVE_INITFINI_ARRAY_SUPPORT

#define USE_INITFINI_ARRAY

#undef INIT_SECTION_ASM_OP
#undef FINI_SECTION_ASM_OP

#undef INIT_ARRAY_SECTION_ASM_OP
#define INIT_ARRAY_SECTION_ASM_OP

#undef FINI_ARRAY_SECTION_ASM_OP
#define FINI_ARRAY_SECTION_ASM_OP

#undef TARGET_ASM_CONSTRUCTOR
#define TARGET_ASM_CONSTRUCTOR default_elf_init_array_asm_out_constructor
#undef TARGET_ASM_DESTRUCTOR
#define TARGET_ASM_DESTRUCTOR default_elf_fini_array_asm_out_destructor

#endif*/
  
//#undef STANDARD_INCLUDE_DIR
//#define STANDARD_INCLUDE_DIR "/include"
