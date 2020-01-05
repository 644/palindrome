#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	if(argc < 2) exit(EXIT_FAILURE);

	char *lineptr = NULL;
	ssize_t ssize, lpos, pal, len;
	size_t n = 0;
	FILE *stream;

	stream = fopen(argv[1], "r");
	if(stream == NULL) exit(EXIT_FAILURE);

	while((ssize = getline(&lineptr, &n, stream)) != -1){
		if(ssize < 4) continue;
		len=ssize-1;
		lineptr[len]=0;

		pal=1;
		for(lpos=0; lpos<(len/2); ++lpos){
			if(tolower(lineptr[lpos]) != tolower(lineptr[len-lpos-1])){
				pal=0;
				break;
			}
		}

		if(pal) printf("%s\n", lineptr);
	}

	fclose(stream);
	if(lineptr) free(lineptr);

	exit(EXIT_SUCCESS);
}
