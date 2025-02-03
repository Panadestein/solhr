#include <bits/stdc++.h>

using namespace std;

/*
   My inital idea was to use Radix sort, which needs a stable sort, ergo the
   count sort implementation. For this particular problem it is a bad idea,
   though. The individual strings could be very large, producing a very slow
   O(k+n) and memory hungry algorithm (if I pad the smaller with zeros)
*/

vector<int> countSort(vector<int> unsorted) {
  int k = 8; // Maximum of the integers
  int n = unsorted.size();
  vector<int> sorted(n, 0);
  vector<int> counts(k + 1, 0);

  // Set counts
  for (int i = 0; i < n; i++)
    counts[unsorted[i]]++;

  // Accumulate counts
  for (int i = 1; i <= k; i++)
    counts[i] += counts[i - 1];

  // Fill sorted array
  for (int i = n - 1; i >= 0; i--) {
    counts[unsorted[i]]--;
    sorted[counts[unsorted[i]]] = unsorted[i];
  }

  return sorted;
}

/*
   A much better idea is to simply use standard library sort function
   with a custom comparison. The algorithm in the std is already very
   efficient, it is an introsort
*/

bool stringNumComp(const string &a, const string &b) {
  if (a.length() != b.length()) {
    return a.length() < b.length();
  }
  // If they are the same length, lexicographical comp
  return a < b;
}

vector<string> bigSorting(vector<string> unsorted) {
  sort(unsorted.begin(), unsorted.end(), stringNumComp);
  return unsorted;
}

int main(int argc, char const *argv[]) {
  vector<string> initial = {
      "31415926535897932384626433832795", "1", "3", "10", "3", "5"};
  vector<int> numbers = {1, 3, 3, 4, 8, 4, 5, 7};

  // Sorted strings
  for (auto &el : bigSorting(initial)) {
    cout << el << endl;
  }

  // Sorted ints
  cout << "NUMS" << endl;
  vector<int> so = countSort(numbers);
  for (auto &i : so) {
    cout << i << endl;
  }

  return 0;
}
