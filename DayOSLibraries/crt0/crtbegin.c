
// Constructors
typedef void (*constructor_t)();

// Im Linkerskript definiert
constructor_t start_ctors;
constructor_t end_ctors;

void run_constructors()
{
    for (constructor_t* i = &start_ctors; i != &end_ctors; ++i)
        (*i)();
} 

// Destructors
constructor_t start_dtors;
constructor_t end_dtors;

void run_destructors()
{
    for (constructor_t* i = &start_dtors; i != &end_dtors; ++i)
        (*i)();
} 

// Pure virtuals
/*void __cxa_pure_virtual()
{

}

void _Unwind_Resume()
{
	
}

void _Unwind_GetRegionStart()
{
	
}

void _Unwind_GetTextRelBase()
{
	
}

void _Unwind_GetDataRelBase()
{
	
}

void _Unwind_GetIP()
{
	
}

void _Unwind_Backtrace()
{
	
}

extern int printf(const char*, ...);
extern void exit(int c);

void _Unwind_RaiseException()
{
	printf("Exceptions are currently not supported by\n\n");
	printf("the DayOS system runtime. Terminating.\n");
	exit(-1);
}

void _Unwind_Resume_or_Rethrow()
{
	
}

void _Unwind_GetLanguageSpecificData()
{
	
}

void _Unwind_SetIP()
{
	
}

void _Unwind_SetGR()
{
	
}*/