/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

static FILE* battleshipMy;
static FILE* battleshipOp;
static CellContent myContent[FIELDSIZE][FIELDSIZE];
static CellContent opContent[FIELDSIZE][FIELDSIZE];
static CellContent myGuess[FIELDSIZE][FIELDSIZE];

void load_game()
{
  battleshipMy = fopen("battleship.my", "r");
  battleshipOp = fopen("battleship.op", "r");

  fread(myContent,sizeof(myContent),FIELDSIZE,battleshipMy);
  fread(opContent,sizeof(opContent),FIELDSIZE,battleshipOp);

  for (int i = 0; i < FIELDSIZE; i++)
  {
    for (int j = 0; j < FIELDSIZE; j++)
    {
      myGuess[i][j] = Unknown;
    }
  }
}

CellContent get_shot(int row, int col)
{
  if (row >= FIELDSIZE || row < 0 || col >= FIELDSIZE || col < 0)
  {
    return OutOfRange;
  }
  return myContent[row][col];
}

bool shoot(int row, int col)
{
  if (row >= FIELDSIZE || row < 0 || col >= FIELDSIZE || col < 0)
  {
    return false;
  }
  if (opContent[row][col] == Boat)
  {
    myGuess[row][col] = Boat;
    Checkboarder(row-1,col-1);
    Checkboarder(row,col-1);
    Checkboarder(row-1,col);
    Checkboarder(row+1,col+1);
    Checkboarder(row,col+1);
    Checkboarder(row+1,col);
    Checkboarder(row+1,col-1);
    Checkboarder(row-1,col+1);
    return true;
  }
  myGuess[row][col] = Water;
  return true;
}

void Checkboarder(int row,int col)
{
  if (row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE)
  {
    return;
  }
  else
  {
    myGuess[row][col] = Water;
  }
}

CellContent get_my_guess(int row, int col)
{
  if (row >= FIELDSIZE || row < 0 || col >= FIELDSIZE || col < 0)
  {
    return OutOfRange;
  }
  return myGuess[row][col];
}
