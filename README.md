# vbox-vmc
簡単(雑)なVirtualBoxのVM操作プログラム  
自己責任でどうぞ。  
  
ビルド確認済:  
macOS Catalina 10.15.5(Apple clang version 11.0.3)  
Ubuntu 18.04.4(g++ 7.5.0)  
## Build
すでにVirtualBoxがインストールされており、vboxmanageまでパスが通っている必要があります。  
必要なパッケージ: g++ perl  
必要なパッケージがインストールされていない場合はインストールしてください。  
```bash
(Ubuntu)$ sudo apt install g++ perl
```
vbox-vmcをビルドするには`main.cpp`のあるフォルダまで移動して↓を実行してください。
```bash
$ ./build.sh
```
または
```bash
$ g++ -g main.cpp -o vbox-vmc
```
## 使い方
vbox-vmcを実行するだけです。
```bash
$ ./vbox-vmc
```
この後は表示されるメッセージに従ってください。  
`--verbose`か`-v`を引数につけて実行すると内部で実行しているコマンドも表示します。
```bash
$ ./vbox-vmc --verbose
or
$ ./vbox-vmc -v
```
