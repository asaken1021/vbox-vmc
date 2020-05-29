#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>

#include "shell_execute.h"

using namespace std;

int main(int argc, char *argv[])
{
  random_device rd;
  mt19937 mt(rd());
  bool isVerbose = false;
  int vmCount = 0;
  int vmNameReadCount = 0;
  int selectedVMNumber = 0;
  int controlNumber = 0;
  string tempFolderName = "vbvmc_temp" + to_string(mt());
  string vmlistFileName = tempFolderName + "/vmlist.vbvmc";
  string vmnameFileName = tempFolderName + "/vmname.vbvmc";
  string strcache = "";

  if (argc == 2)
  {
    if (strcmp(argv[1], "--verbose") || strcmp(argv[1], "-v"))
    {
      isVerbose = true;
    }
  }

  string command = "mkdir " + tempFolderName;
  execute(command, isVerbose);

  command = "vboxmanage list vms > " + vmlistFileName;
  execute(command, isVerbose);

  command = "cat " + vmlistFileName + " | perl -lne 'if(/'\\\"'(.*)'\\\"'/) {print $1}' > " + vmnameFileName;
  execute(command, isVerbose);

  ifstream vmnameFileStream(vmnameFileName);

  if (vmnameFileStream.fail())
  {
    cerr << "一時ファイルの読み取りに失敗しました。" << endl;
    return -1;
  }

  // cout << "^q^" << endl;

  while (getline(vmnameFileStream, strcache))
  {
    // cout << strcache << endl;
    vmCount++;
  }

  string vmNames[vmCount];

  vmnameFileStream.close();
  vmnameFileStream.open(vmnameFileName);

  while (getline(vmnameFileStream, strcache))
  {
    vmNames[vmNameReadCount] = strcache;
    vmNameReadCount++;
  }

  // cout << "vmCount=" << vmCount << ", vmNameReadCount=" << vmNameReadCount << endl;

  cout << "VM List -----" << endl;
  for (int x = 0; x < vmCount; x++)
  {
    cout << "[" << x << "] " << vmNames[x] << endl;
  }
  cout << "操作するVMを選択してください > " << flush;
  cin >> selectedVMNumber;

  if (selectedVMNumber >= vmCount)
  {
    cerr << "そのようなVMはありません。" << endl;
    return -2;
  }

  cout << "VMに対する操作を選択してください。" << endl
       << "(起動: 1, リセット: 2, 強制終了: 3, ACPIシャットダウン: 4) > " << flush;
  cin >> controlNumber;

  if (controlNumber > 4)
  {
    cerr << "そのような操作はありません。" << endl;
    return -3;
  }

  return 0;
}