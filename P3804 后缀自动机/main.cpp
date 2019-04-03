#include <bits/stdc++.h>

using namespace std;

#define N 1000000

int n;
char s[N+5];
int sum[N+5], a[2*N+5];

struct SuffixAutomaton {
    int sz, last, len[2*N+5], cnt[2*N+5], nxt[2*N+5][26], link[2*N+5];
    void init() {
        sz = last = len[0] = 0;
        link[0] = -1;
        memset(nxt, 0, sizeof nxt);
    }
    void expand(char c) {
        int cur = ++sz;
        len[cur] = len[last]+1, cnt[cur] = 1;
        while(~last && !nxt[last][c-'a']) {
            nxt[last][c-'a'] = cur;
            last = link[last];
        }
        if(last == -1) link[cur] = 0;
        else {
            int p = last, q = nxt[p][c-'a'];
            if(len[p]+1 == len[q]) link[cur] = q;
            else {
                int clone = ++sz;
                len[clone] = len[p]+1;
                link[clone] = link[q], link[cur] = link[q] = clone;
                for(int i = 0; i <= 25; ++i) nxt[clone][i] = nxt[q][i];
                while(~p && nxt[p][c-'a'] == q) nxt[p][c-'a'] = clone, p = link[p];
            }
        }
        last = cur;
    }
    void getcnt() {
        for(int i = 1; i <= sz; ++i) sum[len[i]]++;
        for(int i = 1; i <= n; ++i) sum[i] += sum[i-1];
        for(int i = 1; i <= sz; ++i) a[sum[len[i]]--] = i;
        for(int i = sz; i >= 1; --i) cnt[link[a[i]]] += cnt[a[i]];
    }
}sam;

int main() {
    scanf("%s", &s);
    n = strlen(s);
    sam.init();
    for(int i = 0; i < n; ++i) sam.expand(s[i]);
    sam.getcnt();
    int ans = 0;
    for(int i = 1; i <= sam.sz; ++i) if(sam.cnt[i] > 1) ans = max(ans, sam.cnt[i]*sam.len[i]);
    printf("%d\n", ans);
    return 0;
}