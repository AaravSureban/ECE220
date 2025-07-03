#include "sudoku.h"
// worked with sanjayb3, aryana9, sureban2
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/*
In this MP, the goal was to implement a Sudoku solver in C using a recursive backtracking algorithm. 
The implementation involved writing three helper functions to validate 
whether a number could be placed in a specific cell without violating Sudoku rules. is_val_in_row, is_val_in_col, 
and is_val_in_3x3_zone were implemented to check if a number already exists in the respective row, column, or 3x3 
sub-grid. These functions were then used in is_val_valid to determine if a number could be placed in a given cell. 
Finally, the solve_sudoku function was implemented to recursively fill the sudoku board, backtracking 
when a placed number led to an invalid board.
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);  // Ensure the row index is valid.

  // Iterate through each column in the row to check for the value.
  for(int n = 0; n < 9; n++) {
    if(val == sudoku[i][n]) {
      return 1;  // Value found in the row.
    }
  }
  
  return 0;  // Value not found in the row.
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9);  // Ensure the column index is valid.

  // Iterate through each row in the column to check for the value.
  for(int n = 0; n < 9; n++) {
    if(val == sudoku[n][j]) {
      return 1;  // Value found in the column.
    }
  }
  
  return 0;  // Value not found in the column.
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9);  // Ensure the row index is valid.

  // Calculate the starting row and column of the sub-grid.
  int x = i / 3;
  int y = j / 3;
  x *= 3;
  y *= 3;

  // Iterate through the 3x3 sub-grid to check for the value.
  for(int n = 0; n < 3; n++) {
    for(int o = 0; o < 3; o++) {
      if(val == sudoku[x + n][y + o]) {
        return 1;  // Value found in the sub-grid.
      }
    }
  }
  
  return 0;  // Value not found in the sub-grid.
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);  // Ensure the indices are valid.

  // Check if the value is valid in the row, column, and sub-grid.
  if(is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {
    return 0;  // Value is not valid.
  }
  return 1;  // Value is valid.
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int i, j;
  
  // Iterate through the grid to find an empty cell (value 0).
  for(int x = 0; x < 9; x++) {
    for(int y = 0; y < 9; y++) {
      if(sudoku[x][y] == 0) {
        i = x;
        j = y;
        // Try placing numbers 1-9 in the empty cell.
        for(int num = 1; num <= 9; num++) {
          if(is_val_valid(num, i, j, sudoku)) {
            sudoku[i][j] = num;  // Add number.
            if(solve_sudoku(sudoku)) {
              return 1;  // If the puzzle is solved, return true.
            }
            sudoku[i][j] = 0;  // Backtrack if the solution is not valid.
          }
        }
        return 0;  // No valid number found for this cell.
      }
    }
  }

  return 1;  // Sudoku is solved.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9]) {
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}