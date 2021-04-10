#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void init_seperator_mask(int32_t* s, char* a)
{
	while (*a) s[*(a++)] = 1;
}

FILE* open_file(int64_t n, char* fn, char* ff)
{
	sprintf(ff, fn, n);
	return fopen(ff, "w");
}

void close_file(FILE* fp)
{
	fclose(fp);
}

/*
   The large file is read word for word.
   Word seperators are stored in the mask |s|.
   No word may be larger than |maxw|.
   The large file is split into smaller files, at most |m| bytes in size.
   No word may, therefore, be larger than |m|.
   It makes sense, for the above reason, to make |maxw| be the same as |m|.
   Most of the memory used is to store the word, so choosing a smaller |maxw| lessens the memory footprint.
*/
int main()
{
	int64_t m = 100000000, maxw = 100000000, mm = 0, ww = 0, fc = 0;
	int32_t s[256], i;
	char* w = malloc(maxw*sizeof(char));
	assert(w);
	char fn[] = "tsplit-file-%d.txt";
	char c, ff[strlen(fn) + 100]; // Only a problem if you splitting file into more than a 10^100 pieces.
	for (i = 0; i < 256; i++) s[i] = 0;
	init_seperator_mask(s, " \n");
	assert(s['\n']); // Maybe not required, but ok to start. All files should end with '\n' so this guarantees a final print.
	FILE* fp = open_file(++fc, fn, ff);
	assert(fp);
	for (c = getchar(); c != EOF; c = getchar())
	{
		w[ww++] = c;
		if (s[c] == 1)
		{ // Word has ended.
			if (m < ww + mm) close_file(fp), assert(fp = open_file(++fc, fn, ff)), mm = 0;
			w[ww] = '\0';
			fputs(w, fp);
			mm += ww, ww = 0;
		}
		if (fc > 10) break;
	}
	close_file(fp);
	free(w);
	assert(c == EOF);
	return 0;
}
