#include <stdio.h>

int count_floors(const char *fname) {
	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		perror("Error opening the file.");
		return 0;	
	}

	int ch;
	int total = 0;
	while ((ch = fgetc(f)) != EOF) {
		if (ch == '(') {
			total += 1;
		}
		else if (ch == ')') {
			total -= 1;
		}
	}

	if (ferror(f)) {
		perror("Error reading file.\n");
		fclose(f);
		return 0;
	} 

	fclose(f);
	return total;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Enter a .txt file to parse.\n");
	}
	int result = count_floors(argv[1]);
	printf("Floors: %d\n", result);
	return 0;
}
