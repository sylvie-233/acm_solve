#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;
const int N = 1e5 + 5;

struct node {
    int l, r, mx;
};
int n;
node seg[N << 2];

void pushup(int i) {
    seg[i].mx = std::max(seg[i << 1].mx, seg[(i << 1) | 1].mx);
}

void build(int i, int l, int r) {
    seg[i].l = l;
    seg[i].r = r;
    if (l == r) {
        seg[i].mx = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
    pushup(i);
}

int get_max(int i, int l, int r) {
    if (seg[i].l == l && seg[i].r == r) {
        return seg[i].mx;
    }
    int mid = (seg[i].l + seg[i].r) /2;
    if (r <= mid) {
        return get_max(i << 1, l, r);
    } else if (l > mid) {
        return get_max((i << 1) | 1, l, r);
    }
    return std::max(get_max(i << 1, l, mid), get_max((i << 1) | 1, mid + 1, r));
}

void update(int i, int k, int v) {
    if (seg[i].l == k && seg[i].r == k) {
        seg[i].mx = std::max(seg[i].mx, v);
        return;
    }
    int mid = (seg[i].l + seg[i].r) / 2;
    if (k <= mid) {
        update(i << 1, k, v);
    } else {
        update((i << 1) | 1, k, v);
    }
    pushup(i);
}

struct t_w {
    int v1, v2, pos;
} ts[N], qs[N];

bool cmp(const t_w& t1, const t_w& t2) {
    if (t1.v1 != t2.v1) return t1.v1 > t2.v1;
    return t1.v2 > t2.v2;
}


class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<int> ans(queries.size());
        vector<int> uni;
        unordered_map<int, int> mp;
        int len_num = nums1.size(), len_q = queries.size();
        for (int i = 0; i < len_num; i++) {
            ts[i].v1 = nums1[i];
            ts[i].v2 = nums2[i];
            uni.push_back(nums2[i]);
        }
        for (int i = 0; i < len_q; i++) {
            qs[i].v1 = queries[i][0];
            qs[i].v2 = queries[i][1];
            qs[i].pos = i;
            uni.push_back(queries[i][1]);
        }
        sort(uni.begin(), uni.end());
        uni.erase(unique(uni.begin(), uni.end()), uni.end());
        n = uni.size();
        for (int i = 0; i < uni.size(); i++) {
            mp[uni[i]] = i + 1; // 记录离散后的序号
        }
        build(1, 1, n);
        
        sort(ts, ts + len_num, cmp);
        sort(qs, qs + len_q, cmp);

        int l = 0;
        for (int i = 0; i < len_q; i++) {
            while (l < len_num && ts[l].v1 >= qs[i].v1) {
                update(1, mp[ts[l].v2], ts[l].v1 + ts[l].v2);
                l++;
            }
            ans[qs[i].pos] = get_max(1, mp[qs[i].v2], n);
        }
        return ans;
    }
};