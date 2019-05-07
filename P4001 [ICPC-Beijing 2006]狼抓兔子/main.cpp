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

#define N 4000000

struct heapNode {
  ll d;
  int u;
  bool operator < (const heapNode &rhs) const {
    return d > rhs.d;
  }
};

struct Edge {
  int next, to, w;
}e[2*N+5];

int n, m, S, T;
int head[N+5], eid;
ll d[N+5];
bool vis[N+5];

void addEdge(int u, int v, int w) {
  e[++eid] = Edge{head[u], v, w};
  head[u] = eid;
  e[++eid] = Edge{head[v], u, w};
  head[v] = eid;
}

void dij() {
  priority_queue<heapNode> pq;
  d[S] = 0;
  pq.push(heapNode{0, S});
  while(!pq.empty()) {
    int u = pq.top().u; pq.pop();
    if(vis[u]) continue;
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w;
      if(d[v] > d[u]+w) {
        d[v] = d[u]+w;
        pq.push(heapNode{d[v], v});
      }
    }
  }
}

int main() {
  S = N+1, T = N+2;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= 2*n*m; ++i) head[i] = 0, d[i] = IINF, vis[i] = 0;
  head[S] = head[T] = vis[S] = vis[T] = 0, d[S] = d[T] = IINF;
  eid = 0;
  int rowcnt = (m-1)*2, minv = INF;
  for(int i = 1, w; i < m; ++i) {
    scanf("%d", &w);
    addEdge(2*i, T, w);
    minv = min(minv, w);
  }
  for(int i = 2, w; i < n; ++i) {
    for(int j = 1; j < m; ++j) {
      scanf("%d", &w);
      minv = min(minv, w);
      addEdge((i-2)*rowcnt+2*j-1, (i-1)*rowcnt+2*j, w);
   }
  }
  for(int i = 1, w; i < m; ++i) {
    scanf("%d", &w);
    minv = min(minv, w);
    addEdge(S, (n-2)*rowcnt+2*i-1, w);
  }
  for(int i = 1, w; i < n; ++i) {
    scanf("%d", &w);
    minv = min(minv, w);
    addEdge(S, (i-1)*rowcnt+1, w);
    for(int j = 2; j < m; ++j) {
      scanf("%d", &w);
      minv = min(minv, w);
      addEdge((i-1)*rowcnt+2*(j-1), (i-1)*rowcnt+2*(j-1)+1, w);
    }
    scanf("%d", &w);
    minv = min(minv, w);
    addEdge(i*rowcnt, T, w);
  }
  for(int i = 1, w; i < n; ++i) {
    for(int j = 1; j < m; ++j) {
      scanf("%d", &w);
      minv = min(minv, w);
      addEdge((i-1)*rowcnt+2*j-1, (i-1)*rowcnt+2*j, w);
    }
  }
  dij();
  if(n == 1 || m == 1) printf("%d\n", minv);
  else printf("%lld\n", d[T]);
  return 0;
}