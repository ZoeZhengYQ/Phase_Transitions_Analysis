//
//  main.c
//  CSE_6010_A2_yzheng394
//
//  Created by Yingqiao Zheng on 9/22/18.
//  Copyright © 2018 Yingqiao Zheng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*  Functions */
int  **malloc_grid (int);
void free_grid (int, int **);
int  generate_grid (int, double, int **);
void print_grid (int, int **);


/*  The main function */
int main(int argc, const char * argv[]) {
    
    int    k = atoi(argv[1]);
    double p = atof(argv[2]);
    int    vertexNum = 0;
    int    **newGrid = NULL;
    FILE   *fp;
    
    srand((unsigned int)time(0));
    
    newGrid = malloc_grid(k);
    vertexNum = generate_grid(k, p, newGrid);
    // printf("vertex number: %d\n", vertexNum);
    // print_grid(k, newGrid);
    
    
    /* Write the grid to file */
    fp = fopen(argv[3], "w");
    fprintf(fp, "%d\n", vertexNum);
    
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (newGrid[i][j] >= 0) {
                fprintf(fp, "%d ", newGrid[i][j]);
                
                if ((i-1) >= 0 && newGrid[i-1][j] >= 0) {
                    fprintf(fp, "%d ", newGrid[i-1][j]);
                }
                if ((j-1) >= 0 && newGrid[i][j-1] >= 0) {
                    fprintf(fp, "%d ", newGrid[i][j-1]);
                }
                if ((i+1) < k && newGrid[i+1][j] >= 0) {
                    fprintf(fp, "%d ", newGrid[i+1][j]);
                }
                if ((j+1) < k && newGrid[i][j+1] >= 0) {
                    fprintf(fp, "%d ", newGrid[i][j+1]);
                }
                
                fprintf(fp, "\n");
            }
        }
    }
    
    fclose(fp);
    
    free_grid(k, newGrid);
    return 0;
}


/* Functions definition */

/*
 *  Create matrix with k*k size
 */
int **malloc_grid (int k) {
    int **grid = (int **) malloc(k * sizeof(int*));
    if (grid == NULL) {
        printf("\nMemory allocation for **mat failed. Abort.\n");
        return NULL;
    }
    
    for (int i = 0; i < k; ++i) {
        grid[i] = (int *) malloc(k * sizeof(int));
        if (grid[i] == NULL) {
            printf("\nMemory allocation for *mat[%d] failed. Abort.\n", i);
            return NULL;
        }
    }
    return grid;
}

/*
 *  Free memory allocated for grid
 */
void free_grid (int k, int **grid) {
    if (grid == NULL) {
        printf("Current grid is empty!");
        return;
    }
    for (int i = 0; i < k; ++i) { free(grid[i]); }
    free(grid);
    return;
}

/*
 *  Generate grid elements
 */
int generate_grid (int k, double p, int **grid) {
    int randNum = 0;
    int label = 0;
    
    if (grid == NULL) {
        printf("Unable to generate because grid is empty!");
        return 0;
    }
    
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            randNum = rand();
            if (randNum < (RAND_MAX * (1-p))) {
                grid[i][j] = -1;
            }
            else { grid[i][j] = label++; }
        }
    }
    return label;
}

/*
 *  Print grid
 */
void print_grid (int k, int **grid) {
    if (grid == NULL) {
        printf("Unable to print because grid is empty!");
        return;
    }
    
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            printf("  %d ", grid[i][j]);
        }
        printf("\n");
    }
    return;
}

