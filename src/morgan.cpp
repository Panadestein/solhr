#include "morgan.h"
#include <bits/stdc++.h>
using namespace std;

string morganAndStringSlow(string a, string b) {
  string lexi_minimal = "";

  int lena = a.size();
  int lenb = b.size();
  int i = 0, j = 0;

  // This is the key point of the problem
  // it allows for taking the right decision with string
  // Of different size (consider X and XXP, for example)
  a += 'z';
  b += 'z';

  while (i < lena || j < lenb) {
    if (a[i] < b[j]) {
      lexi_minimal += a[i];
      i++;
    } else if (b[j] > a[i]) {
      lexi_minimal += b[j];
      j++;
    } else {
      if (a.substr(i) <= b.substr(j)) {
        lexi_minimal += a[i];
        i++;
      } else {
        lexi_minimal += b[j];
        j++;
      }
    }
  }

  if (i < lena) {
    lexi_minimal += a.substr(i, lena - 1);
  } else if (j < lenb) {
    lexi_minimal += b.substr(j, lenb - 1);
  }

  return lexi_minimal;
}

string morganAndString(string a, string b) {
  string lexi_minimal = "";

  int lena = a.size();
  int lenb = b.size();
  int i = 0, j = 0;

  // This is the key point of the problem
  // it allows for taking the right decision with string
  // Of different size (consider X and XXP, for example)
  a += 'z';
  b += 'z';

  while (i < lena || j < lenb) {
    if (a[i] < b[j]) {
      lexi_minimal += a[i++];
    } else if (a[i] > b[j]) {
      lexi_minimal += b[j++];
    } else {
      int x = i, y = j;
      char ai = a[i], bj = b[j];
      for (; x < lena && y < lenb; x++, y++) {
        if (a[x] != b[y]) {
          break;
        } else if (a[x] > ai) {
          lexi_minimal += a.substr(i, x - i) + b.substr(j, y - j);
          i = x;
          j = y;
          ai = a[i];
          bj = b[j];
        }
      }

      if (x == lena) {
        lexi_minimal += b[j++];
      } else if (y == lenb) {
        lexi_minimal += a[i++];
      } else {
        if (a[x] < b[y]) {
          lexi_minimal += a[i++];
        } else {
          lexi_minimal += b[j++];
        }
      }
    }
  }

  return lexi_minimal;
}

int main() {

  bool simple = false;

  if (simple) {
    cout << morganAndString("CABAA", "CABAB") << endl;
    cout << morganAndString("ABACAZZ", "ABACABA") << endl;
    cout << morganAndString("Z", "ZZT") << endl;
    cout << morganAndString("ZZ", "ZZTA") << endl;
    cout << morganAndString("ZZ", "ZZZT") << endl;
    cout << morganAndString("ZA", "ZZT") << endl;
    cout << morganAndString("Z", "ZXY") << endl;
    cout << morganAndString("BB", "BBX") << endl;
    cout << morganAndString("BB", "BBA") << endl;
    cout << morganAndString("BXY", "B") << endl;
    cout << morganAndString("BXA", "BAT") << endl;
  } else {
    ifstream input("inputs.txt");
    ofstream output("outputs.txt");

    int num_cases;
    input >> num_cases;
    for (int i = 0; i < num_cases; i++) {
      string a, b;
      input >> a >> b;
      if (i == num_cases - 1) {
        output << morganAndString(a, b) << "\n";
      }
    }

    input.close();
    output.close();
  }

  return 0;
}
