#include "output.h"



void output_to_stdout(const char* format) {
	printf("%s\n", format);
}


int output_to_file(const char* filename, const char* format) {
	FILE* file = fopen(filename, "w");

	if (file == NULL)
		return -1;

	fprintf(file, "%s\n", format);

	fclose(file);

	return 0;
}

