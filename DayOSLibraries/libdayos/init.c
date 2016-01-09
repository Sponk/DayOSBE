
extern void InitHeap();
extern void init_signals();

void init_libdayos()
{
	InitHeap();
	init_signals();
}