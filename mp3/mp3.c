#include <stdio.h>
#include <stdlib.h>
// sureban2, aryana9, sanjayb3
// This program prints out a row of the Pascal's Triangle based on user input. It uses an outer for loop to go through
// each column in the row, and an inner for loop to calcuate the value to be printed in each column. The variable row
// is used to store the row value being printed, and prod is used to store the value to be printed in each column.
int main()
{
  int row; //initialize row variable

  printf("Enter the row index: ");
  scanf("%d",&row);

  // Write your code here
  for(int i = 0; i <= row; i++) { //initialize loop to cycle through each column of triangle
    long prod = 1; //initialize value to be computed for each value in triangle
    for(int j = 1; j <= i; j++) { //initialize loop to compute prod
      prod = prod * (row - j + 1) / j; //compute prod based on loop values
    }
    printf("%lu ", prod); //print value
  }

  return 0;
}
