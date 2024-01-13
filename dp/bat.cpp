#include<bits/stdc++.h>

using namespace std;
int main(){
  system("g++ sol.cpp -o sol -O2 -std=c++14 & g++ xs.cpp -o xs -O2 -std=c++14 & echo finish g++");
  for (long long i = 1; /*If you want to set the number of shots, please fill in this expression. Otherwise, execution continues until Hack data is found.*/; i++){
    system("python checker.py > t.in");
    //cout << "finish checker.\n";
    int xsca = clock();
    system("xs.exe < t.in > t.out");
    //cout << "finish xs.\n";
    int xscb = clock();
    system("sol.exe < t.in > t.ans");
    //cout << "finish sol.\n";
    int solcb = clock();
    if (xscb - xsca > 1207){
      cout << "Time Limit Exceeded on test #" << i << ".Time: " << xscb - xsca << "ms.STD time:" << solcb - xscb << "ms.\n";
      exit(0);
    }
    if (system("fc t.out t.ans")){
      cout << "Wrong answer on test #" << i << ".Time: " << xscb - xsca << "ms.STD time:" << solcb - xscb << "ms.\n";
      return 0;
    }
    cout << "Accept on test #" << i << ".Time: " << xscb - xsca << "ms.STD time:" << solcb - xscb << "ms.\n";
  }
  return 0;
}
