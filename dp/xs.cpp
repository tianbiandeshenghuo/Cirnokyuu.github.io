#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

using namespace std;
const int MAXN = 2e5 + 5;
int n, q, a[MAXN], bg[MAXN], ed[MAXN];
int sz[MAXN], top[MAXN], fa[MAXN], son[MAXN], sd[MAXN], ans[MAXN], sum, k[MAXN];
bool vis[MAXN];
struct Node{
  int l, r, lca, id;
  bool operator<(const Node &i)const{
    return k[l] == k[i.l] ? r < i.r : k[l] < k[i.l];
  }
}qr[MAXN];
vector<int> p, g[MAXN];
map<signed, signed> col;
void dfs1(int x, int f){
  fa[x] = f;
  sz[x]++;
  sd[x] = sd[f] + 1;
  p.push_back(x);
  bg[x] = p.size() - 1;
  for (auto v : g[x]){
    if (v != f){
      dfs1(v, x);
      sz[x] += sz[v];
      if (sz[v] > sz[son[x]]){
        son[x] = v;
      }
    }
  }
  p.push_back(x);
  ed[x] = p.size() - 1;
}
void dfs2(int x, int f){
  top[x] = f;
  if (son[x]){
    dfs2(son[x], f);
  }
  for (auto v : g[x]){
    if (v != fa[x] && v != son[x]){
      dfs2(v, v);
    }
  }
}
int Lca(int x, int y){
  while (top[x] != top[y]){
    if (sd[top[x]] < sd[top[y]]){
      swap(x, y);
    }
    x = fa[top[x]];
  }
  return sd[x] < sd[y] ? x : y;
}
void add(int x){
  if (vis[x]){
    col[a[x]]--;
    sum -= col[a[x]] == 0;
  }else {
    col[a[x]]++;
    sum += col[a[x]] == 1;
  }
  vis[x] ^= 1;
}
int read(){
  int x = 0, t = 1;
  char ch = getchar();
  while(ch < '0' || ch > '9'){
    if(ch == '-'){
      t = -1;
    }
    ch = getchar();
  }
  while(ch >= '0' && ch <= '9'){
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * t;
}
void print(int x){
  if(x < 0){
    putchar('-');
		x = -x;
	}
  if(x > 9){
	  print(x / 10);
  }
  putchar(x % 10 + '0');
}
signed main(){
  p.push_back(0);
  n = read(), q = read();
  const int kc = sqrt(2 * n);
  for (int i = 1; i <= 2 * n; i++){
    k[i] = i / kc;
  }
  for (int i = 1; i <= n; i++){
    a[i] = read();
  }
  for (int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  for (int i = 1, l, r; i <= q; i++){
    l = read(), r = read();
    if (sd[l] > sd[r]){
      swap(l, r);
    }
    int lca = Lca(l, r);
    if (l == lca){
      qr[i] = {bg[l], bg[r]};
    }else {
      qr[i] = {ed[l], bg[r], lca};
    }
    qr[i].id = i;
  }
  sort(qr + 1, qr + q + 1);
  int l = 1, r = 0;
  for (int i = 1; i <= q; i++){
    while (l < qr[i].l){
      add(p[l++]);
    }
    while (l > qr[i].l){
      add(p[--l]);
    }
    while (r < qr[i].r){
      add(p[++r]);
    }
    while (r > qr[i].r){
      add(p[r--]);
    }
    //cerr << p[qr[i].l] << ' ' << p[qr[i].r] << ' ' << qr[i].lca << ' ' << a[qr[i].lca] << ' ' << col[a[qr[i].lca]] << ' ' << vis[qr[i].lca] << ' ' << sum << '\n';
    if (qr[i].lca){
      add(qr[i].lca);
    }
    //cerr << p[qr[i].l] << ' ' << p[qr[i].r] << ' ' << qr[i].lca << ' ' << a[qr[i].lca] << ' ' << col[a[qr[i].lca]] << ' ' << vis[qr[i].lca] << ' ' << sum << '\n';
    ans[qr[i].id] = sum;
    if (qr[i].lca){
      add(qr[i].lca);
    }
  }
  for (int i = 1; i <= q; i++){
    print(ans[i]);
    putchar('\n');
  }
  return 0;
}