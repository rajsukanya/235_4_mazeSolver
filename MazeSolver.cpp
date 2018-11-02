/*
Name: Sukanya Raj
File name: MazeSolver.cpp
Date: 11/6/18
Assignment: Project 4
Description: implementation of class MazeSolver
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "MazeSolver.h"
using namespace std;

/*Post: if input file cannot read outputs "Cannot read from input_file_name"
otherwise sets maze_rows_ and maze_columns from first two values in input file
and allocates two 2-dimensional array of size maze_rows_ and maze_columns
both maze_ and solution_ are initialized with characters read from input*/
MazeSolver::MazeSolver(string input_file)
{
  ifstream inStream;
  inStream.open(input_file);
  if(inStream.fail())
  {
    cout << "Cannot read from input file" <<endl;
    exit(1);
  }

  string line;
  int rows, cols;

  inStream >> rows >> cols;
  maze_rows_ = rows;
  maze_columns_ = cols;
  initializeMaze(rows, cols);
  fillMaze(inStream); 
  initializeSolution();
  maze_ready = true;

  inStream.close();
}

MazeSolver::~MazeSolver()
{
  for(int i = 0; i < maze_rows_; i++)
  {
    delete[] maze_[i];
    delete[] solution_[i];
  }
  delete[] maze_;
  delete[] solution_;
}


bool MazeSolver::mazeIsReady() //called by main
{
  return maze_ready;
}

bool MazeSolver::solveMaze() //called by main
{
  Position current_pos = backtrack_stack_.top();

  while(!backtrack_stack_.empty()) 
  {
    if(solution_[current_pos.row][current_pos.column] == '$')
    {
      cout << "Found the exit!!!" << endl;
      return true;
    }
    else if(extendPath(current_pos))
    {
      solution_[current_pos.row][current_pos.column] = '>';
      current_pos = backtrack_stack_.top(); 
    }
    else 
    {
      maze_[current_pos.row][current_pos.column] = 'X';
      solution_[current_pos.row][current_pos.column] = '@';
      backtrack_stack_.pop(); //BACKTRACK STEP
      if(!backtrack_stack_.empty())
      {
        current_pos = backtrack_stack_.top(); 
      }
      else 
      {
        cout << "This maze has no solution." << endl;
        return false;
      }
    }
  }
  return true;
}

void MazeSolver::printSolution() //called by main
{  
  cout << "The solution to this maze is:" << endl;

  for(int i = 0; i < maze_rows_; i++)
  {
    for(int j = 0; j < maze_columns_; j++)
    {
      cout << solution_[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
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
  for(int i = 0; i < maze_rows_; i++)
  {
    for(int j = 0; j < maze_columns_; j++)
    {
      input_stream >> maze_[i][j];
    }
  }
}

void MazeSolver::initializeSolution() //called by constructor
{
  copyMazetoSolution();
  Position start_pos; 
  start_pos.row = 0;
  start_pos.column = 0; 

  backtrack_stack_.push(start_pos);
  if(extendPath(start_pos))
  {
   solution_[0][0] = '>';
  }

}

void MazeSolver::copyMazetoSolution() //called by initializeSolution
{  
  solution_ = new char*[maze_rows_];
  for(int i = 0; i < maze_rows_; i++)
  {
     solution_[i] = new char[maze_columns_];
  }
 
  for(int i = 0; i < maze_rows_; ++i)
  {
    for(int j = 0; j < maze_columns_; ++j)
    {
      solution_[i][j] = maze_[i][j];
    }
  }
}

bool MazeSolver::extendPath(Position current_position) //called by solveMaze()
{ 
  Position new_position; 
  bool extended = false;

  if(isExtensible(current_position, SOUTH))
  {
    new_position = getNewPosition(current_position, SOUTH);
    backtrack_stack_.push(new_position);
    extended = true;
  }
  if(isExtensible(current_position, EAST))
  {
    new_position = getNewPosition(current_position, EAST);
    backtrack_stack_.push(new_position);
    extended = true;
  }
  return extended;
}

Position MazeSolver::getNewPosition(Position old_position, direction dir) //called by extendPath()
{
  Position new_position;

  if(dir == SOUTH)
  {
    new_position.row = old_position.row+1;
    new_position.column = old_position.column;
  }
  else if(dir == EAST)
  {
    new_position.column = old_position.column+1;
    new_position.row = old_position.row;
  }
  return new_position; 
}

bool MazeSolver::isExtensible(Position current_position, direction dir) //called by extendPath()
{ 
  if(dir == SOUTH)
  {
    if(current_position.row < maze_rows_-1 && ((maze_[current_position.row+1][current_position.column] == '_') || (maze_[current_position.row+1][current_position.column] == '$')))
    {
      return true;
    }
  }
  else if(dir == EAST)
  {
    if(current_position.column < maze_columns_-1 && ((maze_[current_position.row][current_position.column+1] == '_') || (maze_[current_position.row][current_position.column+1] == '$')))
    {
      return true;
    }
  }
  return false;
}
