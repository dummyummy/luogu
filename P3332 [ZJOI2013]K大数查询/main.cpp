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
#define vi vector<int>
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 100000
#define M 100000

int n, m, qtot, ans[M+5];

struct Query {
  int type;
  int a, b, id;
  ll c;
}q[M+5], tl[M+5], tr[M+5];

struct SegmentTree {
  ll sumv[4*N+5], addv[4*N+5];
  int lson(int o) { return (o<<1); }
  int rson(int o) { return (o<<1|1); }
  void init() {
    memset(sumv, 0, sizeof sumv);
    memset(addv, 0, sizeof addv);
  }
  void pushup(int o) {
    sumv[o] = sumv[lson(o)]+sumv[rson(o)];
  }
  void pushdown(int o, int l, int r) {
    if(addv[o]) {
      int mid = (l+r)>>1;
      sumv[lson(o)] += (mid-l+1)*addv[o], addv[lson(o)] += addv[o];
      sumv[rson(o)] += (r-mid)*addv[o], addv[rson(o)] += addv[o];
      addv[o] = 0;
    }
  }
  void add(int o, int l, int r, int L, int R, ll k) {
    if(L <= l && r <= R) {
      sumv[o] += (r-l+1)*k, addv[o] += k;
      return ;
    }
    pushdown(o, l, r);
    int mid = (l+r)>>1;
    if(L <= mid) add(lson(o), l, mid, L, R, k);
    if(R > mid) add(rson(o), mid+1, r, L, R, k);
    pushup(o);
  }
  ll query(int o, int l, int r, int L, int R) {
    if(L <= l && r <= R) return sumv[o];
    pushdown(o, l, r);
    int mid = (l+r)>>1;
    ll ret = 0;
    if(L <= mid) ret += query(lson(o), l, mid, L, R);
    if(R > mid) ret += query(rson(o), mid+1, r, L, R);
    return ret;
  }
}ST;

void solve(int l, int r, int L, int R) {
  if(l > r) return ;
  if(L == R) {
    for(int i = l; i <= r; ++i) if(q[i].type == 2) ans[q[i].id] = L;
    return ;
  }
  int mid = L+(R-L)/2;
  int tot1 = 0, tot2 = 0;
  for(int i = l; i <= r; ++i) {
    if(q[i].type == 1) {
      if(q[i].c > mid) ST.add(1, 1, n, q[i].a, q[i].b, 1), tr[++tot2] = q[i];
      else tl[++tot1] = q[i];
    }
    else {
      ll v = ST.query(1, 1, n, q[i].a, q[i].b);
      if(v >= q[i].c) tr[++tot2] = q[i];
      else q[i].c -= v, tl[++tot1] = q[i];
    }
  }
  for(int i = 1; i <= tot1; ++i) q[l+i-1] = tl[i];
  for(int i = 1; i <= tot2; ++i) {
    q[l+tot1+i-1] = tr[i];
    if(tr[i].type == 1) ST.add(1, 1, n, tr[i].a, tr[i].b, -1);
  }
  solve(l, l+tot1-1, L, mid), solve(l+tot1, r, mid+1, R);
}

int main() {
  #ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("my.out", "w", stdout);
  #endif
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; ++i) {
    scanf("%d%d%d%lld", &q[i].type, &q[i].a, &q[i].b, &q[i].c);
    if(q[i].type == 2) q[i].id = ++qtot;
  }
  solve(1, m, -n, n);
  for(int i = 1; i <= qtot; ++i) printf("%d\n", ans[i]);
  return 0;
}