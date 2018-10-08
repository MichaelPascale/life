// World Initialization
int** initialize_world();
int** init_from_file(char* filename);

// Determine the number of neighbors a cell has. 
int neighbors(int x, int y, int** world);

// Determine the next state of a cell.
int next_state(int x, int y, int** world);

// Simulate the next generation of cells.
void next_generation(int** world);

// Display the array.
void display(int** world);
