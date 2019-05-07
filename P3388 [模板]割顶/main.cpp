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
#define DEF 0x8f8f8f8f
#define vi vector<int>
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 100000

int n, m;
vi G[N+5];
int low[N+5], dfn[N+5], dfn_clk, cut[N+5];

void tarjan(int u, int rt) {
  dfn[u] = low[u] = ++dfn_clk;
  int cnt = 0;
  for(int i = 0; i < G[u].size(); ++i) {
    int v = G[u][i];
    if(!dfn[v]) {
      tarjan(v, rt);
      low[u] = min(low[u], low[v]);
      cnt++;
      if(u != rt && low[v] >= dfn[u]) cut[u] = 1;
    }
    else low[u] = min(low[u], dfn[v]);
  }
  if(u == rt && cnt > 1) cut[u] = 1;
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    G[x].pb(y), G[y].pb(x);
  }
  for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i, i);
  int cnt = 0;
  for(int i = 1; i <= n; ++i) cnt += cut[i];
  printf("%d\n", cnt);
  for(int i = 1; i <= n; ++i) if(cut[i]) printf("%d ", i);
  return 0;
}