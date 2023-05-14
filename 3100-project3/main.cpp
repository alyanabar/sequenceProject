// MY TESTING MAIN WHILE MAKING FUNCTIONS
/*#include <iostream>
#include <string>
#include <stdlib.h>
#include "sequence.h"

using namespace std;

int main() {
  Sequence mySequence(4);
  mySequence.push_back(3);
  mySequence.push_back(7);
  mySequence.printForward(); //1
  mySequence.pop_back();
  mySequence.printForward(); //2
  mySequence.insert(1, 4);
  mySequence.printForward();//3
  mySequence.insert(3, 5);
  Sequence::value_type back;
  back = mySequence.back();//4
  cout << "Print back: "<< back << endl;
  bool isIt;
  isIt = mySequence.empty();
  if (isIt == 0) {
    cout << "it is not empty"<< endl;
  }
  int size ;
  size = mySequence.size();
  cout << "size = " << size << endl;
  mySequence.printForward(); //5
  //mySequence.erase(1,7);
  int n = 0;
  n = mySequence[4];
  cout << n << endl;
  mySequence[1] = 99;
  mySequence.printForward();
  mySequence.push_back(7);
  mySequence.printForward();
  cout << mySequence << endl;
}*/