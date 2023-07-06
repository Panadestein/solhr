#include <bits/stdc++.h>
using namespace std;

string morganAndString(string a_in, string b_in) {
  // The result
  string lexi_minimal;
  // Temporary strings
  string a, b;

  a = a_in;
  b = b_in;
  int ctn;
  char cmpchar;
  while (true) {
    if (a.empty()) {
      lexi_minimal += b;
      break;
    } else if (b.empty()) {
      lexi_minimal += a;
      break;
    } else if (a[0] > b[0]) {
      lexi_minimal += b[0];
      b = b.substr(1);
    } else if (a[0] < b[0]) {
      lexi_minimal += a[0];
      a = a.substr(1);
    } else {
      if (a[ctn] == b[ctn]) {
        cmpchar = a[ctn];
        ctn += 1;
        continue;
      }
      if (a > b) {
        lexi_minimal += b[0];
        b = b.substr(1);
      } else if (a < b) {
        lexi_minimal += a[0];
        a = a.substr(1);
      } else {
        lexi_minimal += a[0];
        a = a.substr(1);
      }
    }
  }
  return lexi_minimal;
}

int main() {
  // ifstream input("inputs.txt");
  // ofstream output("outputs.txt");

  cout << morganAndString("Z", "ZZT") << endl;
  cout << morganAndString("ZZ", "ZZTA") << endl;
  cout << morganAndString("ZZ", "ZZT") << endl;
  cout << morganAndString("ZZ", "ZZZT") << endl;
  cout << morganAndString("ZA", "ZZT") << endl;
  cout << morganAndString("Z", "ZXY") << endl;
  cout << morganAndString("BB", "BBX") << endl;
  cout << morganAndString("BB", "BBA") << endl;
  cout << morganAndString("BXY", "B") << endl;
  cout << morganAndString("BXA", "BAT") << endl;

  // int num_cases;
  // input >> num_cases;
  // for(int i = 0; i < num_cases; i++) {
  //     string a, b;
  //     input >> a >> b;
  //     output << morganAndString(a, b) << "\n";
  // }

  // input.close();
  // output.close();

  return 0;
}
