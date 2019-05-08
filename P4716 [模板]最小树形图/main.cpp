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

#define N 100
#define M 10000

struct Edge {
  int from, to, w;
}e[M+5];

int minw[N+5], id[N+5], fa[N+5], top[N+5];

int solve(int n, int m, int r) {
  int ans = 0;
  while(1) {
    int tot = 0;
    for(int i = 1; i <= n; ++i) id[i] = top[i] = 0, minw[i] = INF;
    for(int i = 1; i <= m; ++i)
      if(e[i].from != e[i].to && e[i].w < minw[e[i].to]) fa[e[i].to] = e[i].from, minw[e[i].to] = e[i].w;
    minw[r] = 0;
    for(int i = 1; i <= n; ++i) {
      if(minw[i] == INF) return -1;
      ans += minw[i];
      int u;
      for(u = i; u != r && top[u] != i && !id[u]; u = fa[u]) top[u] = i;
      if(u != r && !id[u]) {
        id[u] = ++tot;
        for(int v = fa[u]; v != u; v = fa[v]) id[v] = tot;
      }
    }
    if(!tot) return ans;
    for(int i = 1; i <= n; ++i) if(!id[i]) id[i] = ++tot;
    for(int i = 1; i <= m; ++i) {
      int t = minw[e[i].to];
      if((e[i].from = id[e[i].from]) != (e[i].to = id[e[i].to])) e[i].w -= t;
    }
    n = tot, r = id[r];
  }
}

int main() {
  int n, m, r;
  scanf("%d%d%d", &n, &m, &r);
  for(int i = 1, x, y, z; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    e[i] = Edge{x, y, z};
  }
  printf("%d\n", solve(n, m, r));
  return 0;
}