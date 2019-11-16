#include <cassert>
#include <cstdint>
#include <fstream>
#include <vector>

constexpr int ind(int i, int j, int w) { return i * w + j; }

struct MPSFinder {
  int numOfVertices;
  std::vector<uint16_t> chords;
  std::vector<uint16_t> MIS;
  // First 16 bits stores the size of maximum independent set,
  // last 16 bits stores k, if MIS(i, j) does not include chord jk,
  // The last 16 bits would be 0xFFFF (UINT16_MAX)
  std::ofstream ofs;

  MPSFinder(const char *inputFile) {
    std::ifstream ifs(inputFile);
    if (!ifs)
      return;
    ifs >> numOfVertices;
    int numOfChords = numOfVertices / 2;
    uint16_t a = 0, b = 0;
    chords.assign(numOfVertices, 0);
    for (; numOfChords > 0; --numOfChords) {
      ifs >> a >> b;
      chords[a] = b;
      chords[b] = a;
    }
    MIS.reserve(numOfVertices * numOfVertices);
    MIS.assign(numOfVertices * numOfVertices, UINT16_MAX);
  }

  uint16_t mis(int i, int j) {
    if (i >= j)
      return 0; // Base case
    if (MIS[ind(i, j, numOfVertices)] != UINT16_MAX)
      return MIS[ind(i, j, numOfVertices)];

    uint16_t k = chords[j];
    uint32_t without_jk = mis(i, j - 1);
    if (i <= k && k < j) {
      uint32_t with_jk = mis(i, k - 1) + mis(k + 1, j - 1) + 1;
      if (with_jk > without_jk) {
        MIS[ind(i, j, numOfVertices)] = with_jk; // Includes chord jk
      } else {
        MIS[ind(i, j, numOfVertices)] =
            without_jk; // Does not include chord jk (i <= k < j)
      }
    } else {
      MIS[ind(i, j, numOfVertices)] =
          without_jk; // Does not include chord jk (i > k or k >= j)
    }
    return MIS[ind(i, j, numOfVertices)];
  }

  void backtrack(int i, int j) {
    if (i >= j)
      return; // Base case
    uint16_t k = chords[j];
    uint32_t without_jk = MIS[ind(i, j - 1, numOfVertices)];
    if (i <= k && k < j) {
      uint32_t with_jk = MIS[ind(i, k - 1, numOfVertices)] +
                         MIS[ind(k + 1, j - 1, numOfVertices)] + 1;
      if (with_jk > without_jk) {
        backtrack(i, k - 1);
        ofs << k << ' ' << j << '\n';
        backtrack(k + 1, j - 1);
        return;
      }
    }
    backtrack(i, j - 1);
  }

  void execute(const char *outputFile) {
    ofs.open(outputFile);
    int ans = mis(0, numOfVertices - 1);
    ofs << ans << std::endl;
    backtrack(0, numOfVertices - 1);
    ofs.flush();
    ofs.close();
  }
};

int main(int argc, char *argv[]) {
  assert(argc > 2);
  MPSFinder finder(argv[1]);
  finder.execute(argv[2]);
  return 0;
}