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
//                     佛祖保佑       永无BUG
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
#define lbd lower_bound
#define ubd upper_bound
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define MOD 1000003

int n = 11;
ll a[15][15], b[15][15], c[15];

int fpow(int x, int p) {
  x %= MOD;
  int ret = 1;
  while(p) {
    if(p&1) ret = 1LL*x*ret%MOD;
    x = 1LL*x*x%MOD;
    p >>= 1;
  }
  return ret;
}

int f(int x) {
  int ret = 0;
  for(int i = n-1; i >= 0; --i) {
    ret = (1LL*ret*x%MOD+c[i])%MOD;
  }
  return ret;
}

void gauss() {
  for(int i = 0; i < n-1; ++i) {
    for(int j = 0; j < n; ++j)
      for(int k = 0; k <= n; ++k) b[j][k] = a[j][k];
    for(int j = i; j <= n; ++j) {
      for(int k = 0; k < n-1-i; ++k) {
        a[k][j] = b[k+1][j]-b[k][j];
        if(j == n) a[k][j] = (a[k][j]%MOD+MOD)%MOD;
      }
    }
    for(int j = 0; j <= n; ++j) a[n-1-i][j] = (a[n-1-i][j]%MOD+MOD)%MOD;
  }
  for(int i = 0; i < n; ++i) {
    ll t = a[i][n]*fpow(a[i][n-i-1], MOD-2)%MOD;
    c[n-i-1] = t;
    for(int j = i+1; j < n; ++j) a[j][n] = ((a[j][n]-t*a[j][n-i-1]%MOD)%MOD+MOD)%MOD, a[j][n-i-1] = 0;
  }
}

int solve() {
  for(int x = 0; x < MOD; ++x) if(!f(x)) return x;
  return -1;
}

int main() {
  for(int i = 0; i < n; ++i) {
    printf("? %d\n", i);
    fflush(stdout);
    scanf("%lld", &a[i][n]);
    ll t = 1;
    for(int j = 0; j < n; ++j) a[i][j] = t, t = t*i;
  }
  gauss();
  printf("! %d\n", solve());
  return 0;
}