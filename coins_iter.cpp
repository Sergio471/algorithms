#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <limits>

static const int MAX = std::numeric_limits<int>::max(); 

std::vector<int> coins = {5, 6};

std::unordered_map<int, int> f(int n)
{
    std::vector<int> counts(n + 1, MAX);
    std::vector<int> last(n + 1, -1);

    for (int c : coins)
    {
        counts[c] = 1;
        last[c] = c;
    } 

    for (int i = 1; i <= n; ++i)
    {
        for (int c : coins)
        {
            if (i - c >= 1 && counts[i - c] != -1)
            {
                if (counts[i - c] < counts[i])
                {
                    counts[i] = counts[i - c] + 1;
                    last[i] = c;
                }             
            }
        }
    }

    std::unordered_map<int, int> ans;

    if (counts[n] != MAX)
    {
        int i = n;
        while (counts[i] != 1)
        {
            ++ans[last[i]];
            i -= last[i];
        }
        ++ans[last[i]];
    }

    return ans;
}

int main()
{
    int N;
    std::cin >> N;
    for (auto& p : f(N)) std::cout << p.first << " -> " << p.second << std::endl;
    return 0;
}
