// luogu-judger-enable-o2
//
//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                           O\  =  /O
//                        ____/`---'\____
//                      .'  \\|     |//  `.
//                     /  \\|||  :  |||//  \
//                    /  _||||| -:- |||||-  \
//                    |   | \\\  -  /// |   |
//                    | \_|  ''\---/''  |   |
//                    \  .-\__  `-`  ___/-. /
//                  ___`. .'  /--.--\  `. . __
//               ."" '<  `.___\_<|>_/___.'  >'"".
//              | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//              \  \ `-.   \_ __\ /__ _/   .-` /  /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                      佛祖保佑       永无BUG
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define ll long long
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define N 100010
#define INF 0x3f3f3f3f

struct Edge {
  int next, to, w;
}e[50*N];

int n, S = 4*N+1, T = 4*N+2;
int d[4*N+10];
int eid, head[4*N+10], vis[4*N+5];
pii p[N+10];
vector<int> G1[N+5], G2[N+5];
int tot1 = 0, tot2 = 0;
map<int, int> m1, m2;

void addEdge(int u, int v, int w) {
  e[++eid].next = head[u];
  e[eid].to = v;
  e[eid].w = w;
  head[u] = eid;
}

void spfa() {
  memset(d, 0x3f, sizeof d);
  memset(vis, 0, sizeof vis);
  queue<int> q;
  q.push(S);
  d[S] = 0;
  vis[S] = 1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    vis[u] = 0;
    for(int i = head[u]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w;
      if(d[v] > d[u]+w) {
        d[v] = d[u]+w;
        if(!vis[v]) q.push(v), vis[v] = 1;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  n += 2;
  for(int i = 1; i <= n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
    if(!m1.count(p[i].first)) m1[p[i].first] = ++tot1;
    if(!m2.count(p[i].second)) m2[p[i].second] = ++tot2;
    G1[m1[p[i].first]].pb(i);
    G2[m2[p[i].second]].pb(i);
    addEdge(i, 2*n+i, 1), addEdge(2*n+i, i, 1);
    addEdge(i, 3*n+i, 1), addEdge(3*n+i, i, 1);
    addEdge(n+i, 2*n+i, 1), addEdge(2*n+i, n+i, 1);
    addEdge(n+i, 3*n+i, 1), addEdge(3*n+i, n+i, 1);
    addEdge(i, n+i, 0), addEdge(n+i, i, 0);
    addEdge(2*n+i, 3*n+i, 0), addEdge(3*n+i, 2*n+i, 0);
  }
  addEdge(S, 1, 0), addEdge(S, n+1, 0), addEdge(S, 2*n+1, 0), addEdge(S, 3*n+1, 0);
  addEdge(2, T, 0), addEdge(n+2, T, 0), addEdge(2*n+2, T, 0), addEdge(3*n+2, T, 0);
  for(int i = 1; i <= tot1; ++i) {
    sort(G1[i].begin(), G1[i].end(), [](const int &lhs, const int &rhs) {
      return p[lhs].second < p[rhs].second;
    });
    for(int j = 0; j < G1[i].size()-1; ++j) addEdge(G1[i][j], G1[i][j+1]+n, 0), addEdge(G1[i][j+1]+n, G1[i][j], 0);
  }
  for(int i = 1; i <= tot2; ++i) {
    sort(G2[i].begin(), G2[i].end(), [](const int &lhs, const int &rhs) {
      return p[lhs].first < p[rhs].first;
    });
    for(int j = 0; j < G2[i].size()-1; ++j) addEdge(G2[i][j]+3*n, G2[i][j+1]+2*n, 0), addEdge(G2[i][j+1]+2*n, G2[i][j]+3*n, 0);
  }
  spfa();
  if(d[T] == INF) printf("-1\n");
  else printf("%d\n", d[T]);
  return 0;
}