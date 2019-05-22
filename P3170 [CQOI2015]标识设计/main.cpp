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

#define N 30
#define MOD 19197

int n, m;
char s[N+5][N+5];
int b[N+5][N+5];
int lst, cur, tot[2], head[MOD+5], nxt[MOD+5], a[2][MOD+5];
ll f[2][MOD+5];

void insert(int s, ll v) {
    int s0 = s%MOD, i;
    for(i = head[s0]; i; i = nxt[i]) if(a[cur][i] == s) break;
    if(!i) nxt[++tot[cur]] = head[s0], a[cur][tot[cur]] = s, f[cur][tot[cur]] = 0, head[s0] = i = tot[cur];
    f[cur][i] += v;
}

// p1  p2  p3  cnt
//低位         高位

int encode(int p1, int p2, int p3, int cnt) {
    static int p[3];
    p[0] = p1, p[1] = p2, p[2] = p3;
    sort(p, p+3);
    return p[0]+(p[1]<<5)+(p[2]<<10)+(cnt<<15);
}

void wrap() {
    for(int i = 1; i <= tot[cur]; ++i) {
        int s = a[cur][i], p1 = s%32, p2 = (s>>5)%32, p3 = (s>>10)%32, cnt = (s>>15)%32;
        a[cur][i] = encode(p1 ? p1+1 : 0, p2 ? p2+1 : 0, p3 ? p3+1 : 0, cnt);
    }
}

int dir(int x, int j) {
    if(x == j) return 1;
    else if(x == j+1) return 2;
    return 0;
}

void printState(int s) {
    printf("%d %d %d %d ", s%32, (s>>5)%32, (s>>10)%32, (s>>15)%32);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%s", s[i]+1);
    for(int i = 0; i <= n+1; ++i) for(int j = 0; j <= m+1; ++j) {
        b[i][j] = 1;
        if(s[i][j] == '.') b[i][j] = 0;
    }
    insert(0, 1);
    for(int i = 1; i <= n; ++i) {
        wrap();
        for(int j = 1; j <= m; ++j) {
            lst = cur, cur ^= 1, tot[cur] = 0;
            memset(head, 0, sizeof head);
            for(int t = 1; t <= tot[lst]; ++t) {
                int s = a[lst][t], p1 = s%32, p2 = (s>>5)%32, p3 = (s>>10)%32, cnt = (s>>15)%32;
                ll v = f[lst][t];
                if(b[i][j]) {
                    if(!dir(p1, j) && !dir(p2, j) && !dir(p3, j)) insert(encode(p1, p2, p3, cnt), v);
                }
                else {
                    if(!dir(p1, j) && !dir(p2, j) && !dir(p3, j)) {
                        insert(encode(p1, p2, p3, cnt), v);
                        if(cnt < 3 && !b[i+1][j]) {
                            if(!p1) insert(encode(j, p2, p3, cnt), v);
                            else if(!p2) insert(encode(p1, j, p3, cnt), v);
                            else if(!p3) insert(encode(p1, p2, j, cnt), v);
                        }
                    }
                    else if(dir(p1, j) == 1 && !dir(p2, j)) {
                        if(!b[i][j+1] && p2 != j+2) insert(encode(p1+1, p2, p3, cnt), v);
                        if(cnt < 3) insert(encode(0, p2, p3, cnt+1), v);
                    }
                    else if(dir(p2, j) == 1 && !dir(p3, j)) {
                        if(!b[i][j+1] && p3 != j+2) insert(encode(p1, p2+1, p3, cnt), v);
                        if(cnt < 3) insert(encode(p1, 0, p3, cnt+1), v);
                    }
                    else if(dir(p3, j) == 1) {
                        if(!b[i][j+1]) insert(encode(p1, p2, p3+1, cnt), v);
                        if(cnt < 3) insert(encode(p1, p2, 0, cnt+1), v);
                    }
                    else if(dir(p1, j) == 2) {
                        if(!b[i+1][j]) insert(encode(p1-1, p2, p3, cnt), v);
                        if(!b[i][j+1] && p2 != j+2) insert(encode(p1, p2, p3, cnt), v);
                    }
                    else if(dir(p2, j) == 2) {
                        if(!b[i+1][j]) insert(encode(p1, p2-1, p3, cnt), v);
                        if(!b[i][j+1] && p3 != j+2) insert(encode(p1, p2, p3, cnt), v);
                    }
                    else if(dir(p3, j) == 2) {
                        if(!b[i+1][j]) insert(encode(p1, p2, p3-1, cnt), v);
                        if(!b[i][j+1]) insert(encode(p1, p2, p3, cnt), v);
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= tot[cur]; ++i) if((a[cur][i]>>15)%32 == 3) ans += f[cur][i];
    printf("%lld\n", ans);
  return 0;
}