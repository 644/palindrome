#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <wctype.h>

int main(int argc, char *argv[])
{
	if(argc < 2) exit(EXIT_FAILURE);

	size_t n;
	ssize_t ssize;
	char *lineptr=NULL;
	FILE *stream;

	stream = fopen(argv[1], "r");
	if(stream == NULL) exit(EXIT_FAILURE);

	while((ssize = getline(&lineptr, &n, stream)) != -1){
		if(ssize < 3) continue;
		ssize_t len=ssize-1;
		lineptr[len]=0;

		for(ssize_t i=0, j=len-1; 0<j-i;){
			int8_t rc=1;
			char *lpos = lineptr+i;
			char *rpos = lineptr+j;
			uint32_t lchar, rchar=0;
			uint8_t l0 = lpos[0];
			uint8_t l1 = lpos[1];
			uint8_t l2 = lpos[2];
			uint8_t l3 = lpos[3];

			switch(l0 >> 4){
			case 15:
				i += 4;
				lchar = (l0 << 24) + (l1 << 16) + (l2 << 8) + l3;
				break;
			case 14:
				i += 3;
				lchar = (l0 << 16) + (l1 << 8) + l2;
				break;
			case 12:
				i += 2;
				lchar = (l0 << 8) + l1;
				break;
			default:
				i += 1;
				lchar = l0 << 0;
			}

			for(uint8_t ufr, mask, shift = 0; ; shift += 8){
				rchar += (uint8_t)*rpos << shift;
				for(ufr = 0, mask = 128; mask & (uint8_t)*rpos; mask >>= 1, ufr++) {}
				uint8_t zwz = (uint8_t)*rpos--;
				if(!(zwz >> 7) || ((ufr == rc) && (192 <= zwz))){
					break;
				}
				rc++;
			}
			j -= rc;

			if(iswupper(lchar)) lchar = lchar - 'A' + 'a';
			if(iswupper(rchar)) rchar = rchar - 'A' + 'a';

			if(lchar != rchar) goto end;
		}

		printf("%s\n", lineptr);
		end: continue;
	}

	fclose(stream);
	if(lineptr) free(lineptr);

	exit(EXIT_SUCCESS);
}
