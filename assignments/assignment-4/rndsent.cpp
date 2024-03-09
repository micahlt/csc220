#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void print(string word, int &wordLineCount) {
  if (isalnum(word[0])) {
    if (wordLineCount > 8) {
      cout << endl << word;
      wordLineCount = 0;
    } else if (wordLineCount > 0) {
      cout << " " << word;
    } else {
      cout << word;
    }
  } else {
    cout << word;
  }
  wordLineCount++;
}

string getWord(string category, map<string, vector<string>> &wordList) {
  int wordIndex = rand() % wordList[category].size();
  string word = wordList[category][wordIndex];
  wordList[category].erase(wordList[category].begin() + wordIndex);
  return word;
}

int main() {
  srand(time(NULL));
  // Establish a map of word categories and the words in those lists
  map<string, vector<string>> allWords;
  // Establish the savename list
  map<string, string> savednames;
  // Establish the current word category
  string currentCategory;
  // Establish the current inputted word
  string val;
  // Establish what we're reading (vars vs template)
  string readMode = "vars";
  // Establish words currently on line
  int wordsOnLine = 0;
  // Loop through each inputted word
  while (cin >> val) {
    if (readMode == "vars") {
      // If the last char is a colon
      if (val.back() == ':') {
        // If it's just a colon then start reading template
        if (val.length() == 1) {
          readMode = "template";
        }
        // Set the current word category
        currentCategory = val.substr(0, val.length() - 1);
      } else {
        allWords[currentCategory].push_back(val);
      }
    } else if (readMode == "template") {
      if (val.front() == '@') { // Read a tag
        int equalsIndex = val.find('=');
        if (equalsIndex == string::npos) {          // Not a savedname adder
          if (!savednames[val.substr(1)].empty()) { // Print savedname
            print(savednames[val.substr(1)], wordsOnLine);
          } else if (!allWords[val.substr(1)].empty()) { // Print category word
            print(getWord(val.substr(1), allWords), wordsOnLine);
          } else {
            continue;
          }
        } else { // Is a savedname
          // Add savendame to map
          savednames[val.substr(1, equalsIndex - 1)] =
              getWord(val.substr(equalsIndex + 1, -1), allWords);
        }
      } else { // Read a word
        print(val, wordsOnLine);
      }
    }
  }
  cout << endl;
}
