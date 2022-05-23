#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *inp;
	char line[128];
	if(argc != 2) {
		printf("usage: show2 file_name\n");
		return 1;
	}
	if((inp = fopen(argv[1],"rt")) == NULL) {
		printf("Cannot open the file %s\n", argv[1]);
		return 2;
	}
	while((fgets(line,sizeof(line),inp)) != NULL)
		printf("%s",line);
	fclose(inp);
	return 0;
}