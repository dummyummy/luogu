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
#define DEF 0x8f8f8f8f
#define DDEF 0x8f8f8f8f8f8f8f8fLL
#define vi vector<int>
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 10
#define MOD 114511

int n;
int val[N+5][N+5], ans = DEF, bin[N+5];

namespace HashTable { //哈希表所需
  int lst, cur, head[MOD+5], nxt[MOD+5], tot[2];
  int f[2][MOD+5], a[2][MOD+5];
  void insert(int x, int v) { // 把x状态的最优值与v取max
    int x0 = x%MOD, i;
    for(i = head[x0]; i; i = nxt[i]) if(a[cur][i] == x) break;
    if(!i) nxt[++tot[cur]] = head[x0], f[cur][tot[cur]] = DEF, a[cur][tot[cur]] = x, head[x0] = i = tot[cur];
    f[cur][i] = max(f[cur][i], v);
  }
}

using namespace HashTable;

// 最多有5(9/2向上取整)个联通块
// 采用8进制压缩

int decode(int s0, int v) { // 最小表示所需
  static int tf[8];
  int cnt = 0, s = 0;
  memset(tf, 0, sizeof tf);
  for(int i = 0; i < n; ++i) {
    int x = (s0>>(3*i))%8;
    if(!x) continue;
    if(!tf[x]) tf[x] = ++cnt;
    s += tf[x]*bin[i];
  }
  if(cnt == 1) ans = max(ans, v); // 顺便更新全局最优解
  return s;
}

int main() {
  scanf("%d", &n);
  bin[0] = 1;
  for(int i = 1; i <= n; ++i) bin[i] = bin[i-1]<<3;
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) scanf("%d", &val[i][j]), ans = max(ans, val[i][j]);
  insert(0, 0); // 初始化
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      lst = cur, cur ^= 1, tot[cur] = 0;
      memset(head, 0, sizeof head);
      for(int k = 1; k <= tot[lst]; ++k) {
        int s = a[lst][k], v = f[lst][k], p1, p2 = (s>>(3*(j-1)))%8;
        if(j == 1) p1 = 0;
        else p1 = (s>>(3*(j-2)))%8;
        if(!p1 && !p2) { // 左和上都没有选
          insert(decode(s, v), v); // 当前不选
          insert(decode(s+7*bin[j-1], v+val[i][j]), v+val[i][j]); // 当前选
        }
        else if(p1 && !p2) { // 只有左选了
          insert(decode(s, v), v); // 当前不选
          insert(decode(s+p1*bin[j-1], v+val[i][j]), v+val[i][j]); // 当前选
        }
        else if(!p1 && p2) { // 只有上选了
          int cnt = 0;
          for(int p = 0; p < n; ++p) if((s>>(3*p))%8 == p2) cnt++; // 只要这个连通块还有另一处与轮廓线相交就可以不选当前的
          if(cnt >= 2) insert(decode(s-p2*bin[j-1], v), v); // 当前不选
          insert(decode(s, v+val[i][j]), v+val[i][j]); // 当前选
        }
        else { // 左和上都选了
          int cnt = 0;
          for(int p = 0; p < n; ++p) if((s>>(3*p))%8 == p2) cnt++; // 与上一种情况同理
          if(cnt >= 2) insert(decode(s-p2*bin[j-1], v), v); // 当前不选
          if(p1 != p2) for(int p = 0; p < n; ++p) if((s>>(3*p))%8 == p2) s += p1*bin[p]-p2*bin[p]; // 合并两个连通块
          insert(decode(s, v+val[i][j]), v+val[i][j]); // 当前选
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}