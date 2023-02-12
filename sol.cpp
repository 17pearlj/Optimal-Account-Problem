class pq
{
  bool reverse;
public:
  pq(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const int& lhs, const int&rhs) const
  {
    if (reverse) return (lhs>rhs);
    else return (lhs<rhs);
  }
};
class Solution {
public:
    unordered_map<int, int> m;
    void buildMap(vector<vector<int>> t) {
        for (int i = 0; i < t.size(); i++) {
            if (m.find(t[i][0]) == m.end()) {
                m[t[i][0]] = 0;
            }
            if (m.find(t[i][1]) == m.end()) {
                m[t[i][1]] = 0;
            }
            m[t[i][0]] -= t[i][2];
            m[t[i][1]] += t[i][2];
        }
    }
    int getNonZeroI() {
        int i = -1;
        for (auto it : m) {
            if (it.second != 0) { i = it.first; break; }
        }
        return i;
    }
    int dfs(int i) {
        if (m[i] == 0) {
            i = getNonZeroI();
            if (i == -1) { return 0;}
        }
        int minV = INT_MAX;
        for (auto it : m) {
            if (it.second * m[i] < 0) {
                int me = m[i];
                int other = it.second;
                m[it.first] = me + other;
                m[i] = 0;
                minV = min(minV, 1 + dfs(it.first));
                m[it.first] = other;
                m[i] = me;
            }
        }
        return minV;

    }
    int minTransfers(vector<vector<int>>& transactions) {
        buildMap(transactions);
        return dfs(0);
    }
};
