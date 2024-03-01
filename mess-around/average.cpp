#include <iostream>
#include <vector>
using namespace std;

int main() {
  // Read them in.
  int arr[50]; /* Array of numbers. */
  int scan[50] = arr;
  cout << "Enter some integers: " << endl;
  while (cin >> *scan)
    ++scan;
  int *end = scan;

  // Print them back out again.
  cout << "===============" << endl;
  for (scan = arr; scan < end; ++scan) {
    cout << *scan << " ";
  }
  cout << endl;
}