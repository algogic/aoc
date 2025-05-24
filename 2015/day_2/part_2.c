#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LEN 8
#define BUF_SIZE (INPUT_LEN + 2)    // 8 chars + newline + NULL
#define MIN(a, b) ( (a) <= (b) ? (a) : (b) )
#define MAX(a, b) ( (a) >= (b) ? (a) : (b) )

static inline unsigned int eval(unsigned int l, unsigned int w, unsigned int h) {
    unsigned int min_side = MIN(l, MIN(w, h));
    unsigned int max_side = MAX(l, MAX(w, h));
    unsigned int min2 = (l + w + h) - min_side - max_side;
    unsigned int feet_ribbon = ((min_side + min2) << 1) + (l * w * h);
    return feet_ribbon;
}

unsigned int surface_area(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (f == NULL) {
        perror("Error opening the file.");
        return 0;
    }

    char buf[BUF_SIZE];
    unsigned int total = 0;
    while (fgets(buf, BUF_SIZE, f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        char *dims_l = strtok(buf, "x");
        char *dims_w = strtok(NULL, "x");
        char *dims_h = strtok(NULL, "x");
        unsigned int l = atoi(dims_l);
        unsigned int w = atoi(dims_w);
        unsigned int h = atoi(dims_h);
        total += eval(l, w, h);
    }

    if (ferror(f)) {
        perror("Error reading the file.");
        fclose(f);
        return 0;
    }

    fclose(f);
    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Enter a .txt file for evaluation.\n");
        return 1;
    }
    unsigned int result = surface_area(argv[1]);
    printf("Wrapping Paper: %u\n", result);
    return 0;
}
