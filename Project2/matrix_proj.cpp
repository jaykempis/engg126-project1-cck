//ENGG 126
//Project 2: Matrix Multiplication Speed Test
//by: Iris Carson, Antonio Castro, and Joshua Kempis
//--------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

void randNumb(int row, int col, int **array, int seed)
{
  srand((unsigned) seed);
  
  // Allocate Random Generated Values to Array 
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      array[i][j] = rand() % 100; //range [0, 100]
    }
  }
  /*
  // Printing the 2D array
  cout<<"\n=====Generated Random Numbers====="<<endl;
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      cout<<array[i][j]<<" ";
    }
  cout<<endl;
  }
  */
}

void fileWrite(int Msize, int Nsize, int **A, int **B)
{
  int size;
  fstream fout;
  fout.open("matrix_checker.csv", ios::out | ios::app); 
  //append to prevent overwriting

  fout<<"Matrix A";
  for (int i = 0; i < Nsize + 1; i++)
  {
    fout<<",";
  }
  fout<<"Matrix B \n";
  
  if (Nsize < Msize)
  {
    size = Msize;
  }
  else if (Nsize > Msize)
  {
    size = Nsize;
  }
  else size = Msize;
  
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < Nsize; j++)
    { 
      if (i >= Msize)
      {
        fout <<",";
      }
      else 
      {
        fout << A[i][j] << ",";
      }
    }
  
    fout <<",";
  
    for (int k = 0; k < Msize; k++)
    {  
      if (i >= Nsize)
      {
        fout << ",";
      }
      else
      {
        fout << B[i][k] << ",";
      }
    }  
    fout << "\n";
  }
  fout.close();
}

void matrixMult(int Msize, int Nsize, int **A, int **B, int **C)
{
  // Initializing Elements of Array C to 0
  for(int i = 0; i < Msize; ++i)
  {
    for(int j = 0; j < Msize; ++j)
    {
      C[i][j]=0;
    }
  }

  // Multiplying Arrays A and B and Storing the Results in Array C
  for(int i = 0; i < Msize; ++i)
  {
    for(int j = 0; j < Msize; ++j)
    {
      for(int k = 0; k < Nsize; ++k)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void matrixMult_row(int row, int Msize, int Nsize, 
                    int **A, int **B, int **C)
{
  // Initializing Elements of Array C to 0
  for(int i = 0; i < Msize; ++i)
  {
    C[row][i] = 0;
  }
  
  for (int i = 0; i < Msize; i++)
  {
    for (int j = 0; j < Nsize; j++)
    {
      C[row][i] = C[row][i] + (A[row][j] * B[j][i]);
    }
    //cout<<C[row][i]<<" ";
  }
  //cout<<endl;
  /*The chaotic display of output on terminal when cout is used showcases the successful implementation of threads */
}

void matrixMult_prod(int row, int col, int Nsize, 
                     int **A, int **B, int **C)
{
  C[row][col] = 0;
  for (int i = 0; i < Nsize; i++)
  {
    C[row][col] = C[row][col] + (A[row][i] * B[i][col]);
  }
}

void threads_row(int Msize, int Nsize, int **A, int **B, int **C)
{
  vector<thread> threads;
  for (int i = 0; i < Msize; i++)
  {
    threads.push_back(thread(matrixMult_row, i, Msize, 
                             Nsize, A, B, C));
  }
  for (auto &th : threads)
  {
    th.join();
  }
}

void threads_prod(int Msize, int Nsize, int **A, int **B, int **C)
{
  vector<thread> threads;
  for (int i = 0; i < Msize; i++)
  {
    for (int j = 0; j < Nsize; j++)
    {
      threads.push_back(thread(matrixMult_prod, i, j, 
                               Nsize, A, B, C));
    }
  }
  for (auto &th : threads)
  {
    th.join();
  }
}

void speedTest(int M, int N, int **A, int **B, int **C, 
               int &count, int mode)
{
  int du;
  count = 0;
  auto start = high_resolution_clock::now();
  do
  {
    switch (mode)
    {
    case 1 : 
      matrixMult(M, N, A, B, C);
      count += 1;
      break;
    case 2 : //using threads per row operation
      threads_row(M, N, A, B, C);
      count += 1;
      break;
    case 3 : //for the third case
      threads_prod(M, N, A, B, C);
      count += 1;
      break;
    }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - start);
  du = duration.count();
  } while (du != 1);
}

void ave_var(int a[], int n, double &ave, double &var)
{
  // Compute for the average
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum += a[i];
  }
  ave = (double)sum / (double)n;
 
  // Compute for the variance
  double sqDiff = 0;
  for (int i = 0; i < n; i++)
  {
    sqDiff += (a[i] - ave) * (a[i] - ave);
  }
  var = sqDiff / n;
}

void validation(string size, int &x, bool &error)
{
  int numb;
  stringstream s(size);
  error = true;
  
  while (s >> numb)
  {
    x = numb;
  error = false;
  }
  
  s.str(string());
}

int main()
{
  string MSize, NSize;
  int count [10];
  int thcount [10];
  int prcount [10];
  int M = 0;
  int N = 0;
  bool errorM, errorN;
  
  do
  {
  cout<<"\nEnter Matrix Size: (M x N)\n"
      <<"M = ";
  getline(cin, MSize);
  cout<<"N = ";
  getline(cin, NSize);
  
  validation(MSize, M, errorM);
  validation(NSize, N, errorN);
  
  if (errorM == true || errorN == true)
  {
    cout<<"\n!!! Invalid Matrix Size !!!"<<endl;
  }
  
  //cout<<"\nM :"<<M<<" == N :"<<N<<endl;
  } while (errorM == true || errorN == true);

  
  // Initializing 2D Dynamic Arrays
  int ** A = new int * [M];
  int ** B = new int * [N];
  int ** C = new int * [M]; //resulting array
  
  for (int i = 0; i < M; i++)
  {
    A[i] = new int [N];
    C[i] = new int [M];
  }
  
  for (int i = 0; i < N; i++)
  {
    B[i] = new int [M];
  }
 
  // Allocating Values to Arrays A and B
  srand((unsigned) time(NULL));
  int seedA = rand(); 
  int seedB = rand();
  
  randNumb(M, N, A, seedA);
  randNumb(N, M, B, seedB);
  
  // Printing the returned 2D array
  cout<<"\n=====Matrix A====="<<endl;
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout<<A[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"\n=====Matrix B====="<<endl;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      cout<<B[i][j]<<" ";
    }
    cout<<endl;
  }
  
  // Exporting Contents of Matrix A and B for Output Checking
   fileWrite(M, N, A, B);
  
  // Performing Matrix Multiplication Individually
  //matrixMult(M, N, A, B, C); 
  //threads_row(M, N, A, B, C);
  //threads_prod(M, N, A, B, C);


  //Perfoming Speed Tests 
  // * Duration per tial = 1s
  // * No. of Trials = 10
  
  //>>WITHOUT THREADS
  for (int i = 0; i < 10; i++)
  {
    speedTest(M, N, A, B, C, count[i], 1);
  }
  
  /* Printing the Product of the Matrix Multiplication */
  cout<<"\n=====Output Matrix w/o threads====="<<endl;
  for (int i = 0; i < M; i++)
  {
    for (int je = 0; j < M; j++)
    {
      cout<<C[i][j]<<" ";
    }
    cout<<endl;
  }

  //>>WITH THREADS PER ROW
  for (int i = 0; i < 10; i++)
  {
    speedTest(M, N, A, B, C, thcount[i], 2);
  }
  
  // Printing the Product of the Matrix Multiplication 
  // using threads per 
  cout<<"\n=====Output Matrix w/ row threads====="<<endl;
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < M; j++)
    {
      cout<<C[i][j]<<" ";
    }
    cout<<endl;
  }
  
  //>>WITH THREADS PER PRODUCT
  for (int i = 0; i < 10; i++)
  {
    speedTest(M, N, A, B, C, prcount[i], 3);
  }
  // Printing the Product of the Matrix Multiplication 
  // using threads per product 
  cout<<"\n=====Output Matrix w/ product threads====="<<endl;
  for (int i = 0; i < M; i++)
  {
    for (int j = 0; j < M; j++)
    {
      cout<<C[i][j]<<" ";
    }
    cout<<endl;
  }
 
  // Printing Details of Performance
  double mean, variance;
  cout<<"\nNumber of performed Matrix Multiplication"
      <<" in 10 trials with duration of 1s each" <<endl;
  
  ave_var(count, 10, mean, variance);
  cout<<">> w/o threads \n"
      <<"Minimum = "<<*min_element(count, count + 10)<<"\n"
      <<"Maximum = "<<*max_element(count, count + 10)<<"\n"
      <<"Average = "<<mean<<"\n"
      <<"Variance = "<<variance<<"\n";
    
  ave_var(thcount, 10, mean, variance);
  cout<<"\n>> w/ threads per row \n"
      <<"Minimum = "<<*min_element(thcount, thcount + 10)<<"\n"
      <<"Maximum = "<<*max_element(thcount, thcount + 10)<<"\n"
      <<"Average = "<<mean<<"\n"
      <<"Variance = "<<variance<<"\n";
    
  ave_var(prcount, 10, mean, variance);
  cout<<"\n>> w/ threads per product \n"
      <<"Minimum = "<<*min_element(prcount, prcount + 10)<<"\n"
      <<"Maximum = "<<*max_element(prcount, prcount + 10)<<"\n"
      <<"Average = "<<mean<<"\n"
      <<"Variance = "<<variance<<"\n";
  
  return 0;
}