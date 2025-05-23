#include <stdio.h>


int find_position(char *fname) {
	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		perror("Error opening the file.");
		return 0;
	}

	int ch;
	int i = 0;
	int total = 0;
	while ((ch = fgetc(f)) != EOF) {
		if (ch == '(') {
			total += 1;
		}
		else if (ch == ')') {
			total -= 1;
		}
		i++;
		if (total == -1) {
			return i;
		}
	}

	if (ferror(f)) {
		perror("Error reading the file.");
		fclose(f);
		return 0;
	}

	return 0;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Please enter a .txt file to parse.\n");
		return 0;
	}
	int result = find_position(argv[1]);
	printf("Position: %d\n", result);
	return 0;
}
