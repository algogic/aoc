#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))


typedef struct {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
} Dimensions;


void calculate_dimensions(FILE *f, Dimensions *santa, Dimensions *robo) {
     int santa_x = 0, santa_y =0;
     int min_santa_x = 0, max_santa_x = 0;
     int min_santa_y = 0, max_santa_y = 0;
     int robo_x = 0, robo_y = 0;
     int min_robo_x = 0, max_robo_x = 0;
     int min_robo_y = 0, max_robo_y = 0;
     int i = 0;
     int ch;

     while ((ch = fgetc(f)) != EOF) {
        if (i % 2 == 0) {
            switch (ch) {
                case '<': robo_x--; break;
                case '>': robo_x++; break;
                case 'v': robo_y--; break;
                case '^': robo_y++; break;
                default : continue;
            }

            if (robo_x > max_robo_x) max_robo_x = robo_x;
            if (robo_x < min_robo_x) min_robo_x = robo_x;
            if (robo_y > max_robo_y) max_robo_y = robo_y;
            if (robo_y < min_robo_y) min_robo_y = robo_y;
        }    
        else {
            switch (ch) {
                case '<': santa_x--; break;
                case '>': santa_x++; break;
                case 'v': santa_y--; break;
                case '^': santa_y++; break;
                default : continue;
            }

            if (santa_x > max_santa_x) max_santa_x = santa_x;
            if (santa_x < min_santa_x) min_santa_x = santa_x;
            if (santa_y > max_santa_y) max_santa_y = santa_y;
            if (santa_y < min_santa_y) min_santa_y = santa_y;
        }

        i++;
     }

     santa->min_x = min_santa_x;
     santa->max_x = max_santa_x;
     santa->min_y = min_santa_y;
     santa->max_y = max_santa_y;

     robo->min_x = min_robo_x;
     robo->max_x = max_robo_x;
     robo->min_y = min_robo_y;
     robo->max_y = max_robo_y;
}


unsigned count_presents(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (f == NULL) {
        perror("Error opening the .txt file.");
        return 0;
    }

    Dimensions *santa = malloc(sizeof *santa);
    Dimensions *robo = malloc(sizeof *robo);
    if (!santa || !robo) {
        perror("malloc");
        fclose(f);
        return 0;
    }

    calculate_dimensions(f, santa, robo);
    rewind(f);

    int min_x = MIN(santa->min_x, robo->min_x);
    int max_x = MAX(santa->max_x, robo->max_x);
    int min_y = MIN(santa->min_y, robo->min_y);
    int max_y = MAX(santa->max_y, robo->max_y);

    int height = max_y - min_y + 1;
    int width = max_x - min_x + 1;

    int *visited = calloc(height * width, sizeof *visited);
    if (visited == NULL) {
        perror("calloc");
        fclose(f);
        return 0;
    }
    
    unsigned num_houses = 0;
    int m_0 = 0 - min_x;
    int n_0 = 0 - min_y;
    visited[n_0 * width + m_0] = 1;
    num_houses++;
    
    int santa_x = 0, santa_y = 0;
    int robo_x = 0, robo_y = 0;
    int m = 0, n = 0;
    int i = 0;
    int ch, idx;
    while ((ch = fgetc(f)) != EOF) {
        if (i % 2 == 0) {
            switch (ch) {
                case '<': robo_x--; break;
                case '>': robo_x++; break;
                case 'v': robo_y--; break;
                case '^': robo_y++; break;
                default : continue;          
            }

            m = robo_x - min_x;
            n = robo_y - min_y;
            idx = n * width + m;
        }
        else {
            switch (ch) {
                case '<': santa_x--; break;
                case '>': santa_x++; break;
                case 'v': santa_y--; break;
                case '^': santa_y++; break;
                default : continue;
            }

            m = santa_x - min_x;
            n = santa_y - min_y;
            idx = n * width + m;
        }

        if (!visited[idx]) {
            visited[idx] = 1;
            num_houses++;
        }

        i++;
    }

    fclose(f);
    free(robo);
    free(santa);
    free(visited);
    return num_houses;
}


int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please add a .txt file for evaluation.\n");
        return 1;
    }

    unsigned result = count_presents(argv[1]);
    printf("Number of presents delivered: %u\n", result);
    
    return 0;
}
