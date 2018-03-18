//               testadec.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM Adec;
///////////////////////
//  Постоить автомат
  addrange(Adec,0,'0','9',1);
  addstr(Adec,0,"+-",5);
  addstr(Adec,0,"0",6);
  addstr(Adec,6,"eE",3);
  addstr(Adec,6,".",2);
  addrange(Adec,5,'1','9',1);
  addstr(Adec,5,"0",6);
  addrange(Adec,1,'0','9',1);
  addstr(Adec,1,".",2);
  addstr(Adec,1,"eE",3);
  addstr(Adec,2,"eE",3);
  addrange(Adec,2,'0','9',2);
  addstr(Adec,3,"+-0123456789",4);
  addrange(Adec,4,'0','9',4);
//......................
 Adec.final(1);
 Adec.final(2);
 Adec.final(4);
//......................
///////////////////////
  cout << "*** svs Adec "
       << "size=" << Adec.size()
       << " ***\n";
  cout << endl;

  while(true)
 {
  char input[81];
  cout << ">";
  cin.getline(input,81);
  if(!*input) break;
  int res = Adec.apply(input);
  cout << setw(res?res+1:0) << "^"
       << endl;
 }
 return 0;
}

