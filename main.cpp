#include <iostream>
#include <cstdlib>
#include <random>

#include "shell_execute.h"

using namespace std;

int main(int argc, char *argv[])
{
  random_device rd;
  mt19937 mt(rd());
  string tempFolderName = "vbvmc_temp" + to_string(mt());
  string vmlistFileName = tempFolderName + "/vmlist.vbvmc";
  string command = "mkdir " + tempFolderName;
  execute(command);
  command = "vboxmanage list vms > " + vmlistFileName;
  execute(command);
}