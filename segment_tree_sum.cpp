#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>

static const int N = 4;

typedef int elem_t;
typedef long long sum_t;

// s and e inclusive
void fill_segm(const std::vector<elem_t> &vec, std::vector<sum_t> &segm, size_t s, size_t e, size_t pos)
{
    if (s == e)
    {
        segm[s] = vec[s - vec.size() + 1];
        std::cout << "s: " << s << ", " << segm[s] << std::endl;
    }
    else
    {
        size_t mid = (s + e) / 2; // includes mid if odd
        fill_segm(vec, segm, s, mid, pos * 2 + 1); // left child, left half
        fill_segm(vec, segm, mid + 1, e, pos * 2 + 2); // right child, right half
        segm[pos] = segm[2*pos + 1] + segm[2*pos + 2];
    }
}

std::vector<sum_t> segm_tree(const std::vector<elem_t> &vec)
{
    std::vector<sum_t> segm(vec.size() * 2 - 1, -1);
    fill_segm(vec, segm, 0, segm.size() - 1, 0);
    return segm;
}

int main()
{
    std::vector<elem_t> vec(N);
    for (int i = 1; i <= N; ++i)
        vec.push_back(i);

    for (sum_t s : segm_tree(vec)) std::cout << s << " ";
    std::cout << std::endl;

    return 0;
}
