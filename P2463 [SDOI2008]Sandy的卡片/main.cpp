#include <bits/stdc++.h>

using namespace std;

#define N 1000
#define M 1000
#define mii map<int, int>

int n, m;
int maxlen[2*M+5], link[2*M+5], mx[2*M+5], mn[2*M+5], len, nums[M+5];
mii ch[2*M+5];
int tmp[M+5], a[2*M+5];
int last = 1, nid = 1;

void insert(int c) {
  int cur = ++nid;
  maxlen[cur] = maxlen[last]+1;
  while(last && !ch[last].count(c)) ch[last][c] = cur, last = link[last];
  if(!last) link[cur] = 1;
  else {
    int p = last, q = ch[last][c];
    if(maxlen[q] == maxlen[p]+1) link[cur] = q;
    else {
      int clone = ++nid;
      maxlen[clone] = maxlen[p]+1;
      ch[clone] = ch[q]; link[clone] = link[q];
      link[q] = link[cur] = clone;
      while(p && ch[p].count(c) && ch[p][c] == q) ch[p][c] = clone, p = link[p];
    }
  }
  last = cur;
}

void topo() {
  memset(tmp, 0, sizeof tmp);
  for(int i = 1; i <= nid; ++i) tmp[maxlen[i]]++;
  for(int i = 1; i <= M; ++i) tmp[i] += tmp[i-1];
  for(int i = 1; i <= nid; ++i) a[tmp[maxlen[i]]--] = i;
  for(int i = nid; i >= 1; --i)
    mx[link[a[i]]] = max(mx[link[a[i]]], min(maxlen[link[a[i]]], mx[a[i]])), mn[a[i]] = min(mn[a[i]], mx[a[i]]);
}

void calc(int *s) {
  int u = 1;
  len = 0;
  memset(mx, 0, sizeof mx);
  for(int i = 1; i <= m; ++i) {
    while(u && !ch[u].count(s[i])) u = link[u], len = maxlen[u];
    if(!u) u = 1;
    else u = ch[u][s[i]], len++, mx[u] = max(mx[u], len);
  }
  topo();
}

int main() {
  scanf("%d", &n);
  memset(mn, 0x3f, sizeof mn);
  scanf("%d", &m);
  for(int j = 1; j <= m; ++j) scanf("%d", &nums[j]);
  for(int j = 1; j < m; ++j) nums[j] -= nums[j+1];
  for(int j = 1; j <= m; ++j) insert(nums[j]);
  for(int i = 1; i < n; ++i) {
    scanf("%d", &m);
    for(int j = 1; j <= m; ++j) scanf("%d", &nums[j]);
    for(int j = 1; j < m; ++j) nums[j] -= nums[j+1];
    calc(nums);
  }
  int ans = 0;
  for(int i = 1; i <= nid; ++i) ans = max(ans, mn[i]);
  ans++;
  printf("%d\n", ans);
  return 0;
}