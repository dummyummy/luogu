#include <bits/stdc++.h>

using namespace std;

#define N 50000
#define M 50000
#define pii pair<int, int>
#define mp make_pair

int n, m, bs, qd, md;
int a[N+5], cnt[1000005], sum, ans[M+5];
pii mpos[M+5];

int getBlock(int x) {
  return (x-1)/bs+1;
}

struct Query {
  int l, r, t, id;
  bool operator < (const Query &rhs) const {
    if(getBlock(l) != getBlock(rhs.l)) return getBlock(l) < getBlock(rhs.l);
    if(getBlock(r) != getBlock(rhs.r)) return getBlock(r) < getBlock(rhs.r);
    return t < rhs.t;
  }
}querys[M+5];

void add(int v) {
  if(++cnt[v] == 1) sum++;
}

void del(int v) {
  if(--cnt[v] == 0) sum--;
}

void Mo() {
  int l = 1, r = 0, cur = 0;
  sort(querys+1, querys+qd+1);
  for(int i = 1; i <= qd; ++i) {
    while(l < querys[i].l) del(a[l++]);
    while(l > querys[i].l) add(a[--l]);
    while(r < querys[i].r) add(a[++r]);
    while(r > querys[i].r) del(a[r--]);
    while(cur < querys[i].t) {
      cur++;
      if(mpos[cur].first >= querys[i].l && mpos[cur].first <= querys[i].r)
        del(a[mpos[cur].first]), add(mpos[cur].second);
      swap(a[mpos[cur].first], mpos[cur].second);
    }
    while(cur > querys[i].t) {
      if(mpos[cur].first >= querys[i].l && mpos[cur].first <= querys[i].r)
        del(a[mpos[cur].first]), add(mpos[cur].second);
      swap(a[mpos[cur].first], mpos[cur].second);
      cur--;
    }
    ans[querys[i].id] = sum;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  char type[2];
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%s%d%d", type, &x, &y);
    if(type[0] == 'Q') querys[++qd] = Query{x, y, md, qd};
    else mpos[++md] = mp(x, y);
  }
  bs = (int)floor(pow(n, 2.0/3.0));
  Mo();
  for(int i = 1; i <= qd; ++i) printf("%d\n", ans[i]);
  return 0;
}