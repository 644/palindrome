#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	if(argc < 2) exit(EXIT_FAILURE);

	size_t n;
	ssize_t ssize, len, lpos;
	int lchar, rchar;
	char *lineptr=NULL;
	FILE *stream;

	stream = fopen(argv[1], "r");
	if(stream == NULL) exit(EXIT_FAILURE);

	while((ssize = getline(&lineptr, &n, stream)) != -1){
		if(ssize < 4) continue;

		lpos=0, len=ssize-1, lineptr[len]=0;

		while(len > lpos){
			lchar=tolower(lineptr[lpos++]);
			rchar=tolower(lineptr[--len]);
			if(lchar != rchar) goto end;
		}

		printf("%s\n", lineptr);
		end: continue;
	}

	fclose(stream);
	if(lineptr) free(lineptr);

	exit(EXIT_SUCCESS);
}
