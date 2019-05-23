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

#define N 6000
#define M 4000

struct Edge {
  int next, to, w;
}e[2*M+5];

const double eps = 1e-5;

int n, m, S, T, maxflow;
int head[N+5], eid;
double d[N+5], ans0;
int cnt[N+5];
bool inq[N+5];

void addEdge(int from, int to, int w) {
  e[++eid].next = head[from];
  e[eid].to = to;
  e[eid].w = w;
  head[from] = eid;
}

bool spfa(double mid) {
  static queue<int> q;
  for(int i = 1; i <= N; ++i) d[i] = 1e9, cnt[i] = inq[i] = 0;
  q.push(S);
  d[S] = 0;
  inq[S] = cnt[S] = 1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    inq[u] = 0;
    for(int i = head[u]; i; i = e[i].next) {
      int v = e[i].to;
      double w = e[i].w+mid;
      if(d[v] > d[u]+w) {
        d[v] = d[u]+w;
        if(!inq[v]) {
          if(++cnt[v] >= n) return true;
          inq[v] = 1;
          q.push(v);
        }
      }
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &m);
  n += 2;
  for(int i = 1, u, v, a, b, c, d; i <= m; ++i) {
    scanf("%d%d%d%d%d%d", &u, &v, &a, &b, &c, &d);
    if(u == n-1) {
      maxflow = c;
      S = v;
      continue;
    }
    addEdge(u, v, b+d);
    if(c > 0) addEdge(v, u, a-d);
  }
  double l = 0, r = 1e9, mid;
  while(r-l > eps) {
    mid = (l+r)/2;
    if(spfa(mid)) l = mid;
    else r = mid;
  }
  printf("%.2lf\n", l);
  return 0;
}