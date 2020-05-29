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

  cout << endl
       << "--- 仮想マシン一覧 ----------" << endl;
  for (int x = 0; x < vmCount; x++)
  {
    cout << "[" << x << "] " << vmNames[x] << endl;
  }
  cout << endl
       << "操作するVMを選択してください > " << flush;
  cin >> selectedVMNumber;
  if (cin.fail())
  {
    cerr << "入力が正しくありません。" << endl;
    return -2;
  }

  if (selectedVMNumber >= vmCount)
  {
    cerr << "そのようなVMはありません。" << endl;
    return -3;
  }

  cout << endl
       << "VMに対する操作を選択してください。" << endl
       << "(通常起動: 1, ヘッドレス起動:2, リセット: 3, 強制終了: 4, ACPIシャットダウン: 5) > " << flush;
  cin >> controlNumber;
  if (cin.fail())
  {
    cerr << "入力が正しくありません。" << endl;
    return -2;
  }

  switch (controlNumber)
  {
  case 1:
    command = "vboxmanage startvm '" + vmNames[selectedVMNumber] + "' --type gui";
    execute(command, isVerbose);
    break;
  case 2:
    command = "vboxmanage startvm '" + vmNames[selectedVMNumber] + "' --type headless";
    execute(command, isVerbose);
    break;
  case 3:
    command = "vboxmanage controlvm '" + vmNames[selectedVMNumber] + "' reset";
    execute(command, isVerbose);
    break;
  case 4:
    command = "vboxmanage controlvm '" + vmNames[selectedVMNumber] + "' poweroff";
    execute(command, isVerbose);
    break;
  case 5:
    command = "vboxmanage controlvm '" + vmNames[selectedVMNumber] + "' acpipowerbutton";
    execute(command, isVerbose);
    break;
  default:
    cerr << "そのような操作はありません。または、不明なエラーです。" << endl;
    return -4;
  }

  return 0;
}