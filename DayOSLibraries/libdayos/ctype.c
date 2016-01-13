/*
int isspace(int x) { return (x == ' ' || x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r'); }
int isdigit(int x) { return (x >= '0' && x <= '9'); }
int isxdigit(int x) { return ((x >= 'A' && x <= 'F') && (x >= 'a' && x <= 'f') && (x >= '0' && x <= '9')); }
int isalpha(int x) { return (x >= 'A' && x <= 'z'); }
int toupper(int x) { return (x + 26); }
int tolower(int x) { return (x - 26); }
int isprint(int x) { return (x >= 0x1f || x == 0x7f); }
int isalnum(int x) { return (isdigit(x) || isalpha(x)); }

int iscntrl(int x) { return !isprint(x); }
int isgraph(int x) { return (isprint(x) && x != ' '); }

int isupper(int x) { return (x >= 'A' && x <= 'Z'); }
int islower(int x) { return (x >= 'a' && x <= 'z'); }
int ispunct(int x) { return (isgraph(x) && !isalnum(x)); }*/

#define INLINE
#include <ctype.h>