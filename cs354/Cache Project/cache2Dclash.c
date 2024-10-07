/*
* Name: Sidney Heberlein
*/

#define ROWS 128
#define COLS 8
#define CONST 100
int arr[ROWS][COLS];

int main()
{
  for (int col = 0; col < COLS; col++)
    for (int row = 0; row < ROWS; row += 64)
      for (int iteration = 0; iteration < CONST; iteration++)
      {
        arr[row][col] = iteration + row + col;
      }
}

