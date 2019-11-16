#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream fin;
  // string seq;
  int num = 0;
  int i = 0, j = 0;
  int *array;

  fin.open(argv[1], ios::in);
  if (fin) {
    fin >> num;
    // array = new int[num];
    int chord = num / 2;
    cout << num;
    cout << chord;
    for (int line = 0; line < chord; chord++) {
      fin >> i >> j;
      // cout << i << j << endl;
    }
  } else {
    cout << "file doesn't exist!";
  }
}