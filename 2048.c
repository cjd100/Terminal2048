#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macro for length
#define L 4

int grid[L][L] = {0}; //global integer 4x4 grid
int changed = 0;

//now random
void place_nums()
{
  //places to put
  int first = rand() % L;
  int second = rand() % L;

  //choose 2 or 4
  int chance = rand() % 2; // will be 0 or 1
  //use bitwise ops
  //need a while loop here
  while (grid[first][second])
  {
    first = rand() % L;
    second = rand() % L;
  }
  int x = chance ? 2 : 4;

  grid[first][second] = x;
}

void print_grid()
{
  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < L; j++)
    {
      printf("%d", grid[i][j]);
    }
    printf("\n");
  }
}

void welcome()
{
  printf("Welcome User!\n");
  printf("Controls:\n w=up,\n a=left,\n s=down,\n d=right.\n 'q' to quit.");
}

void rotate_left()
{
  int copy[L][L] = {0};
  //copy the grid
  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < L; j++)
    {
      copy[i][j] = grid[i][j];
    }
  }

  //rotate the grid
  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < L; j++)
    {
      grid[L - j - 1][i] = copy[i][j];
    }
  }
}

void rotate_right()
{
  int copy[L][L] = {0};

  //copy the grid
  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < L; j++)
    {
      copy[i][j] = grid[i][j];
    }
  }

  //rotate the grid right
  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < L; j++)
    {
      grid[i][j] = copy[L - 1 - j][i];
    }
  }
}

void dezero(int row[])
{
  int copy[L];
  //copy the grid
  for (int i = 0; i < L; i++)
  {
    copy[i] = row[i];
    row[i] = 0;
  }

  int place = 0;
  //copy all non zeroes back to row
  for (int i = 0; i < L; i++)
  {
    if (copy[i])
    {
      row[place] = copy[i];
      place++;
    }
  }
}

void merge_dups(int row[])
{
  //scan left to right looking for dupes
  for (int i = 0; i < L - 1; i++)
  {
    //check if same
    if (row[i] == row[i + 1])
    {
      row[i] *= 2;
      row[i + 1] = 0;
      i++;
    }
  }
}

void shift_left()
{
  //copy memory of grid
  int copy[L][L];
  *memcpy(copy, grid, (L * L * 4));
  for (int r = 0; r < L; r++)
  {
    dezero(grid[r]);
    merge_dups(grid[r]);
    dezero(grid[r]);
  }
  if (memcmp(grid, copy, (L * L * 4)))
  {
    changed = 1;
  }
  else
  {
    changed = 0;
  }
}
/*
void shift_row_left()
{
  dezero_left();
  merge_dups();
  dezero_left();
}*/

/*
void dezero_right(int[] row)
{
  for (int i = (L - 1); i <= 0; i--)
  {
    if (row[i] == 0)
    {
      for (int j = (L - 1); j <= 0; j--)
      {
        if (row[j] != 0)
        {
          row[i] = row[j];
          row[j] == 0;
        }
      }
    }
  }
}
*/

char process_cmd(char c)
{
  switch (c)
  {
  case ('w'):
    rotate_left();
    shift_left();
    rotate_right();
    break;

  case ('a'):
    shift_left();
    break;

  case ('s'):
    rotate_right();
    shift_left();
    rotate_left();
    break;

  case ('d'):
    rotate_left();
    rotate_left();
    shift_left();
    rotate_right();
    rotate_right();
    break;
  }
}

int main()
{
  print_grid();
  printf("\n");
  place_nums();
  place_nums();
  print_grid();
  printf("\n");
  welcome();

  //while loop until game quit
  char c;
  while ((c = getchar()) != 'q')
  { //get command from user
    c = getchar();
    getchar(); //just flush out the /n
    process_cmd(c);
    if (changed)
    {
      place_nums();
    }
    print_grid();
  }
  return EXIT_SUCCESS;
}
