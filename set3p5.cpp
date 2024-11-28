#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <string>
#include <cctype>
#include <random>

std::vector<int> randomVector(int n) {
  std::vector<int> vec(n);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1);

  for (int i = 0; i < n; ++i) {
    vec[i] = dist(gen);
  }

  return vec;
}

std::vector<int> multiply(const std::vector<std::vector<int>>& A, const std::vector<int>& col, int n) {
  std::vector<int> result(n, 0);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      result[i] = (result[i] + A[i][j] * col[j]) % 2;
    }
  }

  return result;
}

bool checkMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B,
                   const std::vector<std::vector<int>>& C, int n) {
  for (int attempt = 0; attempt < 5; ++attempt) {
    std::vector<int> r = randomVector(n);
    std::vector<int> B_r = multiply(B, r, n);
    std::vector<int> A_B_r = multiply(A, B_r, n);
    std::vector<int> C_r = multiply(C, r, n);
    if (A_B_r != C_r) {
      return false;
    }
  }
  return true;
}


std::vector<int> hexToBin(char hex) {
  int value;
  std::vector<int> row(4);
  value = hex <= '9' ? (hex - '0') : (hex - 'A' + 10);
  std::bitset<4> bin(value);
  int ind = 0;
  for (int i = 3; i >= 0; --i) {
    row[ind++] = static_cast<int>(bin[i]);
  }
  return row;
}



std::vector<std::vector<int>> convertMatrix(int n) {
  std::vector<std::vector<int>> binary_matrix(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    int ind = 0;
    for (int j = 0; j < (n + 3) / 4 ; ++j) {
      char c;
      std::cin >> c;
      std::vector<int> temp = hexToBin(c);
      for (int k = 0; k < temp.size() && k + 4 * j < n; ++k) {
        binary_matrix[i][ind++] = temp[k];
      }
    }
  }
  return binary_matrix;
}



int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }

  std::vector<std::vector<int>> A = convertMatrix(n);
  std::vector<std::vector<int>> B = convertMatrix(n);
  std::vector<std::vector<int>> C = convertMatrix(n);

  if (checkMultiply(A, B, C, n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  std::cout << "\n";
  return 0;
}
