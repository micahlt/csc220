#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main() {
  string word;
  string previousWord;
  bool handleNewParagraph = false;
  bool handleBlankLines = false;
  bool handleWidth = false;
  int lineLength = 5;
  int maxLineLength = 75;

  cout << "     ";
  while (cin >> word) {
    if (word == ":P") {
      handleNewParagraph = true;
    } else if (word == ":B") {
      handleBlankLines = true;
      int lines;
      cin >> lines;
      if (lineLength != 0) {
        for (int i = 0; i < lines; i++) {
          cout << endl;
        }
      }
    } else if (word == ":W") {
      int width;
      cin >> width;
      maxLineLength = width >= 20 ? width : 20;
      handleNewParagraph = true;
    } else {
      if (handleNewParagraph) {
        cout << endl << "     ";
        lineLength = 5;
        handleNewParagraph = false;
      }
      if ((lineLength + word.length() + 1) > (maxLineLength + 1)) {
        cout << endl;
        lineLength = 0;
      }
      if (word.substr(0, 1) == "\\") {
        word = word.substr(1);
        if (word.length() == 0) {
          continue;
        }
      }
      cout << word << " ";
      lineLength += word.length() + 1;
    }
  }
  cout << endl;
}