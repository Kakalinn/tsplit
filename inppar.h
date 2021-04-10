#ifndef WRAPPER_INPPAR
#define WRAPPER_INPPAR
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int inppar_fetchs(int argc, char** argv, char* target, char* src)
{
	int i, j;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], target) == 0)
		{
			assert(i != argc - 1);
			i++;
			assert(strlen(argv[i]) < 1023);
			int sum = 0;
			for (j = 0; argv[i][j] != '\0'; j++) src[j] = argv[i][j];
			src[j] = '\0';
			return i;
		}
	}
	return 0;
}

int inppar_fetchi(int argc, char** argv, char* target, int64_t* src)
{
	int i, j;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], target) == 0)
		{
			assert(i != argc - 1);
			i++;
			int sum = 0;
			for (j = 0; argv[i][j] != '\0'; j++)
			{
				if (argv[i][j] < '0' || argv[i][j] > '9')
				{
					printf("error: '%s' is an illegal parameter becuase '%s' is a number flag.\n", argv[i], target);
					exit(33);
				}
				sum = (sum << 1) + (sum << 3) + argv[i][j] - '0';
			}
			*src = sum;
			return i;
		}
	}
	return 0;
}

int inppar_fetchb(int argc, char** argv, char* target, int* src)
{
	int i, j;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], target) == 0)
		{
			*src = 1;
			return i;
		}
	}
	*src = 0;
	return 0;
}

















#endif
