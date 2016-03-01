#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc < 2)
		return 0;
 
	FILE* f = fopen(argv[1], "w");

	if(!f)
	{
		perror("Could not open file!");
		return 1;
	}
	
	for(int i = 2; i < argc; i++)
		//fwrite(argv[i], strlen(argv[i]), 1, f);
		fprintf(f, "%s\n", argv[i]);

	fflush(f);
	fclose(f);
	
	return 0;
}
