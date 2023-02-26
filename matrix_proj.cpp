//ENGG 126
//Project 2: Matrix Multiplication Speed Test
//by: Iris Carson, Antonio Castro, and Joshua Kempis
//--------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

void randNumb(int size, int **array, int seed) //int &array)
{
  srand((unsigned) seed);
  
  // Allocate Random Generated Values to Array 
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      array[i][j] = rand() % 100; //range [0, 100]
    }
  }

  // Printing the 2D array
  cout<<"\n=====Generated Random Numbers====="<<endl;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout<<array[i][j]<<" ";
    }
	cout<<endl;
  }

}

void fileWrite(int size, int **A, int **B)
{
  ofstream fout;
  fout.open("matrix_checker.csv", ios::app); //append to prevent overwriting

  fout<<"Matrix A";
  for (int i = 0; i < size + 1; i++)
  {
    fout<<",";
  }
  fout<<"Matrix B \n";
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {  
      fout << A[i][j] << ",";
	}
	
	fout <<",";
	
    for (int k = 0; k < size; k++)
    {  
      fout << B[i][k] << ",";
	}	
	fout << "\n";
  }
}

void matrixMult(int size, int **A, int **B, int **C)
{
  // Initializing Elements of Array C to 0
  for(int i = 0; i < size; ++i)
  {
    for(int j = 0; j < size; ++j)
    {
      C[i][j]=0;
    }
  }

  // Multiplying Arrays A and B and Storing the Results in Array C
  for(int i = 0; i < size; ++i)
  {
    for(int j = 0; j < size; ++j)
    {
      for(int k = 0; k < size; ++k)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
  // Printing the Product of the Matrix Multiplication
  cout<<"\n=====Output Matrix====="<<endl;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout<<C[i][j]<<" ";
    }
	cout<<endl;
  }
}

void clearArray(int size, int **array)
{
  // Deallocate Stored memory
  for (int i = 0; i < size; i++) {
    delete[] array[i];
  }
  delete[] array;
}

int main()
{
  int matrixSize = 0;
  cout<<"Enter Matrix Size: ";
  cin >> matrixSize;
  
  // Initializing 2D Dynamic Arrays
  int ** A = new int * [matrixSize];
  int ** B = new int * [matrixSize];
  int ** C = new int * [matrixSize]; //resulting array
  
  for (int i = 0; i < matrixSize; i++)
  {
    A[i] = new int [matrixSize];
	B[i] = new int [matrixSize];
	C[i] = new int [matrixSize];
  }

  // Allocating Values to Arrays A and B
  srand((unsigned) time(NULL));
  int seedA = rand(); 
  int seedB = rand();
  
  randNumb(matrixSize, A, seedA);
  randNumb(matrixSize, B, seedB);
  
  // Printing the returned 2D array
  cout<<"\n=====Matrix A====="<<endl;
  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixSize; j++)
    {
      cout<<A[i][j]<<" ";
    }
	cout<<endl;
  }
  cout<<"\n=====Matrix B====="<<endl;
  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixSize; j++)
    {
      cout<<B[i][j]<<" ";
    }
	cout<<endl;
  }
  
  /*
  // Printing a value in the returned 2D array 
  cout<<"=========="<<endl;
  cout<<"value at row 3, column 4: "<< A[2][3]<<"&"<<B[2][3]<<endl;
  //array[row][column]
  */

  // Exporting Contents of Matrix A and B for Output Checking
  //fileWrite(matrixSize, A, B);
  
  // Performing Matrix Multiplication
  matrixMult(matrixSize, A, B, C);  
  
  return 0;
}