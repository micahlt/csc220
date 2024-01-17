#include <iostream>
#include <math.h>

using namespace std;

int main() {
  int height, diameter, fillRate;
  cout << "Enter bucket height (cm): ";
  cin >> height;
  cout << "Enter diameter (cm): ";
  cin >> diameter;
  cout << "Enter fill rate (ml/s): ";
  cin >> fillRate;
  double volume = (double)height * M_PI * pow((double)diameter / 2, 2);
  double fillTime = volume / fillRate;
  cout << "Bucket of diameter " << diameter << " cm and " << height
       << " cm tall filling at " << fillRate << " ml/s will fill in "
       << fillTime << " seconds." << endl;
}