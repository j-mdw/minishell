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

	entry = strdup("|");
	c = first_read(entry);
	printf("%s\n", c);
	free(entry);

	entry = strdup("");
	c = first_read(entry);
	printf("%s\n", c);
	free(entry);

	entry = strdup("a|a");
	c = first_read(entry);
	printf("%s\n", c);
	free(entry);

	return 0;
}
