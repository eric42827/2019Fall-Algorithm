#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
int MIS(int i, int j, int *array, int **misrray);
inline void backtrack(int i, int j, int *array, char *s, int num,
                      int **misrray);
// int backtrack(int i, int j, int *array, int **misrray);
int main(int argc, char *argv[]) {
  ifstream fin;
  ofstream fout(argv[2]);
  // string seq;
  int num = 0;
  int a = 0, b = 0;
  int *array;
  bool *crray; // check the chord be choosed
  int **misrray;
  fin.open(argv[1], ios::in);

  if (fin) {
    fin >> num;
    array = new int[num];
    crray = new bool[num];
    misrray = new int *[num];
    for (int p = 0; p < num; p++) {
      misrray[p] = new int[num];
      for (int q = 0; q < num; q++)
        misrray[p][q] = -1;
    }

    int chord = num / 2;
    // cout << num;
    // cout << chord;
    for (int line = 0; line < chord; line++) {
      fin >> a >> b;
      array[a] = b;
      array[b] = a;
      // cout << array[j] << " " << array[i] << endl;
    }
    // fout << MIS(0, num - 1, array, misrray) << endl;
  } else {
    cout << "file doesn't exist!";
  }
  /*for (int p = 0; p < num; p++)
    cout << setw(2) << p + 1 << " ";
  cout << endl;
  for (int p = 0; p < num; p++) {
    for (int q = 0; q < num; q++)
      cout << setw(2) << misrray[p][q] << " ";
    cout << endl;
  }*/
  backtrack(0, num - 1, array, argv[2], num, misrray);
  /*for (int p = 0; p < num; p++) {
    if (crray[p])
      fout << p << " " << array[p] << endl;
  }*/
}
int MIS(int i, int j, int *array, int **misrray) {
  // if (i >= 0 && j >= 0) {
  // cout << "i: " << i << " j: " << j << endl;
  if (misrray[i][j] != -1)
    return misrray[i][j];
  else {
    if (i >= j) {
      // cout << "i: " << i << endl;
      return 0;
    } else {
      if (array[j] > j || array[j] < i) {
        // cout << "k: " << array[j] << endl;
        misrray[i][j] = MIS(i, j - 1, array, misrray);
        return misrray[i][j];
      } else {
        // cout << "k: " << array[j] << endl;
        if (MIS(i, array[j] - 1, array, misrray) + 1 +
                MIS(array[j] + 1, j - 1, array, misrray) >
            MIS(i, j - 1, array, misrray)) {
          // crray[array[j]] = true;
          misrray[i][j] = MIS(i, array[j] - 1, array, misrray) + 1 +
                          MIS(array[j] + 1, j - 1, array, misrray);
        } else {
          misrray[i][j] = MIS(i, j - 1, array, misrray);
        }
        return misrray[i][j];
      }

      //}
    }
  }
}
inline void backtrack(int i, int j, int *array, char *s, int num,
                      int **misrray) {

  static ofstream fout(s);
  if (j == num - 1) {
    // cout << s << endl;
    fout << MIS(0, num - 1, array, misrray) << endl;
    // cout << MIS(0, num - 1, array, misrray) << endl;
  }

  if (i >= j)
    return;
  // if (misrray[i][j - 1] < misrray[i][j])
  // crray[array[j]] = true;
  if (i <= array[j] && array[j] < j) {
    if (MIS(i, array[j] - 1, array, misrray) + 1 +
            MIS(array[j] + 1, j - 1, array, misrray) >
        MIS(i, j - 1, array, misrray)) {
      backtrack(i, array[j] - 1, array, s, num, misrray);
      fout << array[j] << " " << j << endl;
      backtrack(array[j] + 1, j - 1, array, s, num, misrray);
      return;
    }
  }
  backtrack(i, j - 1, array, s, num, misrray);
}