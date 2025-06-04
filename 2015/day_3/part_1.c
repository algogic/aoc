#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
} Dimensions;

void calculate_dimensions(FILE *f, Dimensions *out) {
    int ch;
    int x = 0, y = 0;
    int max_x = 0, max_y = 0;
    int min_x = 0, min_y = 0;

    while ((ch = fgetc(f)) != EOF) {
        switch (ch) {
            case '<': x--; break;
            case '>': x++; break;
            case 'v': y--; break;
            case '^': y++; break;
            default: continue;
        }

        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
        if (x < min_x) min_x = x;
        if (y < min_y) min_y = y;
    }

    out->min_x = min_x;
    out->max_x = max_x;
    out->min_y = min_y;
    out->max_y = max_y;
}

int count_houses(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (f == NULL) {
        perror("Error opening the file.");
        return 0;
    }

    Dimensions dim;
    calculate_dimensions(f, &dim);
    rewind(f);

    int width = dim.max_x - dim.min_x + 1;
    int height = dim.max_y - dim.min_y + 1;
    int *visited = calloc(height * width, sizeof *visited);
    if (visited == NULL) {
        perror("calloc");
        fclose(f);
        return 0;
    }  

    int houses_visited = 0;
    int i_0 = 0 - dim.min_x;
    int j_0 = 0 - dim.min_y;
    visited[j_0 * width + i_0] = 1;
    houses_visited++;

    int x = 0, y = 0;
    int i = 0, j = 0;
    int idx = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        switch (ch) {
            case '<': x--; break;
            case '>': x++; break;
            case 'v': y--; break;
            case '^': y++; break;
            default: continue;
        }
        
        i = x - dim.min_x;
        j = y - dim.min_y;
        idx = j * width + i;

        if (!visited[idx]) {
            visited[idx] = 1;
            houses_visited++;
        }
    }
    
    free(visited);
    fclose(f);
    return houses_visited;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Enter a .txt file for evaluation.\n");
        return 1;
    }
    int result = count_houses(argv[1]);
    printf("Houses visited: %d\n", result);
    return 0;
}
