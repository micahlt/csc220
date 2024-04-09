#include "url.h"
#include <iostream>
using namespace std;

int main() {
  URL u = URL("https://www.domain.com/path/mypath/./..///");
  cout << u.get() << endl;
}