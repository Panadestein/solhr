#include <bits/stdc++.h>

using namespace std;

void matrixRotation(vector<vector<int>> matrix, const int r) {
  // Number of layers
  int m = matrix.size();
  int n = matrix[0].size();
  int n_layer = min(m, n) / 2;

  // Some dummy variables
  int ctn;

  // The rotated matrix
  vector<vector<int>> rotated_matrix(m, vector<int>(n, 0));

  // Loop through layers
  for (int l = 0; l < n_layer; l++) {
    // Store current layer as counter clockwise vector
    vector<int> current_layer;

    // Left column unpack
    for (int i = l; i < m - l; i++) {
      current_layer.push_back(matrix[i][l]);
    }

    // Bottom row unpack
    for (int j = l + 1; j < n - l; j++) {
      current_layer.push_back(matrix[m - l - 1][j]);
    }

    // Right column unpack
    for (int i = m - l - 2; i >= l; i--) {
      current_layer.push_back(matrix[i][n - l - 1]);
    }

    // Top row unpack
    for (int j = n - l - 2; j >= l + 1; j--) {
      current_layer.push_back(matrix[l][j]);
    }

    // Perimeter of the layer
    int per = current_layer.size();

    // Effective rotation
    int r_eff = r % per;
    rotate(current_layer.rbegin(), current_layer.rbegin() + r_eff,
           current_layer.rend());

    // Rotated left column
    ctn = 0;
    for (int i = l; i < m - l; i++) {
      rotated_matrix[i][l] = current_layer[ctn];
      ctn += 1;
    }

    // Rotated bottom row
    for (int j = l + 1; j < n - l; j++) {
      rotated_matrix[m - l - 1][j] = current_layer[ctn];
      ctn += 1;
    }

    // Rotated right column
    for (int i = m - l - 2; i >= l; i--) {
      rotated_matrix[i][n - l - 1] = current_layer[ctn];
      ctn += 1;
    }

    // Rotated top row
    for (int j = n - l - 2; j >= l + 1; j--) {
      rotated_matrix[l][j] = current_layer[ctn];
      ctn += 1;
    }
  }
  // Print the rotated matrix
  for (const auto &row : rotated_matrix) {
    for (const auto &elem : row) {
      cout << elem << " ";
    }
    cout << endl;
  }
}

int main() {
  // 4x4 matrix
  vector<vector<int>> matrix = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  // number of rotations
  int r = 2;

  // call the function
  matrixRotation(matrix, r);

  return 0;
}
