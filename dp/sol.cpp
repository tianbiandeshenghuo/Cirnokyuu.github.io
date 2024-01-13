#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,len,a[100005],lst[200005],dep[100005],f[100005][25],dfn[100005],nxt[100005];

vector <int> to[100005];

map<int,int> mp;int idk;

int lt=1,rt,t[100005],tag[100005],cnt,res,ans[100005];

inline void dfs(int x,int last){
	dep[x]=dep[last]+1;
	dfn[x]=++cnt,lst[cnt]=x,f[x][0]=last;
	for(int y:to[x]){
		if(y!=last)dfs(y,x);
	}nxt[x]=++cnt,lst[cnt]=x;return;
}

inline void init(){
	dfs(1,0);
	for(int j=1;1<<j<=n;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}return;
}

inline int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int h=dep[x]-dep[y];
	for(int i=0;i<=20;i++){
		if(h&(1<<i))x=f[x][i];
	}if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i],y=f[y][i];
		}
	}return f[x][0];
}

struct node{
	int l,r,k,id;
}q[100005];

inline bool cmp(node x,node y){
	return (x.l-1)/len==(y.l-1)/len?x.r<y.r:(x.l-1)/len<(y.l-1)/len;
}

inline void add(int x){
	t[x]++,res+=(t[x]==1);return;
}

inline void del(int x){
	t[x]--,res-=(t[x]==0);return;
}

inline void updata(int x){
	tag[x]^=1;
	if(tag[x])add(a[x]);
	else del(a[x]);
	return;
}

inline int read(){
	register int x(0),t(1);
	static char ch=getchar();
	while(!isdigit(ch)){t=ch=='-'?-1:t;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*t;
}

signed main(){
	n=read(),m=read(),len=sqrt(2*n);
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!mp[a[i]])mp[a[i]]=++idk;
		a[i]=mp[a[i]];
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		to[x].push_back(y),to[y].push_back(x); 
	}init();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),k=lca(x,y);
		if(dfn[x]>dfn[y])swap(x,y);
		if(k==x||k==y){
			q[i]={dfn[x],dfn[y],-1,i};
		}else q[i]={nxt[x],dfn[y],k,i};
	}sort(q+1,q+1+m,cmp);
	for(int i=1;i<=m;i++){
		while(lt>q[i].l)updata(lst[--lt]);
		while(rt<q[i].r)updata(lst[++rt]);
		while(lt<q[i].l)updata(lst[lt++]);
		while(rt>q[i].r)updata(lst[rt--]);
		if(q[i].k!=-1)updata(q[i].k);
		ans[q[i].id]=res;
		if(q[i].k!=-1)updata(q[i].k);
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<'\n';
	}
	return 0;
}