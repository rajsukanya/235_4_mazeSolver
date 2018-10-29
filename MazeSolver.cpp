#include <fstream>
#include <iostream>
#include <cstdlib>
#include "MazeSolver.h"
using namespace std;

MazeSolver::MazeSolver(string input_file)
{
  ifstream inStream;
  inStream.open("inputA");
  if(inStream.fail())
  {
    cout << "Cannot read from inputA" <<endl;
    exit(1);
  }

  string line;
  int rows, cols;

  while(inStream >> rows >> cols)
  {
    maze_rows_ = rows;
    maze_columns_ = cols;
    cout << "ROWS: " << rows <<endl;
    cout << "COLUMNS: " << cols <<endl;
    initializeMaze(rows, cols);
  }
  inStream.close();
  //cout << "PARAMETERIZED CONSTRUCTOR" <<endl;
}

MazeSolver::~MazeSolver()
{  
  cout << "DESTRUCTOR" <<endl;
}


bool MazeSolver::mazeIsReady()
{  
  cout << "MAZE IS READY" <<endl;
}

bool MazeSolver::solveMaze()
{  
  cout << "SOLVE MAZE" <<endl;
}

void MazeSolver::printSolution()
{  
  cout << "PRINT SOLUTION" <<endl;
}

//Private Member Functions (helper functions) :

void MazeSolver::initializeMaze(int rows, int columns) //called by constructor
{  
  maze_ = new char*[rows];

  for(int i = 0; i < rows; i++)
  {
    maze_[i] = new char[columns];
  }
}

void MazeSolver::fillMaze(ifstream& input_stream) //called by constructor
{
  char character;

  while(input_stream >> character)
  {
    for(int i = 0; i < maze_rows_; i++)
    {
      for(int j = 0; j < maze_columns_; j++)
        cout << character;
    }
  }
}

void MazeSolver::initializeSolution() //called by constructor
{
  copyMazetoSolution();

  for(int i = 0; i < maze_rows_; i++)
  {
    for(int j = 0; j < maze_columns_; j++)
    {
    }
  }
}

void MazeSolver::copyMazetoSolution() //called by initializeSolution
{  
  solution_ = new char*[maze_rows_];

  for(int i = 0; i < maze_rows_; i++)
  {
    solution_[i] = new char[maze_columns_];
    for(int j = 0; i < maze_columns_; j++)
    {
      solution_[i][j] = maze_[i][j];
    }
  }
}

bool MazeSolver::extendPath(Position current_position)
{  
  cout << "EXTEND PATH" <<endl;
}

Position MazeSolver::getNewPosition(Position old_position, direction dir)
{  
  cout << "GET NEW POSITION" <<endl;
}

bool MazeSolver::isExtensible(Position current_position, direction dir)
{  
  cout << "IS EXTENSIBLE" <<endl;
}
