#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

// Completed with aryana9, sanjayb3, sureban2

/*
In this MP, we created a maze solver using a recursive depth-first search (DFS) algorithm. We created four 
functions: `createMaze`, which reads a maze from a file and stores it in a dynamically allocated structure; 
`destroyMaze`, which frees all allocated memory; `printMaze`, which displays the maze in a human-readable format; 
and `solveMazeDFS`, which solves the maze recursively by exploring all possible paths from the start to the end. 
If a path is found, the solution cells are marked with '*' and visited dead-end cells are marked with '~'. We 
followed the project guidelines closely and tested the code with provided maze test cases to ensure correctness 
and safe memory allocation.
*/


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

maze_t * createMaze(char * fileName) {
    // Open maze file for reading
    FILE *maze_data = fopen(fileName, "r");
    // Allocate memory for maze structure
    maze_t *maze = (maze_t *)malloc(sizeof(maze_t)); 
     // Read maze dimensions
    fscanf(maze_data, "%d %d\n", &maze->width, &maze->height);
    // Allocate memory for rows
    maze->cells = (char **)malloc(maze->height * sizeof(char *));
    // Allocate memory for each row's cells
    for (int i = 0; i < maze->height; i++) {
        maze->cells[i] = (char *)malloc((maze->width + 1) * sizeof(char)); 
        for (int j = 0; j < maze->width; j++) {
            char cur;
            // Read individual characters
            if (fscanf(maze_data, "%c", &cur) == EOF) {
                fclose(maze_data);
                return NULL;
            }
            // Skip newline or carriage return characters
            while (cur == '\n' || cur == '\r') { 
                if (fscanf(maze_data, "%c", &cur) == EOF) break;
            }
            // Store cell character
            maze->cells[i][j] = cur;
            // Save positions of start and end points
            if (cur == 'S') {
                maze->startRow = i;
                maze->startColumn = j;
            } else if (cur == 'E') {
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        // Null-terminate each row
        maze->cells[i][maze->width] = '\0';
    }

    // Close file
    fclose(maze_data);
    // Return pointer to the maze structure
    return maze; 
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */

 void destroyMaze(maze_t * maze) {
    // Free memory for each row
    for (int i = 0; i < maze->height; i++) {
        free(maze->cells[i]); 
    }
    // Free memory for row pointers and maze
    free(maze->cells); 
    free(maze); 
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */

void printMaze(maze_t * maze) {
    // Print each row followed by a newline
    for (int i = 0; i < maze->height; i++) {
        printf("%s\n", maze->cells[i]);
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently being visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 

 int solveMazeDFS(maze_t * maze, int col, int row) {

    // Check if the current position is outside the maze
    if (row < 0 || row >= maze->height || col < 0 || col >= maze->width) {
        return 0;
    }

    // Check if the current cell is a wall or already visited
    if (maze->cells[row][col] == '%' || maze->cells[row][col] == '*') {
        return 0;
    }

    // Check if the current cell is the end point
    if (row == maze->endRow && col == maze->endColumn) {
        return 1;
    }

    char cur = maze->cells[row][col];

    // Mark current cell as part of the path unless it's the start or end point
    if (cur != 'S' && cur != 'E') {
        maze->cells[row][col] = '*';
    }

    // Recursively attempt to solve the maze in each direction
    if (solveMazeDFS(maze, col + 1, row) || // Right
        solveMazeDFS(maze, col, row + 1) || // Down
        solveMazeDFS(maze, col - 1, row) || // Left
        solveMazeDFS(maze, col, row - 1)) { // Up
        return 1;
    }

    // Mark cell as visited but not part of the solution if all directions fail
    if (cur != 'S' && cur != 'E') {
        maze->cells[row][col] = '~';
    }

    return 0;
}
