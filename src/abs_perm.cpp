#include <iostream>
#include <vector>

std::vector<int> absolutePermutation(int n, int k) {
    std::vector<int> perm(n);
    std::vector<int> defa(1, -1);

    if (k == 0) {
        for (int i = 0; i < n; ++i) {
            perm[i] = i + 1;
        }
    } else if ((n % (2 * k)) != 0) {
        return defa;
    } else {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                perm[i + j] = i + j + k + 1;
                perm[i + j + k] = i + j + 1;
            }
        }
    }
    return perm;
}

void testAbsolutePermutation(int n, int k) {
    std::vector<int> result = absolutePermutation(n, k);
    for (int value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test cases
    testAbsolutePermutation(66, 60);
    testAbsolutePermutation(95, 22);
    testAbsolutePermutation(48, 0);
    testAbsolutePermutation(2, 0);
    testAbsolutePermutation(94, 47);
    testAbsolutePermutation(80, 0);
    testAbsolutePermutation(63, 0);
    testAbsolutePermutation(2, 1);
    testAbsolutePermutation(65, 0);
    testAbsolutePermutation(42, 0);

    return 0;
}