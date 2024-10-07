/*
* Name: Sidney Heberlein
*/

#define ROWS 3000
#define COLS 500
int arr[ROWS][COLS];

int main() 
{
  for (int row = 0; row < ROWS; row++)
    for (int col = 0; col < COLS; col++)
    {
      arr[row][col] = row + col;
    }
}
