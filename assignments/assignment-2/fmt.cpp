#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main() {
  string word;
  bool handleNewParagraph = false;
  // Current line length starts at 5 to handle initial indent
  int lineLength = 5;
  int maxLineLength = 75;

  // Initial paragraph indent
  cout << "     ";
  // Loop over each word in the inputted string
  while (cin >> word) {
    // Handle the paragraph flag

    if (word == ":P") {
      // Set handler variable for next iteration of the loop
      handleNewParagraph = true;
      // Handle the line-break flag
    } else if (word == ":B") {
      int lines;
      // Set the number of lines to break
      cin >> lines;
      // If the line length is not zero, print the proper amount of newlines
      if (lineLength != 0) {
        for (int i = 0; i < lines; i++) {
          cout << endl;
        }
      }
      // Handle the width flag
    } else if (word == ":W") {
      int width;
      // Set the new width of lines
      cin >> width;
      // Ensure that the max line width is no less than 20
      maxLineLength = width >= 20 ? width : 20;
      // Set paragraph handler variable for next iteration of the loop
      handleNewParagraph = true;
    } else {
      // Check if should break for new paragraph
      if (handleNewParagraph) {
        // Print a newline and an indent
        cout << endl << "     ";
        // Update current line length with indent
        lineLength = 5;
        // Reset paragraph handler variable
        handleNewParagraph = false;
      }
      // Check if line has reached max length
      if ((lineLength + word.length() + 1) > (maxLineLength + 1)) {
        // Print a newline
        cout << endl;
        // Reset current line length
        lineLength = 0;
      }
      // Check if word begins with an escape character
      if (word.substr(0, 1) == "\\") {
        // Remove the backslash from the word
        word = word.substr(1);
        // If the characther is just a backslash then skip it
        if (word.length() == 0) {
          continue;

        }
      }
      // Print word and a space
      cout << word << " ";
      // Update current line length
      lineLength += word.length() + 1;
    }
  }
  // Print a newline at the end of the program
  cout << endl;
}