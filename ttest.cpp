#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 1e6 + 5;
int n;
double ans;
void dfs(set<int> a, int cnt, double op){
  if (!a.size()){
    ans += cnt * op;
    return ;
  }
  for (auto v : a){
    set<int> p = a;
    int cn = v;
    if (cn == 1){
      p.erase(1);
      dfs(p, cnt + 1, 1.0 * op / (p.size() + 1));
      continue;
    }
    int tmp = p.size();
    while (cn <= n){
      p.erase(cn);
      cn *= v;
    }
    dfs(p, cnt + 1, 1.0 * op / tmp);
  }
}
void Solve(){
  ans = 0;
  set<int> b;
  for (int i = 1; i <= n; i++){
    b.insert(i);
  }
  dfs(b, 0, 1);
  cout << fixed << setprecision(10) << ans << '\n';
}
signed main(){
  freopen("ans.txt", "w", stdout);
  for (int i = 1; i <= 1e9; i++){
    n = i;;
    Solve();
    cerr << i << '\n';
  }
  return 0;
}