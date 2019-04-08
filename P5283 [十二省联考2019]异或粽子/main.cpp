#include <bits/stdc++.h>

using namespace std;

#define N 500000
#define ll long long
#define pli pair<long long, int>
#define mp make_pair
#define LIM 31

int n, k;
ll a[N+5], xorsum[N+5];
int nid = 1, ch[2][50*N+5], sumv[50*N+5], root[N+5], head[N+5];
priority_queue<pli> pq;

void build() {
  int bit = LIM, u = root[0] = 1;
  sumv[u] = 1;
  while(~bit) {
    ch[0][u] = ++nid;
    u = ch[0][u];
    sumv[u] = 1;
    bit--;
  }
}

void insert(int u, int &v, ll x, int bit) {
  v = ++nid;
  sumv[v] = sumv[u]+1;
  ch[0][v] = ch[0][u], ch[1][v] = ch[1][u];
  if(bit < 0) return ;
  int d = (x>>bit)&1;
  if(!d) insert(ch[0][u], ch[0][v], x, bit-1);
  else insert(ch[1][u], ch[1][v], x, bit-1);
}

ll query(int u, ll x, int k) {
  ll v = 0;
  int bit = LIM;
  while(~bit) {
    int d = (x>>bit)&1;
    if(!d) {
      if(sumv[ch[1][u]] >= k) u = ch[1][u], v = (v<<1)|1;
      else k -= sumv[ch[1][u]], u = ch[0][u], v = v<<1;
    }
    else {
      if(sumv[ch[0][u]] >= k) u = ch[0][u], v = (v<<1)|1;
      else k -= sumv[ch[0][u]], u = ch[1][u], v = v<<1;
    }
    bit--;
  }
  return v;
}

void debug(int u, ll x) {
  int bit = LIM;
  while(~bit) {
    int d = (x>>bit)&1;
    if(!d) u = ch[0][u];
    else u = ch[1][u];
    bit--;
  }
  printf("%d\n", sumv[u]);
}

int main() {
  scanf("%d%d", &n, &k);
  build();
  ll t, ans = 0;
  for(int i = 1; i <= n; ++i) {
    scanf("%lld", &t);
    xorsum[i] = xorsum[i-1]^t;
    pq.push(mp(query(root[i-1], xorsum[i], 1), i));
    insert(root[i-1], root[i], xorsum[i], LIM);
    head[i] = 1;
  }
  while(k--) {
    pli fir = pq.top(); pq.pop();
    ll v = fir.first;
    int x = fir.second;
    ans += v;
    if(head[x] < x) {
      head[x]++;
      pq.push(mp(query(root[x-1], xorsum[x], head[x]), x));
    }
  }
  printf("%lld\n", ans);
  return 0;
}