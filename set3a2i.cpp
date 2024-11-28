#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& array, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = array[i];
    int j = i - 1;
    while (j >= left && array[j] > key) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

void merge(std::vector<int>& array, int left, int middle, int right) {
  int n1 = middle - left + 1;
  int n2 = right - middle;

  std::vector<int> left_array(n1);
  std::vector<int> right_array(n2);

  for (size_t i = 0; i < n1; ++i) {
    left_array[i] = array[left + i];
  }

  for (size_t i = 0; i < n2; ++i) {
    right_array[i] = array[middle + 1 + i];
  }

  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (left_array[i] <= right_array[j]) {
      array[k++] = left_array[i++];
    } else {
      array[k++] = right_array[j++];
    }
  }

  while (i < n1) {
    array[k++] = left_array[i++];
  }

  while (j < n2) {
    array[k++] = right_array[j++];
  }
}

void hybridSort(std::vector<int>& array, int left, int right) {
  const int threshold = 15;

  if (right - left + 1 <= threshold) {
    insertionSort(array, left, right);
  } else {
    int middle = left + (right - left) / 2;
    hybridSort(array, left, middle);
    hybridSort(array, middle + 1, right);
    merge(array, left, middle, right);
  }
}

int main() {
  int n;
  std::cin >> n;

  if (n == 0) {
    return 0;
  }

  std::vector<int> array(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  hybridSort(array, 0, n - 1);

  for (size_t i = 0; i < n; ++i) {
    std::cout << array[i] << " ";
  }

  std::cout << "\n";
  return 0;
}
