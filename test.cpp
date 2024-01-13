#include<bits/stdc++.h>
#define f first
#define s second

using namespace std;
const int MAXN = 1e3 + 5;
int n, m, a[MAXN];
struct Node{
  int v, id;
};
vector<Node> g[MAXN];
vector<pair<int, pair<int, int>>> c;
vector<pair<int, vector<int>>> b;
void dfs(int x, int p, vector<int> c){
  if (x == n){
    b.push_back({p, c});
    return ;
  }
  for (auto v : g[x]){
    c.push_back(v.id);
    dfs(v.v, p + 1, c);
    c.pop_back();
  }
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  c.push_back({0, {0, 0}});
  for (int i = 1, u, v; i <= m; i++){
    cin >> u >> v;
    c.push_back({u, {v, 0}});
    g[u].push_back({v, i});
  }
  dfs(1, 0, vector<int> ());
  int cnt = 1;
  for (auto v : b){
    cnt = lcm(cnt, v.f);
  }
  for (auto v : b){
    for (auto vv : v.s){
      c[vv].s.s = cnt / v.s.size();
    }
  }
  //cerr << cnt;
  cout << n << ' ' << m << '\n';
  for (auto v : c){
    if (!v.f){
      continue;
    }
    cout << v.f << ' ' << v.s.f << ' ' << v.s.s << '\n';
  }
  return 0;
}