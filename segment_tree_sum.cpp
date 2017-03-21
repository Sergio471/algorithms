#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <cassert>

class SegmentTree
{
    typedef int elem_t;
    typedef long long sum_t;

    std::vector<sum_t> segm; // holds segment tree
    const size_t orig_size; // original vector size

    // qs - query start pos (inclusive)
    // qe - query end pos (inclusive)
    // [ts; te] -- range for which segm[pos] gives answer
    // pos - current pos in segm
    sum_t query2(size_t qs, size_t qe, size_t ts, size_t te, size_t pos)
    {
        if (qs > te || qe < ts) // no overlap
        {
            return 0;
        }
        else if (qs <= ts && qe >= te) // total overlap
        {
            return segm[pos];
        }
        else // partial overlap
        {
            size_t tmid = (ts + te) / 2;
            return query2(qs, qe, ts, tmid, 2*pos + 1) +
                   query2(qs, qe, tmid + 1, te, 2*pos + 2);
        }
    }

    // s and e - current range (both inclusive)
    // pos - current pos in segm
    void fill_segm(const std::vector<elem_t>& vec, std::vector<sum_t>& segm, size_t s, size_t e, size_t pos)
    {
        if (s == e)
        {
            segm[pos] = vec[s];
        }
        else
        {
            size_t mid = (s + e) / 2; // includes mid if odd
            size_t left_ch_pos = pos * 2 + 1;
            size_t right_ch_pos = pos * 2 + 2;
            fill_segm(vec, segm, s, mid, left_ch_pos); // left child, left half
            fill_segm(vec, segm, mid + 1, e, right_ch_pos); // right child, right half
            segm[pos] = segm[left_ch_pos] + segm[right_ch_pos];
        }
    }

public:

    SegmentTree(const std::vector<elem_t>& vec) : orig_size(vec.size())
    {
        int last_lvl_len = 1;
        while (last_lvl_len < vec.size()) last_lvl_len *= 2;
        segm.resize(last_lvl_len * 2 - 1, -1);

        fill_segm(vec, segm, 0, vec.size() - 1, 0);
    }

    // qs - query start pos (inclusive)
    // qe - query end pos (inclusive)
    sum_t query(size_t s, size_t e)
    {
        if (!(e < orig_size && s <= e)) return 0;
        return query2(s, e, 0, orig_size - 1, 0);
    }
};

int main()
{
    /*
    SegmentTree st{{1,3,5,7,9,11}};

    std::cout << st.query(0, 5) << std::endl;
    std::cout << st.query(0, 0) << std::endl;
    std::cout << st.query(5, 5) << std::endl;
    std::cout << st.query(1, 3) << std::endl;
    */

    const int N = 500;
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) v[i] = i;
    SegmentTree st{v};
    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < N; ++j)
        {
            const int true_sum = (i + j) * (j - i + 1) / 2;
            assert(true_sum == st.query(i, j));
        }
    }

    return 0;
}
