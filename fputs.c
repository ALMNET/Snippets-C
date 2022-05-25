#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE	   *inp, *out;
	char	     line[128];

	if(argc != 3) {
		printf("usage: copys source_file target_file\n");
		return 1;
	}

	if((inp = fopen(argv[1],"rt")) == NULL) {
		printf("Cannot open %s\n", argv[1]);
		return 2;
	}
	if((out = fopen(argv[2],"wt")) == NULL) {
		printf("Cannot create %s\n", argv[2]);
		fclose(inp);
		return 3;
	}
	while((fgets(line,sizeof(line),inp)) != NULL)
		if(fputs(line,out) == EOF)
			break;
	fclose(inp);
	fclose(out);
	return 0;
}