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

#define N 200000
#define M 100000

int n, m, n0;
int a[N+5], pos[N+5], vis[N+5], ans[N+5];
int root[N+5];
int nid, ch[2][50*N+5], sumv[50*N+5];
int b[N+5];

int lowbit(int x) {
  return x&-x;
}

void update(int x, int k) {
  while(x <= n) {
    b[x] += k;
    x += lowbit(x);
  }
}

int getsum(int x) {
  int ret = 0;
  while(x) {
    ret += b[x];
    x -= lowbit(x);
  }
  return ret;
}

int newNode() {
  int u = ++nid;
  sumv[u] = ch[0][u] = ch[1][u] = 0;
  return u;
}

void add(int &o, int l, int r, int x, int k) {
  if(!o) o = newNode();
  sumv[o] += k;
  if(l == r) return ;
  int mid = (l+r)>>1;
  if(x <= mid) add(ch[0][o], l, mid, x, k);
  else add(ch[1][o], mid+1, r, x, k);
}

int query(int o, int l, int r, int x, int flag) { // 0:??x 1:??x
  if(!o) return 0;
  if(l == r) {
    if(flag) return l > x ? sumv[o] : 0;
    else return l < x ? sumv[o] : 0;
  }
  int mid = (l+r)>>1;
  if(flag) {
    if(x <= mid) return query(ch[0][o], l, mid, x, flag)+sumv[ch[1][o]];
    else return query(ch[1][o], mid+1, r, x, flag);
  }
  else {
    if(x <= mid) return query(ch[0][o], l, mid, x, flag);
    else return query(ch[1][o], mid+1, r, x, flag)+sumv[ch[0][o]];
  }
}

void Add(int x, int v, int k) {
  while(x <= n) {
    add(root[x], 1, n, v, k);
    x += lowbit(x);
  }
}

int Query(int x, int v, int flag) { // x???????(1)/??(0)v?
  int ans = 0;
  while(x) {
    ans += query(root[x], 1, n, v, flag);
    x -= lowbit(x);
  }
  return ans;
}

int main() {
  while(~scanf("%d%d", &n, &m)) {
    memset(root, 0, sizeof root);
    memset(b, 0, sizeof b);
    nid = 0;
    ll sum = 0;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), pos[a[i]] = i, Add(i, a[i], 1);
    for(int i = 1; i <= n; ++i) {
      update(a[i], 1);
      sum += i-getsum(a[i]);
    }
    for(int i = 1, x; i <= m; ++i) {
      scanf("%d", &x);
      printf("%lld\n", sum);
      sum -= Query(pos[x], x, 1);
      sum -= Query(n, x, 0)-Query(pos[x], x, 0);
      Add(pos[x], x, -1);
    }
  }
  return 0;
}