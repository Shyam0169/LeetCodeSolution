// 2022.06.04
// use binary search on path length
class Solution {
private:
    static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        int res = 0;
        int left = 0;
        int right = 999999;
        while(left <= right) {
            int mid = left + (right - left) / 2; // mid refers to cur max path length
            vector<bool> seen(m * n, false); // record seen point
            queue<pair<int, int>> que;
            que.emplace(0, 0);
            seen[0] = true;
            while(!que.empty()) {
                auto [x, y] = que.front();
                que.pop();
                for(int i = 0; i < 4; i++) {
                    int nx = x + dirs[i][0];
                    int ny = y + dirs[i][1];
                    if(nx >= 0 && nx < m && ny >= 0 && ny < n && !seen[nx * n + ny] && abs(heights[x][y] - heights[nx][ny]) <= mid) {
                        que.emplace(nx, ny);
                        seen[nx * n + ny] = true;
                    }
                }
            }
            if(seen[m * n - 1]) {
                res = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return res;
    }
};

// unionfindset
class UnionFindSet {
public:
    UnionFindSet(int n) {
        ranks_ = vector<int>(n + 1, 0);
        parent_ = vector<int>(n + 1, 0);
        for(int i = 0; i < parent_.size(); i++) {
            parent_[i] = i;
        }
    }
    int Find(int u) {
        if(u != parent_[u]) {
            parent_[u] = Find(parent_[u]);
        }
        return parent_[u];
    }
    bool Union(int u, int v) {
        int pu = Find(u);
        int pv = Find(v);
        if(pu == pv) {
            return false;
        }
        if(ranks_[pu] < ranks_[pv]) {
            parent_[pu] = pv;
        }
        else if(ranks_[pu] > ranks_[pv]) {
            parent_[pv] = pu;
        }
        else {
            parent_[pv] = pu;
            ranks_[pu]++;
        }
        return true;
    }
private:
    vector<int> ranks_;
    vector<int> parent_;
};

struct Edge {
    int u;
    int v;
    int w;
    Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
    bool operator < (const Edge& that) const {
        return w < that.w;
    }
};

class Solution {
// private:
//     static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<Edge> edges;
        // build edge set
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int id = i * n + j;
                if(i > 0) {
                    edges.emplace_back(id - n, id, abs(heights[i][j] - heights[i - 1][j]));
                }
                if(j > 0) {
                    edges.emplace_back(id - 1, id, abs(heights[i][j] - heights[i][j - 1]));
                }
            }
        }
        sort(edges.begin(), edges.end());
        UnionFindSet set(m * n);
        for(const auto& edge : edges) {
            set.Union(edge.u, edge.v);
            int pu = set.Find(0);
            int pv = set.Find(m * n - 1);
            if(pu == pv) {
                return edge.w;
            }
        }
        return 0;
    }
};

// shortest path
struct Dist {
    int u;
    int v;
    int w;
    Dist(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
    bool operator < (const Dist& that) const {
        return w > that.w;
    }
};

class Solution {
private:
    static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        priority_queue<Dist> que;
        vector<bool> seen(m * n, false);
        vector<int> dist(m * n, 0x3f3f3f3f);
        que.emplace(0, 0, 0);
        dist[0] = 0;
        while(!que.empty()) {
            auto [u, v, w] = que.top();
            que.pop();
            if(seen[u * n + v]) {
                continue;
            }
            seen[u * n + v] = true;
            dist[u * n + v] = w;
            for(int i = 0; i < 4; i++) {
                int nu = u + dirs[i][0];
                int nv = v + dirs[i][1];
                if(nu >= 0 && nu < m && nv >= 0 && nv < n && !seen[nu * n + nv]) {
                    que.emplace(nu, nv, max(w, abs(heights[u][v] - heights[nu][nv])));
                }
            }
        }
        return dist[m * n - 1];
    }
};