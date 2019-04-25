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
#define mii map<int, int>
#define uint unsigned int
#define lbd lower_bound
#define ubd upper_bound
#define ll long long
#define mp make_pair
#define pb push_back
#define re register
#define il inline

#define N 100000

static int n;
static ll f[N+5], ans[N+5], v1, v2, v3;
static int stk[N+5], tp;

int main() {
  scanf("%d", &n);
  int i, t;
  for(i = 1; i <= n; ++i) scanf("%lld", &f[i]);
  for(i = 0; i <= n+1; ++i) {
    while(tp >= 2 && (f[i]-f[stk[tp-1]])*(stk[tp]-stk[tp-1]) > (f[stk[tp]]-f[stk[tp-1]])*(i-stk[tp-1])) --tp;
    stk[++tp] = i;
  }
  for(t = 2; t <= tp; ++t) {
    v1 = f[stk[t]]-f[stk[t-1]];
    v2 = f[stk[t-1]]*stk[t]-f[stk[t]]*stk[t-1];
    v3 = stk[t]-stk[t-1];
    for(i = stk[t-1]+1; i <= stk[t]; ++i)
      ans[i] = (ll)(100000.0*(v1*i+v2)/v3);
  }
  for(i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
  return 0;
}