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
#define mii map<int, int>
#define uint unsigned int
#define lbd lower_bound
#define ubd upper_bound
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 100000

static int n, m;
static int head[N+5], eid;
static int fa[N+5], d[N+5], sz[N+5], hson[N+5];
static int id[N+5], dfn[N+5], dfn_clk, top[N+5], tail[N+5];

struct Edge { 
  int next, to;
}e[2*N+5];

struct SegmentTree {
  #define mid ((l+r)>>1)
  #define lson (o<<1)
  #define rson (o<<1|1)
  int maxv[4*N+5], addv[4*N+5];
  void pushup(int o) {
    maxv[o] = max(maxv[lson], maxv[rson]);
  }
  void pushdown(int o) {
    if(addv[o]) {
      addv[lson] += addv[o], addv[rson] += addv[o];
      maxv[lson] += addv[o], maxv[rson] += addv[o];
      addv[o] = 0;
    }
  }
  void build(int o, int l, int r) {
    addv[o] = 0;
    if(l == r) {
      maxv[o] = d[id[l]];
      return ;
    }
    build(lson, l, mid), build(rson, mid+1, r);
    pushup(o);
  }
  void add(int o, int l, int r, int L, int R, int k) {
    if(L <= l && r <= R) {
      maxv[o] += k, addv[o] += k;
      return ;
    }
    pushdown(o);
    if(L <= mid) add(lson, l, mid, L, R, k);
    if(R > mid) add(rson, mid+1, r, L, R, k);
    pushup(o);
  }
  int query(int o, int l, int r, int x) {
    if(l == r) return maxv[o];
    pushdown(o);
    if(x <= mid) return query(lson, l, mid, x);
    else return query(rson, mid+1, r, x);
  }
  int query(int o, int l, int r, int L, int R) {
    if(L <= l && r <= R) return maxv[o];
    pushdown(o);
    int ret = 0;
    if(L <= mid) ret = max(ret, query(lson, l, mid, L, R));
    if(R > mid) ret = max(ret, query(rson, mid+1, r, L, R));
    return ret;
  }
}st;

struct LCT {
  int fa[N+5], ch[2][N+5];
  void init() {
    memset(fa, 0, sizeof fa);
    memset(ch, 0, sizeof ch);
  }
  bool isRoot(int x) {
    return ch[0][fa[x]] != x && ch[1][fa[x]] != x;
  }
  void rotate(int x) {
    int y = fa[x], z = fa[y], d = ch[1][y] == x, p = ch[d^1][x];
    if(!isRoot(y)) ch[ch[1][z]==y][z] = x; ch[d][y] = p; ch[d^1][x] = y;
    if(p) fa[p] = y; fa[y] = x; fa[x] = z;
  }
  void splay(int x) {
    for(int y, z; !isRoot(x); rotate(x))
      if((y = fa[x], z = fa[y], !isRoot(y))) rotate((ch[1][y]==x ^ ch[1][z]==y) ? x : y);
  }
  int findRoot(int x) {
    while(ch[0][x]) x = ch[0][x];
    return x;
  }
  void access(int x) {
    for(int y = 0, t; x; y = x, x = fa[x]) {
      splay(x);
      if(ch[1][x]) t = findRoot(ch[1][x]), st.add(1, 1, n, dfn[t], tail[t], 1);
      if(y) t = findRoot(y), st.add(1, 1, n, dfn[t], tail[t], -1);
      ch[1][x] = y;
    }
  }
}lct;

void addEdge(int u, int v) {
  e[++eid].next = head[u];
  e[eid].to = v;
  head[u] = eid;
}

void dfs1(int u, int pa) {
  d[u] = d[pa]+1;
  sz[u] = 1;
  fa[u] = pa;
  for(int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if(v == pa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    if(sz[hson[u]] < sz[v]) hson[u] = v;
  }
}

void dfs2(int u, int tp) {
  dfn[u] = ++dfn_clk, id[dfn_clk] = u;
  top[u] = tp;
  if(hson[u]) dfs2(hson[u], tp);
  for(int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if(v == fa[u] || v == hson[u]) continue;
    dfs2(v, v);
  }
  tail[u] = dfn_clk;
}

int lca(int x, int y) {
  while(top[x] != top[y]) d[top[x]] > d[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
  return d[x] < d[y] ? x : y;
}

int query(int x, int y) {
  return st.query(1, 1, n, dfn[x])+st.query(1, 1, n, dfn[y])-2*st.query(1, 1, n, dfn[lca(x, y)])+1;
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y), addEdge(y, x);
  }
  dfs1(1, 0), dfs2(1, 1);
  st.build(1, 1, n);
  lct.init();
  for(int i = 1; i <= n; ++i) lct.fa[i] = fa[i];
  for(int i = 1, type, x, y; i <= m; ++i) {
    scanf("%d", &type);
    if(type == 1) {
      scanf("%d", &x);
      lct.access(x);
    }
    else if(type == 2) {
      scanf("%d%d", &x, &y);
      printf("%d\n", query(x, y));
    }
    else {
      scanf("%d", &x);
      printf("%d\n", st.query(1, 1, n, dfn[x], tail[x]));
    }
  }
  return 0;
}