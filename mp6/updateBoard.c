// partners: aryana9, sureban2, sanjayb3

// Our code uses 3 different function to implement the game of life.

/*
 * countLiveNeighbor: The countLiveNeighbor function iterates through a 1D array that represents a 2D array. For a given cell, it looks at all the cells adjacent to it
and checks if they are alive or not and then returns the total number of adjacent cells that are alive. 
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

 int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int live = 0; // number of alive neighbors
    for(int r = row - 1; r <= row + 1; r++){ // nested for loop going through columns first then rows
        if(r >= 0 && r < boardRowSize){ // checking if row is within row borders
            for(int c = col - 1; c <= col + 1; c++){
                if(c >= 0 && c < boardColSize){ // checking if col is within column borders
                    if(!(r == row && c == col)){ // skipping the cell itself to not count itself as a live neighbour
                        if(board[r * boardColSize + c] == 1){ // if neighbour is alive, then increment number of alive neighbours
                            live++;
                        }
                    }
                }
            }
        }
    }
    return live;
}

/*
 * updateBoard: The updateBoard function will first make a copy of the existing game board and then update the board based the rules of the game. 
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    // Create a copy of the original board to avoid modifying it while updating
    int origBoard[boardRowSize * boardColSize];
    
    // Copy the original board values into origBoard
    for(int i = 0; i < boardRowSize * boardColSize; i++) {
        origBoard[i] = board[i];
    }
    
    // Iterate through each cell in the board
    for(int r = 0; r < boardRowSize; r++) {
        for(int c = 0; c < boardColSize; c++) {
            // Check if the current cell is alive
            if(origBoard[r * boardColSize + c] == 1) {
                // Count the number of live neighbors
                int liveNeighbors = countLiveNeighbor(origBoard, boardRowSize, boardColSize, r, c);
                
                // If the live cell does not have exactly 2 or 3 neighbors, it dies
                if(liveNeighbors != 2 && liveNeighbors != 3) {
                    board[r * boardColSize + c] = 0; // Cell dies
                }
            } 
            else {
                // If the current cell is dead and has exactly 3 live neighbors, it becomes alive
                if(countLiveNeighbor(origBoard, boardRowSize, boardColSize, r, c) == 3) {
                    board[r * boardColSize + c] = 1; // Cell becomes alive
                }
            }
        }
    }
}


/*
 * aliveStable: the aliveStable checks if the board has changed at all after the update, returning a 1 if the state is stable and 0 if there has been a change.
 If the board has not changed, that means a stable state has been found and the program can terminate. 
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same
 * as the current step.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int newBoard[boardRowSize * boardColSize];
    for(int i = 0; i < boardRowSize * boardColSize; i++){
        newBoard[i] = board[i]; // make a copy of board
    }

    updateBoard(newBoard, boardRowSize, boardColSize); // update the copy

    for(int j = 0; j < boardRowSize * boardColSize; j++){ // for loop to check if the updated board mathches the original board
        if (newBoard[j] != board[j]){ // if an element in the updated board doesn't match that same index's element in the original board, then return 0
            return 0;
        }
    }
    return 1; // 
}