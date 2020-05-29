#include <iostream>
#include <string>

using namespace std;

int execute(string cmd)
{
  system(cmd.c_str());
  return 0;
}