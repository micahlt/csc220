#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  vector<string> myVect;
  myVect.push_back("Hello");
  myVect.push_back("my name is");
  myVect.push_back("Micah");
  for (vector<string>::iterator i = myVect.begin(); i != myVect.end(); i++) {
    cout << *i << endl;
  }
  return 0;
}