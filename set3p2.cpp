#include <iostream>
#include <vector>

void CountingSort(const std::vector<int>& input, std::vector<int>& output, int min_value, int max_value) {
  int range = max_value - min_value + 1;
  std::vector<int> count(range, 0);

  for (int num : input) {
    count[num - min_value]++;
  }

  int index = 0;
  for (int i = 0; i < range; ++i) {
    while (count[i] > 0) {
      output[index++] = i + min_value;
      count[i]--;
    }
  }
}

int main() {
  // Отключить синхронизацию между iostream и stdio.
  std::ios::sync_with_stdio(false);
  // Отключить синхронизацию между std::cin и std::cout.
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> A(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> A[i];
  }

  const int min_value = -1000000;
  const int max_value = 1000000;

  std::vector<int> sorted_A(n);

  CountingSort(A, sorted_A, min_value, max_value);

  for(int num : sorted_A) {
    std::cout << num << " ";
  }

  std::cout << "\n";
  return 0;
}