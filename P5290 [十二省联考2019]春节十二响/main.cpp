#include <bits/stdc++.h>

using namespace std;

#define N 200000
#define ll long long

int n, rt[N+5], id;
vector<int> G[N+5];
ll tmp[N+5], a[N+5];
priority_queue<ll> pq[N+5];

void dfs(int u) {
  rt[u] = ++id;
  for(int i = 0; i < G[u].size(); ++i) {
    int v = G[u][i];
    dfs(v);
    if(pq[rt[u]].size() < pq[rt[v]].size()) swap(rt[u], rt[v]);
    int tot = 0;
    while(!pq[rt[v]].empty()) {
      tmp[++tot] = max(pq[rt[u]].top(), pq[rt[v]].top());
      pq[rt[u]].pop(), pq[rt[v]].pop();
    }
    for(int j = 1; j <= tot; ++j) pq[rt[u]].push(tmp[j]);
  }
  pq[rt[u]].push(a[u]);
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
  for(int i = 2, x; i <= n; ++i) {
    scanf("%d", &x);
    G[x].push_back(i);
  }
  dfs(1);
  ll ans = 0;
  while(!pq[rt[1]].empty()) ans += pq[rt[1]].top(), pq[rt[1]].pop();
  printf("%lld\n", ans);
  return 0;
}