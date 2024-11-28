#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

double estimate(const std::vector<int> &spots) {
  size_t n = spots.size();
  std::vector<bool> diag1(2 * n - 1);
  std::vector<bool> diag2(2 * n - 1);
  int result = 0;
  for (int i = 0; i < n; ++i) {
    size_t d1 = i + spots[i];
    size_t d2 = i - spots[i] + (n - 1);
    if (!diag1[d1] && !diag2[d2]) {
      result++;
      diag1[d1] = true;
      diag2[d2] = true;
    }
  }
  return result;
}

double rnd(std::mt19937& gen) {
  std::uniform_real_distribution<> dist(0.0, 1.0);
  return dist(gen);
}

int randomIndex(int n, std::mt19937& gen) {
  std::uniform_int_distribution<> dist(0, n - 1);
  return dist(gen);
}

std::vector<int> solve(int n) {
  std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

  std::vector<int> spots(n, 0);
  for (int i = 0; i < n; ++i) {
    spots[i] = i;
  }

  std::shuffle(spots.begin(), spots.end(), gen);

  double energy = estimate(spots);
  double Ti = 1.0;

  while (energy < n) {
    Ti *= 0.99;

    std::vector<int> new_spots = spots;
    int idx1 = randomIndex(n, gen);
    int idx2 = randomIndex(n, gen);
    std::swap(new_spots[idx1], new_spots[idx2]);

    double new_energy = estimate(new_spots);
    double dE = new_energy - energy;

    if (new_energy > energy || rnd(gen) < std::exp(dE / Ti)) {
      spots = new_spots;
      energy = new_energy;
    }
  }

  return spots;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  if (n < 5 || n > 200) {
    return 0;
  }

  std::vector<int> result = solve(n);

  for (int spot : result) {
    std::cout << spot + 1 << " ";
  }

  std::cout << "\n";
  return 0;
}