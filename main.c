#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string.h>

char		*first_read(char *str);

int main (){
	char *c;
	char *entry;

	entry = strdup("a|");
	c = first_read(entry);

	printf("%s\n", c);
	free(entry);
	system("leaks ./a.out");
	return 0;
}
