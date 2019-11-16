#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
int MIS(int i, int j, int *array, bool *crray);

int main(int argc, char *argv[]) {
  ifstream fin;
  ofstream fout(argv[2]);
  // string seq;
  int num = 0;
  int i = 0, j = 0;
  int *array;
  bool *crray; // check the chord be choosed
  fin.open(argv[1], ios::in);

  if (fin) {
    fin >> num;
    array = new int[num];
    crray = new bool[num];
    int chord = num / 2;
    // cout << num;
    // cout << chord;
    for (int line = 0; line < chord; line++) {
      fin >> i >> j;
      array[i] = j;
      array[j] = i;
      // cout << array[j] << " " << array[i] << endl;
    }
    fout << MIS(0, num - 1, array, crray) << endl;
  } else {
    cout << "file doesn't exist!";
  }

  for (int p = 0; p < num; p++) {
    if (crray[p])
      fout << p << " " << array[p] << endl;
  }
}
int MIS(int i, int j, int *array, bool *crray) {
  if (i >= 0 && j >= 0) {
    cout << "i: " << i << " j: " << j << endl;
    if (i == j) {
      // cout << "i: " << i << endl;
      return 0;
    } else {
      if (array[j] > j || array[j] < i) {
        cout << "k: " << array[j] << endl;
        return MIS(i, j - 1, array, crray);
      } else if (array[j] == i) {
        crray[i] = true;
        // crray[j] = 1;
        return 1 + MIS(array[j] + 1, j - 1, array, crray);
      } else {
        crray[array[j]] = true;
        // crray[j] = 1;
        return MIS(i, array[j] - 1, array, crray) + 1 +
               MIS(array[j] + 1, j - 1, array, crray);
      }
    }
  }
}