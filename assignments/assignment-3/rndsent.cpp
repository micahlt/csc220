#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  srand(time(NULL));
  // Establish a map of word categories and the words in those lists
  map<string, vector<string>> allWords;
  // Establish the current word category
  string currentCategory;
  // Establish the current inputted word
  string val;
  // Loop through each inputted word
  while (cin >> val) {
    // If the last char is a colon
    if (val.back() == ':') {
      // If it's just a colon then break out of the loop
      if (val.length() == 1) {
        break;
      }
      // Set the current word category
      currentCategory = val.substr(0, val.length() - 1);
    } else {
      allWords[currentCategory].push_back(val);
    }
  }

  string name = allWords["name"][rand() % allWords["name"].size()];
  string verb = allWords["verb"][rand() % allWords["verb"].size()];
  string noun = allWords["noun"][rand() % allWords["noun"].size()];
  string adjString;

  if (rand() % 4 < 3) {
    int firstAdjIndex = rand() % allWords["adj"].size();
    adjString += allWords["adj"][firstAdjIndex];
    allWords["adj"].erase(allWords["adj"].begin() + firstAdjIndex);
    if (rand() % 4 < 3) {
      adjString += " " + allWords["adj"][rand() % allWords["adj"].size()];
    }
    adjString += " ";
  }
  cout << name << " " << verb << " the " << adjString << noun << endl;
}