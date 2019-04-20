#include <bits/stdc++.h>

using namespace std;

#define N 500000
#define M 200000

int n, m, tot;
int head[N+5], eid;
int dfn[N+5], low[N+5], dfn_clk;
int stk[N+5], tp, val[N+M+5], vis[N+M+5], cnt[N+M+5], sz[N+M+5], S;
long long ans;
vector<int> G[N+5];

struct Edge {
  int next, to;
}e[2*M+5];

void addEdge(int u, int v) {
  e[++eid].next = head[u];
  e[eid].to = v;
  head[u] = eid;
}

void tarjan(int u) {
  dfn[u] = low[u] = ++dfn_clk; //初始化dfn和low数组
  stk[++tp] = u; //把u加入栈中
  for(int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if(!dfn[v]) { //v还未访问
      tarjan(v); //先访问
      low[u] = min(low[u], low[v]); //然后更新u的信息
      if(low[v] == dfn[u]) { //找到一个以u为顶点的点双
        ++tot; //新建一个方点
        for(int x = 0; x != v; --tp) { //把栈中在u之前的点都向方点连边并弹出
          x = stk[tp];
          G[tot].push_back(x);
          G[x].push_back(tot);
        }
        G[tot].push_back(u); //注意不能把u弹出
        G[u].push_back(tot); //因为u可能在多个点双中
      }
    }
    else low[u] = min(low[u], dfn[v]);
  }
}

void getcnt(int u, int fa) {
  if(u <= n) cnt[u] = 1;
  for(int i = 0; i < G[u].size(); ++i) {
    int v = G[u][i];
    if(v == fa) continue;
    getcnt(v, u);
    cnt[u] += cnt[v];
  }
}

void dp(int u, int fa) {
  vis[u] = 1;
  if(u <= n) sz[u] = 1;
  long long sum = 1LL*cnt[u]*(S-cnt[u]);
  for(int i = 0; i < G[u].size(); ++i) {
    int v = G[u][i];
    if(v == fa) continue;
    dp(v, u);
    sum += 1LL*sz[u]*sz[v];
    sz[u] += sz[v];
  }
  ans += 1LL*val[u]*sum;
}

int main() {
  scanf("%d%d", &n, &m);
  tot = n;
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y), addEdge(y, x);
  }
  for(int i = 1; i <= n; ++i)
    if(!dfn[i]) tarjan(i);
  for(int i = 1; i <= n; ++i) val[i] = -1;
  for(int i = n+1; i <= tot; ++i) val[i] = G[i].size();
  for(int i = 1; i <= tot; ++i)
    if(!vis[i]) {
      getcnt(i, 0);
      S = cnt[i];
      dp(i, 0);
    }
  printf("%lld\n", ans*2);
  return 0;
}