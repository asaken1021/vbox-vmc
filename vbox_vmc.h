#include <iostream>
#include <string>

using namespace std;

int execute(string cmd, bool showCommand)
{
  if (showCommand)
  {
    cout << cmd << endl;
  }

  system(cmd.c_str());
  return 0;
}

int remove_cache(string tempFolderName, bool isVerbose)
{
  execute("rm -rf ./" + tempFolderName, isVerbose);
  return 0;
}