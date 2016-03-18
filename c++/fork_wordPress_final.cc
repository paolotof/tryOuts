#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>// Declaration for exit()
#include <chrono> // available from c++11
#include <ctime>


using namespace std;

long fibonacci(unsigned n)
{
  if (n < 2) return n;
  return fibonacci(n-1) + fibonacci(n-2);
}

int printOutput(string nameProcess, size_t nFibonacci)
{
  cout << nameProcess << " started at ";
  chrono::time_point<chrono::system_clock> start;
  start = chrono::system_clock::now();
  time_t startTime = chrono::system_clock::to_time_t(start);
  cout << ctime(&startTime);
  
  cout << nameProcess << "f(" << nFibonacci << ") = ";
  cout << fibonacci(nFibonacci) << '\n';
  
  cout << nameProcess << "finished computation at ";
  chrono::time_point<chrono::system_clock> end;
  end = chrono::system_clock::now();
  time_t end_time = chrono::system_clock::to_time_t(end);
  cout << ctime(&end_time);
   
  cout << nameProcess << "elapsed time: ";
  chrono::duration<double> elapsed_seconds = end-start;
  cout << elapsed_seconds.count() << "s\n";
  
  return 0;
}

int main()
{
  pid_t pid;
  pid = fork();
  switch(pid)
  {
    case 0:
    {
      printOutput("CHILD ", 42);
      exit(0);
    }
    case -1:
    {
      cout << "Failed to fork\n";
      exit(1);
    }
    default:
      printOutput("PARENT ", 42);
  }
  cout << "waiting for all processes to finish\n";
  waitpid(-1, NULL, 0);
  cout << "END\n";
  return 0;
}
