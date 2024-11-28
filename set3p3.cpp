#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

long long getDigit(long long num, long long exp) {
  return (std::abs(num) / exp) % 10;
}

void countingSort(std::vector<long long>& array, long long exp) {
  std::vector<long long> output(array.size());
  std::vector<long long> count(20, 0);

  for (long long num : array) {
    long long digit = getDigit(num, exp);
    count[digit + 10]++;
  }

  for (size_t i = 1; i < 20; i++) {
    count[i] += count[i - 1];
  }

  for (long long i = array.size() - 1; i >= 0; --i) {
    long long num = array[i];
    long long digit = getDigit(num, exp);
    output[count[digit + 10] - 1] = num;
    count[digit + 10]--;
  }

  for (size_t i = 0; i < array.size(); i++) {
    array[i] = output[i];
  }
}

void radixSort(std::vector<long long>& array) {
  std::vector<long long> negatives;
  std::vector<long long> positives;

  for (long long num : array) {
    if (num < 0) {
      negatives.push_back(num);
    } else {
      positives.push_back(num);
    }
  }

  if (!positives.empty()) {
    long long max_value = *std::max_element(positives.begin(), positives.end());
    for (long long exp = 1; exp <= max_value; exp *= 10) {
      countingSort(positives, exp);
    }
  }

  if (!negatives.empty()) {
    long long min_value = *std::min_element(negatives.begin(), negatives.end());
    for (long long exp = 1; exp <= std::abs(min_value); exp *= 10) {
      countingSort(negatives, exp);
    }
    std::reverse(negatives.begin(), negatives.end());
  }

  array.clear();
  array.insert(array.end(), negatives.begin(), negatives.end());
  array.insert(array.end(), positives.begin(), positives.end());
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }

  std::vector<long long> array(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  radixSort(array);

  for (int i = 0; i < n; ++i) {
    if (i > 0) std::cout << " ";
    std::cout << array[i];
  }
  std::cout << "\n";

  return 0;
}
