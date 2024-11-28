#include <iostream>
#include <vector>
#include <string>

struct Fraction {
    std::string original;
    int numerator;
    int denominator;
    double value;
};

Fraction parseFraction(const std::string& str) {
  size_t slash_pos = str.find('/');
  int numerator = std::stoi(str.substr(0, slash_pos));
  int denominator = std::stoi(str.substr(slash_pos + 1));
  return {str, numerator, denominator, static_cast<double>(numerator) / denominator};
}

void merge(std::vector<Fraction>& fractions, int left, int mid, int right) {
  std::vector<Fraction> temp;
  int i = left;
  int j = mid + 1;

  while (i <= mid && j <= right) {
    if (fractions[i].value <= fractions[j].value) {
      temp.push_back(fractions[i++]);
    } else {
      temp.push_back(fractions[j++]);
    }
  }

  while (i <= mid) {
    temp.push_back(fractions[i++]);
  }
  while (j <= right) {
    temp.push_back(fractions[j++]);
  }

  for (int k = left; k <= right; ++k) {
    fractions[k] = temp[k - left];
  }
}

void mergeSort(std::vector<Fraction>& fractions, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(fractions, left, mid);
    mergeSort(fractions, mid + 1, right);
    merge(fractions, left, mid, right);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  if (n <= 0) {
    return 0;
  }

  std::vector<Fraction> fractions(n);

  for (int i = 0; i < n; ++i) {
    std::string fraction_str;
    std::cin >> fraction_str;
    fractions[i] = parseFraction(fraction_str);
  }

  mergeSort(fractions, 0, n - 1);

  for (const auto& fraction : fractions) {
    std::cout << fraction.original << " ";
  }

  std::cout << "\n";
  return 0;
}
