#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

int solve(const vector<int>& vec) {
    vector<int> max_end = vec;
    vector<int> max_start = vec;
    vector<int> min_end = vec;
    vector<int> min_start = vec;
    for (int i = 1; i < max_end.size(); ++i) {
        max_end[i] = std::max(vec[i], max_end[i - 1] + vec[i]);
    }
    for (int i = max_start.size() - 2; i >= 0; --i) {
        max_start[i] = std::max(vec[i], max_start[i + 1] + vec[i]);
    }
    for (int i = 1; i < min_end.size(); ++i) {
        min_end[i] = std::min(vec[i], min_end[i - 1] + vec[i]);
    }
    for (int i = min_start.size() - 2; i >= 0; --i) {
        min_start[i] = std::min(vec[i], min_start[i + 1] + vec[i]);
    }

    vector<int> max_up_to = max_end;
    vector<int> min_up_to = min_end;
    vector<int> max_from = max_start;
    vector<int> min_from = min_start;
    for (int i = 1; i < max_up_to.size(); ++i) max_up_to[i] = std::max(max_up_to[i - 1], max_end[i]);
    for (int i = 1; i < min_up_to.size(); ++i) min_up_to[i] = std::min(min_up_to[i - 1], min_end[i]);
    for (int i = max_from.size() - 2; i >= 0; --i) max_from[i] = std::max(max_from[i + 1], max_start[i]);
    for (int i = min_from.size() - 2; i >= 0; --i) min_from[i] = std::min(min_from[i + 1], min_start[i]);

    int ans = 0;
    for (int i = 0; i < vec.size() - 1; ++i) {
        int diff = std::max(max_up_to[i] - min_from[i + 1], max_from[i + 1] - min_up_to[i] );
        if (diff > ans) {
            ans = diff;
        }
    }

    return ans;
}

int main()
{
    int n;
    std::cin >> n;
    vector<int> vec(n, 0);
    for (auto &n : vec) std::cin >> n;
    std::cout << solve(vec) << std::endl;
    return 0;
}
