一道很好的圆方树入门题

感谢[PinkRabbit](https://www.luogu.org/blog/PinkRabbit/Introduction-to-Round-Square-Tree)巨佬的博客，讲的太好啦

首先是构建圆方树的代码，也比较好想好记

```cpp
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

```

注释写的还算详细$QWQ$

考虑这一题怎么做

### 题目大意

给你一张无向图，让你求这样的有序三元组$<s,c,f>$的个数，使得存在一条简单路径依次经过$s,c,f$

### Solution

首先我们把圆方树建出来

考虑如下性质，对于在同一个点双中的两点$s,t$，还有一个给定的也在这个点双中的点$c$，一定存在一条简单路径依次经过$s,c,t$，~~貌似挺显然的~~

在这题中，假设钦定了路径的两个端点$s,t$，由上面的性质，那么能作为中间点的点集就是在圆方树上$s$到$t$的路径所经过的方点所代表的点双的并集(不包括$s,t$)。这句话是本题的突破点，虽然有点拗口

然后是一个很套路的处理，把方点的点权设为点双的大小，圆点的点权设为$-1$，这样的话上面要求的值就转化为$s$到$t$路径上的点权之和了

直接枚举$s$和$t$显然不行，考虑枚举每个点对答案的贡献，即
$$
w[u]=val[u]*经过u的路径条数
$$
然后用树形$dp$就可以$O(n)$的统计答案了

另外，注意图不一定联通，所以需要单独统计每个联通块中的答案

```cpp
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
```

