#include <algorithm>
#include  <iostream>
#include   <cstdlib>
#include   <cstring>
#include    <cstdio>
#include    <string>
#include    <vector>
#include     <cmath>
#include     <ctime>
#include     <queue>
#include       <map>
#include       <set>

using namespace std;

#define ull unsigned long long
#define pii pair<int, int>
#define uint unsigned int
#define mii map<int, int>
#define lbd lower_bound
#define ubd upper_bound
#define INF 0x3f3f3f3f
#define IINF 0x3f3f3f3f3f3f3f3fLL
#define DEF 0x8f8f8f8f
#define DDEF 0x8f8f8f8f8f8f8f8fLL
#define vi vector<int>
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 510

int n, m, q;

struct Dinic {
  struct Edge {
    int to, cap, flow;
  };
  vi G[N+5];
  vector<Edge> edges;
  int d[N+5], cur[N+5];
  void clear() {
    for(int i = 0; i < edges.size(); ++i) {
      Edge &e = edges[i];
      e.flow = 0;
    }
  }
  void addEdge(int from, int to, int cap) {
    edges.pb(Edge{to, cap, 0}), edges.pb(Edge{from, cap, 0});
    G[from].pb(edges.size()-2), G[to].pb(edges.size()-1);
  }
  bool bfs(int S, int T) {
    static queue<int> q;
    memset(d, -1, sizeof d);
    q.push(S);
    d[S] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(int i = 0; i < G[u].size(); ++i) {
        Edge &e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] == -1) {
          d[e.to] = d[u]+1;
          q.push(e.to);
        }
      }
    }
    return ~d[T];
  }
  int dfs(int u, int a, int T) {
    if(u == T || !a) return a;
    int flow = 0, f;
    for(int &i = cur[u]; i < G[u].size(); ++i) {
      Edge &e = edges[G[u][i]];
      if(d[e.to] == d[u]+1 && (f = dfs(e.to, min(e.cap-e.flow, a), T)) > 0) {
        flow += f;
        a -= f;
        e.flow += f;
        edges[G[u][i]^1].flow -= f;
        if(!a) break;
      }
    }
    return flow;
  }
  int maxFlow(int S, int T) {
    clear();
    int ret = 0;
    while(bfs(S, T)) {
      memset(cur, 0, sizeof cur);
      ret += dfs(S, INF, T);
    }
    return ret;
  }
}solver;

struct GomoryHu {
  struct Edge {
    int next, to, w;
  }e[3000+5];
  int head[N+5], eid;
  int d[N+5][N+5];
  void init() {
    memset(head, 0, sizeof head);
    eid = 0;
  }
  void addEdge(int from, int to, int w) {
    e[++eid].next = head[from];
    e[eid].to = to;
    e[eid].w = w;
    head[from] = eid;
  }
  void dfs(int u, int fa, int *d) {
    for(int i = head[u]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w;
      if(v == fa) continue;
      d[v] = min(d[u], w);
      dfs(v, u, d);
    }
  }
  void build(vi &s) {
    if(s.size() == 1) return ;
    int x = s[0], y = s[1];
    int w = solver.maxFlow(x, y);
    addEdge(x, y, w), addEdge(y, x, w);
    vi s1, s2;
    for(int i = 0; i < s.size(); ++i) {
      int v = s[i];
      if(~solver.d[v]) s1.pb(v);
      else s2.pb(v);
    }
    build(s1), build(s2);
    if(s.size() == n) for(int i = 1; i <= n; ++i) d[i][i] = INF, dfs(i, 0, d[i]);
  }
  int query(int x, int y) {
    return d[x][y];
  }
}tr;

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y, z; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    solver.addEdge(x, y, z);
  }
  vi s;
  for(int i = 1; i <= n; ++i) s.pb(i);
  tr.init();
  tr.build(s);
  scanf("%d", &q);
  for(int i = 1, x, y; i <= q; ++i) {
    scanf("%d%d", &x, &y);
    printf("%d\n", tr.query(x, y));
  }
  return 0;
}