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
int low[N+5], dfn[N+5], dfn_clk, cut[N+5], stk[N+5], tp;
int bcc_id;
vi bcc[N+5];

void clear() {
  for(int i = 1; i <= n; ++i) G[i].clear(), dfn[i] = 0, cut[i] = 0;
  n = bcc_id = tp = dfn_clk = 0;
}

void tarjan(int u, int rt) {
  dfn[u] = low[u] = ++dfn_clk;
  stk[++tp] = u;
  int cnt = 0;
  for(int i = 0; i < G[u].size(); ++i) {
    int v = G[u][i];
    if(!dfn[v]) {
      tarjan(v, rt);
      low[u] = min(low[u], low[v]);
      cnt++;
      if(low[v] == dfn[u]) {
        bcc_id++;
        bcc[bcc_id].clear();
        for(int x = 0; x != v; --tp) {
          x = stk[tp];
          bcc[bcc_id].pb(x);
        }
        bcc[bcc_id].pb(u);
      }
      if(u != rt && low[v] >= dfn[u]) cut[u] = 1;
    }
    else low[u] = min(low[u], dfn[v]);
  }
  if(u == rt && cnt > 1) cut[u] = 1;
}

int main() {
  int kase = 0;
  while(~scanf("%d", &m) && m) {
    clear();
    for(int i = 1, x, y; i <= m; ++i) {
      scanf("%d%d", &x, &y);
      n = max(n, max(x, y));
      G[x].pb(y), G[y].pb(x);
    }
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i, i);
    printf("Case %d: ", ++kase);
    ll ans1 = 0, ans2 = 1;
    for(int i = 1; i <= bcc_id; ++i) {
      int vcnt = 0, sz = bcc[i].size();
      for(int j = 0; j < sz; ++j) if(cut[bcc[i][j]]) vcnt++;
      if(vcnt == 0) {
        ans1 += 2;
        ans2 *= 1LL*sz*(sz-1)/2;
      }
      else if(vcnt == 1) {
        ans1++;
        ans2 *= sz-1;
      }
    }
    printf("%lld %lld\n", ans1, ans2);
  }
  return 0;
}