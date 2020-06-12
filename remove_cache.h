#include "shell_execute.h"

int remove_cache(string tempFolderName, bool isVerbose)
{
  execute("rm -rf ./" + tempFolderName, isVerbose);
}