#include <bits/stdc++.h>

using namespace std;

#define N 1000
#define M 10000
#define pii pair<int, int>
#define mp make_pair

//k短路
//先建以1为根的最短路树
//然后把不在最短路上的边拿出来

int n, m, k;
int S = 1, head[N+5], eid, d[N+5], inT[M+5], done[N+5];
int chosen[N+5];
int dfn_clk, dfn[N+5], en[N+5];
vector<int> G[N+5];
vector<int> r[N+5];

struct Node {
  int tail, w;
  bool operator < (const Node &rhs) const {
    return w > rhs.w;
  }
};
priority_queue<Node> q;

struct Edge {
  int u, v, w;
}e[M+5];

struct Edge0 {
  int next, to, w, id;
}edges[M+5];

struct HeapNode {
  int u, w;
  bool operator < (const HeapNode &rhs) const {
    return w > rhs.w;
  }
};

void add_edge(int u, int v, int w, int id) {
  edges[++eid].next = head[u];
  edges[eid].to = v;
  edges[eid].w = w;
  edges[eid].id = id;
  head[u] = eid;
}

void dij() {
  memset(d, 0x3f, sizeof d);
  d[S] = 0;
  priority_queue<HeapNode> pq;
  pq.push(HeapNode{S, d[S]});
  while(!pq.empty()) {
    int u = pq.top().u; pq.pop();
    if(done[u]) continue;
    done[u] = 1;
    for(int i = head[u], v, w; i; i = edges[i].next) {
      v = edges[i].to, w = edges[i].w;
      if(d[v] > d[u]+w) {
        chosen[v] = edges[i].id;
        d[v] = d[u]+w;
        pq.push(HeapNode{v, d[v]});
      }
    }
  }
}

void dfs(int u) {
  dfn[u] = ++dfn_clk;
  for(int i = 0; i < G[u].size(); ++i) dfs(G[u][i]);
  en[u] = dfn_clk;
}

bool is_fa(int x, int y) { //y是不是x的祖先
  return dfn[x] <= en[y] && dfn[x] >= dfn[y];
}

void build_T() {
  dij();
  for(int i = 2; i <= n; ++i) {
    int x = e[chosen[i]].u, y = e[chosen[i]].v;
    G[y].push_back(x);
    inT[chosen[i]] = 1;
  }
  dfs(1);
}

int main() {
  freopen("data.in", "r", stdin);
  freopen("my.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 1, x, y, z; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    add_edge(y, x, z, i);
    e[i] = Edge{x, y, z};
  }
  build_T();
  for(int i = 1; i <= m; ++i) {
    if(inT[i]) continue;
    for(int j = 1; j <= n; ++j)
      if(is_fa(j, e[i].u)) r[j].push_back(i);
  }
  q.push(Node{n, 0});
  while(!q.empty() && k--) {
    Node u = q.top(); q.pop();
    if(d[n]+u.w < 0x3f3f3f3f) printf("%d\n", d[n]+u.w);
    else printf("-1\n");
    for(int i = 0; i < r[u.tail].size(); ++i) {
      q.push(Node{e[r[u.tail][i]].v, u.w+e[r[u.tail][i]].w+d[e[r[u.tail][i]].v]-d[e[r[u.tail][i]].u]});
    }
  }
  while(k > 0) printf("-1\n"), k--;
  return 0;
}