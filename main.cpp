#include <iostream>
#include "MazeSolver.h"

int main()
{
  MazeSolver solver("inputD");

  if(solver.mazeIsReady())
  {
    solver.solveMaze();
    solver.printSolution();
  }
  return 0;
}
