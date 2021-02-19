#include <stdio.h>
#include <string.h>

#define DEST_SIZE 40

int main()
{
	char *src[] = {"ok","ok"};
	char dest[DEST_SIZE] = "Unimaginable";
     strcpy(dest,src[0]);


	printf("%s",dest);

	return 0;
}
