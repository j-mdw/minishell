#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string.h>

// char		*first_read(char *str);
char *param_trim(char *raw_param);

int main(){
	char *toto, *tata;

	toto = "aoe$$1_u#$oe;";
	printf("%s\n", (tata = param_trim(toto)));
	free(tata);
	return (0);
}

// int first_read_main (){
// 	char *c;
// 	char *entry;

// 	entry = strdup("a|");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("|");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("a|a");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("|a");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup(";");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("<");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 		entry = strdup(">");
// 		c = first_read(entry);
// 		printf("%s\n", c);
// 		free(entry);

// 	entry = strdup(">>");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("<a");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup(">a");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup(">>a");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup(">;");// nothing before redir
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("echo \"toto > toto\"");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("ls \"| grep t");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("ls \"| grep t\"");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("ls \"/\" | sort -r");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

// 	entry = strdup("ls '/tmp' ;");
// 	c = first_read(entry);
// 	printf("%s\n", c);
// 	free(entry);

	// entry = strdup("a|a");
	// c = first_read(entry);
	// printf("%s\n", c);
	// free(entry);

// 	return 0;
// }
