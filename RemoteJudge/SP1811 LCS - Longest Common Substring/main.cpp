#include <bits/stdc++.h>

using namespace std;

#define N 250000

int m, n, root = 1, nid = 1, last = 1, maxlen[2*N+5], ch[2*N+5][26], link[2*N+5], mx[2*N+5], mn[2*N+5], len;
int tmp[2*N+5], a[2*N+5];

void insert(int c) {
  int cur = ++nid;
  maxlen[cur] = maxlen[last]+1;
  while(last && !ch[last][c]) ch[last][c] = cur, last = link[last];
  if(!last) link[cur] = root;
  else {
    int p = last, q = ch[last][c];
    if(maxlen[q] == maxlen[p]+1) link[cur] = q;
    else {
      int clone = ++nid;
      maxlen[clone] = maxlen[p]+1;
      for(int i = 0; i < 26; ++i) ch[clone][i] = ch[q][i];
      link[clone] = link[q]; link[q] = link[cur] = clone;
      while(p && ch[p][c] == q) ch[p][c] = clone, p = link[p];
    }
  }
  last = cur;
}

void radixSort() {
  memset(tmp, 0, sizeof tmp);
  for(int i = 1; i <= nid; ++i) tmp[maxlen[i]]++;
  for(int i = 1; i <= m; ++i) tmp[i] += tmp[i-1];
  for(int i = 1; i <= nid; ++i) a[tmp[maxlen[i]]--] = i;
  for(int i = nid; i >= 1; --i)
    mx[link[a[i]]] = max(mx[link[a[i]]], min(maxlen[link[a[i]]], mx[a[i]])), mn[a[i]] = min(mn[a[i]], mx[a[i]]);
}

void calc(char *s) {
  n = strlen(s);
  memset(mx, 0, sizeof mx);
  int u = root;
  len = 0;
  for(int i = 0; i < n; ++i) {
    while(u && !ch[u][s[i]-'a']) u = link[u], len = maxlen[u];
    if(!u) u = root;
    else {
      u = ch[u][s[i]-'a'];
      len++;
      mx[u] = max(mx[u], len);
    }
  }
  radixSort();
}

int main() {
  char s[N+5];
  scanf("%s", s);
  m = strlen(s);
  for(int i = 0; i < m; ++i) insert(s[i]-'a');
  memset(mn, 0x3f, sizeof mn);
  while(~scanf("%s", s)) calc(s);
  int ans = 0;
  for(int i = 1; i <= nid; ++i) ans = max(ans, mn[i]);
  printf("%d\n", ans);
  return 0;
}