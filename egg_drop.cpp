#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <limits>

std::vector<std::vector<int>> mem;

int solve(int n, int h) {
    if (n == 1 || h == 0 || h == 1) return h;
    if (mem[n][h] != -1) return mem[n][h];
    int ans = std::numeric_limits<int>::max();
    for (int f = 1; f <= h; ++f) {
        ans = std::min(ans, 1 + std::max(solve(n - 1, f - 1), solve(n, h - f)));
    }
    mem[n][h] = ans;
    return ans;
}

int main(int argc, char* argv[])
{
    if (argc != 3) std::cout << "Usage: ./a.out n h\n";
    int n = std::atoi(argv[1]);
    int h = std::atoi(argv[2]);
    mem.resize(n + 1, std::vector<int>(h + 1, -1));
    std::cout << solve(n, h) << std::endl;
    return 0;
}
