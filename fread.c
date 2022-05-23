#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE			*inp;
	unsigned char		buffer[1024]; /* 1 kilobyte */
	int			i, read;

	if(argc != 2) {
		printf("usage: show3 file_name\n");
		return 1;
	}
	if((inp = fopen(argv[1],"rb")) == NULL) {
		printf("Cannot open the file %s\n", argv[1]);
		return 2;
	}
	do {
		read = fread(buffer,1,sizeof(buffer),inp);
		for(i = 0; i < read; i++)
			printf("%02X",buffer[i]);
	} while (read > 0);
	fclose(inp);
	return 0;
}