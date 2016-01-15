extern int main(int argc, char* argv[]);
extern char** init_libdayos(int* argc);
extern void _init();
extern void _fini();
extern void exit(int val);

void _start()
{
	int argc;
	char** argv = init_libdayos(&argc);
	
	_init();
	int retval = main(argc, argv);
	_fini();
	
	exit(retval);
}

