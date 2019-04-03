#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2000010;

char s[N]; ll ans;
int fa[N], len[N], siz[N], ch[N][26];
int l, lst = 0, node = 0, t[N], A[N];


void Extend (int c) {
    int f = lst, p = ++node; lst = p;
    len[p] = len[f] + 1; siz[p] = 1;
    //f是添加c前的最大前缀
    //p是添加c后的最大前缀
    while(~f && !ch[f][c]) {
        ch[f][c] = p;
        f = fa[f];
    }
    //遍历旧的最大前缀的后缀,看原来有没有c
    //如果没有的话,需要拉一个向c的节点,作为新产生的后缀
    if(f == 0) {
        fa[p] = 1;
        //如果原先压根没有c这个字符
    } else {
        int x = ch[f][c];
        if (len[f] + 1 == len[x]) {
            fa[p] = x;
            //如果下一个类中正好只有一个对应的更长的串
        } else {
            //len[f] + 1 < len[x]
            //x中:len[f] + 1 <= len[x]的部分会增加一个end_pos为n的后缀
            int y = ++node;
            //我们新拆出来一个y来存储这些会产生增量的部分
            len[y] = len[f] + 1; //设置长度
            fa[y] = fa[x]; //新节点在原先节点的父亲位置上,这个节点的父亲又应该对应原节点的父亲
            fa[x] = fa[p] = y; //尾部新生后缀和原先节点的父亲都应该是当前拆分的节点
            memcpy (ch[y], ch[x], sizeof (ch[y])); //连边是一致哒!
            while(f != 0 && ch[f][c] == x) {
                ch[f][c] = y;
                f = fa[f];
            }
            //对更短一点的子后缀(父节点)做出更新
        }
    }
}

int main () {
    scanf ("%s", s); l = strlen (s);
    fa[0] = -1;
    for (int i = 0; i < l; i++) {
        Extend (s[i] - 'a');
        //在SAM上扩展一个字符s[i] - 'a';
    }
    for (int i = 1; i <= node; i++) t[len[i]]++;
    for (int i = 1; i <= node; i++) t[i] += t[i - 1];
    for (int i = 1; i <= node; i++) A[t[len[i]]--] = i;
    //A记录最大串的长度第i大的类的编号
    for (int i = node; i >= 1; i--) {
        //从小到大枚举，实际上在模拟parent树的DFS
        //比DAG上跑拓扑DP好写QwQ
        int now = A[i]; siz[fa[now]] += siz[now];
        if (siz[now] > 1) {
            ans = max (ans, 1ll * siz[now] * len[now]);
        }
    }
    printf ("%lld\n", ans);
    return 0;
}
