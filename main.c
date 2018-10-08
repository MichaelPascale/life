/* Conway's Game of Life
 * Implementation by Michael Pascale in March 2018
 * 
 * Rules:
 * 	1) A live cell with fewer than two live neighbors dies.
 * 	2) A live cell with more than three live neighbors also dies.
 * 	3) A live cell with exactly two or three neighbors lives.
 * 	4) A dead cell with exactly three live neighbors becomes alive.
 */

#define Y_SIZE	25
#define	X_SIZE	95

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"

int main(int argc, char** argv) {
	
	int generations;													// Input variables.
	char filename[30];
	int** world = NULL;													// Pointer to an integer array containing the world.
	srand(time(NULL));
	
	printf("World File to Load (Blank for None): ");					// Determine if world file is to be loaded and initialize the world.
	
	fgets(filename, 30, stdin);
	
	if(*filename == '\n')
		world = initialize_world();
	else
		world = init_from_file(filename);
		
	if(world == NULL) {													// Check if world initialization failed.
		printf("There was an error initializing the world.");
		return 1;
	}
	
	printf("World Initialized!\n");
	printf("Generations (Blank for Infinite): ");											// Run the number of generations specified by the user.
	scanf("%d", &generations);
	
	for(int i = 0; i < i +1; i++) {
		next_generation(world);
		display(world);
		sleep(1);
	}
	
	free(world);
	return 0;
}

// World Initialization
int** initialize_world() {
	
	printf("Initializing World...\n");
	
	int num[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	
	int** world = malloc(Y_SIZE * sizeof(int*));
	
	if (world == NULL)
		return NULL;
		
	for (int y = 0; y < Y_SIZE; y++) {
		
		world[y] = malloc(X_SIZE * sizeof(int));
		
		if (world[y] == NULL) {
			for(int i = 0; i < y; i++)
				free(world[i]);
			free(world);
			return NULL;
		}
	}
	
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			
			world[y][x] = num[rand() % 15];
			
		}
	}
		
	return world;
}

int** init_from_file(char* filename) {
	printf("initialize_from_file() is a stub!\n");
	return NULL;
}

// Determine the number of neighbors a cell has. 
int neighbors(int x, int y, int** world) {
	
	int number = 0;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (   (y != 0 && y != Y_SIZE - 1) ? (world[y - 1 + i][x - 1 + j] == 1) :   0)
				number++;
	
	if (world[y][x] == 1)		// Don't count the cell itself if it is alive.
		number--;

	return number;
}

// Determine the next state of a cell. Returns 1 for alive, 0 for dead.
/*	1) A live cell with fewer than two live neighbors dies.
 * 	2) A live cell with more than three live neighbors also dies.
 * 	3) A live cell with exactly two or three neighbors lives.
 * 	4) A dead cell with exactly three live neighbors becomes alive.
 */
 
int next_state(int x, int y, int** world) {
	int number = neighbors(x, y, world);
	int state = world[y][x];
	
	if (state == 1) {
		if (number < 2 || number > 3) return 0;
		if (number == 2 || number == 3) return 1;
	}
	
	if (number == 3) return 1;
	
	return 0;
}

// Simulate the next generation of cells.
void next_generation(int** world) {
	
	for (int i = 0; i < Y_SIZE; i++) {
		for (int j = 0; j < X_SIZE; j++) {
			world[i][j] = next_state(j, i, world);
		}
	}
	
	return;
}

// Display the array.
void display(int** world) {
	
	for (int i = 0; i < X_SIZE; i++)
		printf("-");
	
	printf("\n");
	
	for (int i = 0; i < Y_SIZE; i++) {
		for (int j = 0; j < X_SIZE; j++) {
			
			//printf("%d ", world[i][j]);
			if (world[i][j] == 0)
				printf(" ");
				
			else printf("%%");
		}
		printf("\n");
	}
	
	return;
}
