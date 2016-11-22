#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>

std::vector<int> nom = {1, 2};

std::unordered_map<int, std::vector<int>> mem;

std::vector<int> f(int n)
{
    if (std::find(nom.begin(), nom.end(), n) != nom.end()) return {n};

    if (!mem[n].empty()) return mem[n];
 
    int min_len = 9999999;
    std::vector<std::vector<int>> answers;
    for (int nm : nom)
    {
        if (n - nm > 0)
        {
            answers.push_back(f(n - nm));
            if (!answers.back().empty() && answers.back().size() < min_len) min_len = answers.back().size();
        }
    }

    for (int i = 0; i < answers.size(); ++i)
    {
        if (answers[i].size() == min_len)
        {
            auto a2 = answers[i];
            a2.push_back(nom[i]);
            mem[n] = a2;
            return mem[n];
        }
    }
    return std::vector<int>{};
}

int main()
{
    int N;
    std::cin >> N;
    std::cout << N << std::endl;
    for (auto c : f(N)) std::cout << c;
    std::cout << std::endl;
    return 0;
}
