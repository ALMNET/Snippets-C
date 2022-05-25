#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE	*inp, *out;
	char 	buffer[16384]; /* 16 kilobytes */
	int	read, written;

	if(argc != 3) {
		printf("usage: copyw source_file target_file\n");
		return 1;
	}
	if((inp = fopen(argv[1],"rb")) == NULL) {
		printf("Cannot open %s\n", argv[1]);
		return 2;
	}
	if((out = fopen(argv[2],"wb")) == NULL) {
		printf("Cannot create %s\n", argv[2]);
		fclose(inp);
		return 3;
	}
	do {
		read = fread(buffer,1,sizeof(buffer),inp);
		if(read)
			written = fwrite(buffer,1,read,out);
	} while (read && written);
	fclose(inp);
	fclose(out);
	return 0;
}