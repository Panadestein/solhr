#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> precomputed_solutions = {
  {{7, 11}, {11, 1}, {-2, 12}, {5, 4}, {12, -3}, {10, 3}, {9, 6}, {-12, -7}, {1, 11}, {-6, -6}, {12, -4}, {4, 12}},
  {{-12, 8}, {9, -6}, {10, 5}, {-5, 1}, {3, 3}, {3, 1}, {-10, -2}, {2, 1}, {7, 5}, {2, 2}, {6, 5}, {9, 7}},
  {{10, 5}, {-2, 1}, {3, 3}, {3, 1}, {10, 2}, {-7, -5}, {12, 8}, {2, 2}, {6, -5}, {5, 1}, {-9, 6}, {9, 7}},
  {{10, 2}, {-2, 2}, {12, 6}, {3, -1}, {-11, 3}, {-7, -5}, {2, 2}, {5, 1}, {9, 6}, {1, 1}, {6, 5}, {12, 8}},
  {{9, 7}, {3, 2}, {-10, 2}, {-5, 1}, {7, 1}, {7, -5}, {3, 1}, {-9, -6}, {4, 2}, {9, 6}, {6, 5}, {8, 4}},
  {{7, 3}, {-12, -7}, {6, -3}, {11, 5}, {12, 7}, {9, 3}, {7, 7}, {-12, 7}, {-3, 2}, {10, 1}, {4, 2}, {9, 7}},
  {{7, 3}, {10, 8}, {-5, 1}, {11, 4}, {9, 1}, {10, 6}, {-11, -2}, {12, 11}, {6, -6}, {12, 10}, {-11, 7}, {10, 9}},
  {{9, 7}, {-9, -1}, {12, 7}, {-10, 4}, {-3, 1}, {11, 1}, {12, 8}, {8, -4}, {12, 10}, {10, 3}, {1, 1}, {5, 3}},
  {{11, 7}, {3, 2}, {10, 8}, {11, 4}, {9, 2}, {-11, 1}, {11, 2}, {-7, 6}, {-11, -1}, {10, -8}, {10, 1}, {12, 11}},
  {{10, 8}, {8, 3}, {10, 5}, {8, 1}, {10, 6}, {12, 6}, {-11, 8}, {-10, 5}, {11, -5}, {10, 3}, {-11, -8}, {12, 8}},
  {{12, 2}, {8, 3}, {-4, 4}, {10, 4}, {8, 1}, {-10, -5}, {10, 6}, {9, 3}, {7, 5}, {-12, 8}, {7, -4}, {5, 2}},
  {{-9, 4}, {11, 4}, {12, 1}, {8, 2}, {7, 1}, {-10, -8}, {3, 1}, {9, -4}, {12, 4}, {9, 4}, {-12, 4}, {4, 1}},
  {{10, 8}, {12, 1}, {11, 4}, {5, 5}, {-9, -4}, {3, 1}, {9, -4}, {-6, 2}, {6, 2}, {9, 4}, {-12, 4}, {12, 3}},
  {{9, 7}, {-12, 12}, {-9, 5}, {6, 1}, {10, 6}, {-10, -6}, {9, -9}, {8, 7}, {9, 4}, {8, 5}, {10, 9}, {5, 3}},
  {{-9, 4}, {10, 10}, {6, 1}, {10, 6}, {-11, -3}, {10, -6}, {8, 7}, {-11, 11}, {9, 5}, {8, 5}, {10, 9}, {5, 3}},
  {{6, 4}, {9, 7}, {5, 5}, {3, 1}, {3, -2}, {-7, -5}, {-3, 2}, {-12, 6}, {5, 1}, {9, 6}, {6, 5}, {10, 2}},
  {{8, -7}, {3, 2}, {5, 1}, {-9, -1}, {10, 7}, {9, 2}, {-7, 5}, {11, 3}, {-11, 4}, {6, 2}, {12, 10}, {11, 6}},
  {{11, 4}, {8, 2}, {-12, -10}, {11, 8}, {8, 1}, {9, 8}, {9, 9}, {-12, 10}, {-7, 2}, {12, -10}, {11, 6}, {8, 4}},
  {{10, 8}, {12, 1}, {9, 1}, {7, 6}, {9, 3}, {11, 9}, {2, 1}, {-12, 11}, {9, -4}, {12, 11}, {-6, 6}, {-10, -1}},
  {{7, 3}, {11, 10}, {11, 5}, {10, 7}, {-8, -5}, {-8, 5}, {11, 3}, {8, -5}, {7, 5}, {9, 5}, {-9, 6}, {6, 5}},
  {{12, 2}, {9, 2}, {10, 7}, {-9, -4}, {11, 9}, {10, 6}, {-12, 11}, {9, -3}, {8, 8}, {11, 1}, {-7, 2}, {7, 2}}
};

vector<pair<int, int>> transform_set(const vector<pair<int, int>> &set,
                                     const string &transformation) {
  vector<pair<int, int>> new_set;
  for (const auto &coord : set) {
    int x = coord.first;
    int y = coord.second;
    if (transformation == "vertical") {
      new_set.push_back({x, -y});
    } else if (transformation == "horizontal") {
      new_set.push_back({-x, y});
    } else if (transformation == "diagonal") {
      new_set.push_back({y, x});
    }
  }
  return new_set;
}

void generate_all_transformations(vector<vector<pair<int, int>>> &solutions) {
  vector<vector<pair<int, int>>> new_solutions;
  for (const auto &set : solutions) {
    new_solutions.push_back(transform_set(set, "vertical"));
    new_solutions.push_back(transform_set(set, "horizontal"));
    new_solutions.push_back(transform_set(set, "diagonal"));
  }
  solutions.insert(solutions.end(), new_solutions.begin(), new_solutions.end());
}

int main() {
  int X, Y;
  cin >> X >> Y;

  // Use a LuT
  generate_all_transformations(precomputed_solutions);

  bool found = false;
  for (const auto &set : precomputed_solutions) {
    if (find(set.begin(), set.end(), make_pair(X, Y)) != set.end()) {
      for (const auto &coord : set) {
        if (coord != make_pair(X, Y)) {
          cout << coord.first << " " << coord.second << endl;
        }
      }
      found = true;
      break;
    }
  }

  return 0;
}
