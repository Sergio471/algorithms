#include <string>
#include <vector>

/*
 *  Finds the length of lcs.
 */
size_t lcs(const std::string &s1, const std::string &s2)
{
    size_t res = 0;

    if (!s1.empty() && !s2.empty())
    {
        // Init memoization 2D matrix with zeros
        std::vector<std::vector<int>> mem;
        mem.resize(s1.size() + 1);
        for (auto &v : mem) v.resize(s2.size() + 1, 0);

        // Main logic
        for (int i = 1; i <= s1.size(); ++i)
        {
            for (int j = 1; j <= s2.size(); ++j)
            {
                if (s1[i - 1] == s2[j - 1]) mem[i][j] = mem[i-1][j-1] + 1;
                else mem[i][j] = std::max(mem[i-1][j], mem[i][j-1]);
            }
        }

        // Result is in the last cell
        res = mem[s1.size()][s2.size()];
    }

    return res;
}
