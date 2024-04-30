#include "queues.h"
#include <iostream>
using namespace std;

int main() {
  cout << "==== REPEATING QUEUE ====" << endl;
  rpt_queue<int> q;
  q.push(10);
  q.push(10);
  q.push(3);
  q.push(18);
  q.push(18);
  q.push(18);
  q.push(10);
  int item;
  cout << "Original Queue:" << endl;
  q.print();
  cout << endl;
  cout << "Popped Item Count: " << q.pop(item) << endl;
  cout << "Popped Item Value: " << item << endl << endl;
  cout << "Final Queue:" << endl;
  q.print();
  cout << endl;

  cout << "==== EXPANDING QUEUE ====" << endl;
  expand_queue<int> e;
  e.push(3, 10);
  e.push(2, 18);
  e.push(0, 5);
  e.push(1, 1);
  e.print();
}