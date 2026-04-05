#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const ll inf=1e16;
int T;
int n,op;
vector<int> e[N];
int root;
int fa[N],de[N],si[N];
int hs[N],hi[N];
int sm[N],om[N];
int sb[N],ob[N];
int pk[N];
ll sd[N],od[N],td[N];
ll sc[N],oc[N],ans[N];
ll A[N*3],h[N];
ll *ptr,*down[N],*up[N];
void find_rt(int no,int ff){
	si[no]=1;
	int mx=0;
	for(int to:e[no]){
		if(to==ff)continue;
		find_rt(to,no);
		si[no]+=si[to];
		mx=max(mx,si[to]);
	}
	mx=max(mx,n-si[no]);
	if(mx*2<=n)root=no;
}
void dfs_sub(int no,int ff){
	fa[no]=ff;
	de[no]=de[ff]+1;
	si[no]=1;
	hs[no]=0;
	sd[no]=0;
	for(int to:e[no]){
		if(to==ff)continue;
		dfs_sub(to,no);
		si[no]+=si[to];
		sd[no]+=sd[to]+si[to];
		if(si[to]>si[hs[no]])hs[no]=to;
	}
	int s=hs[no];
	if(si[s]*2<=si[no]){
		sm[no]=no;
		sc[no]=sd[no];
	}
	else{
		int id=sm[s];
		sc[no]=sc[s]+(sd[no]-sd[s]-si[s])+(ll)(de[id]-de[no])*(si[no]-si[s]);
		while(si[id]*2<si[no]){
			sc[no]-=si[no]-(ll)2*si[id];
			id=fa[id];
		}
		sm[no]=id;
	}
	sb[no]=de[sm[no]]-de[no];
}
void dfs_od(int no,int fa){
	for(int to:e[no]){
		if(to==fa)continue;
		od[to]=od[no]+sd[no]-sd[to]-si[to]+(n-si[to]);
		dfs_od(to,no);
	}
}
void dfs_oinf(int no,int fa){
	for(int to:e[no]){
		if(to!=fa)dfs_oinf(to,no);
	}
	int x=pk[si[no]];
	om[no]=x;
	ob[no]=de[no]+de[x];
	oc[no]=sd[x]+od[x]-sd[no]-(ll)si[no]*ob[no];
}
void dfs_hi(int no,int fa){
	hs[no]=0;
	for(int to:e[no]){
		if(to==fa)continue;
		dfs_hi(to,no);
		if(hi[to]>hi[hs[no]])hs[no]=to;
	}
	hi[no]=hi[hs[no]]+1;
}
void pull_dp(int no,int fa){
	if(hs[no]){
		down[hs[no]]=down[no]-1;
		up[hs[no]]=up[no]+1;
		pull_dp(hs[no],no);
	}
	int mx=0;
	vector<int> lts;
	for(int to:e[no]){
		if(to==fa||to==hs[no])continue;
		ptr+=hi[to];
		down[to]=ptr;
		ptr+=hi[to];
		up[to]=ptr+1;
		ptr+=hi[to];
		pull_dp(to,no);
		lts.push_back(to);
		mx=max(mx,hi[to]);
		for(int d=0;d<hi[to];++d){
			up[to][d]=min(up[to][d],down[no][d+1]);
		}
	}
	for(int i=0;i<mx;++i)h[i]=inf;
	for(int to:lts){
		for(int d=0;d<hi[to];++d){
			up[to][d]=min(up[to][d],h[d]);
		}
		for(int d=2;d<=hi[to];++d){
			h[d-2]=min(h[d-2],down[to][d]);
		}
	}
	reverse(lts.begin(),lts.end());
	for(int i=0;i<mx;++i)h[i]=inf;
	for(int to:lts){
		for(int d=0;d<hi[to];++d){
			up[to][d]=min(up[to][d],h[d]);
		}
		for(int d=2;d<=hi[to];++d){
			h[d-2]=min(h[d-2],down[to][d]);
		}
	}
	for(int to:e[no]){
		if(to==fa||to==hs[no])continue;
		for(int d=1;d<=hi[to];++d){
			down[no][d-1]=min(down[no][d-1],down[to][d]);
		}
	}
	if(hs[no])ans[no]=min(ans[no],td[no]+down[no][0]);
	if(!fa)return;
	int d=sb[no];
	ll bs=sc[no]-sd[no];
	if(d)down[no][d]=min(down[no][d],bs-(ll)d*si[no]);
	down[no][d+1]=min(down[no][d+1],bs-(ll)(d+1)*si[no]);
}
void push_dp(int no,int fa){
	if(fa){
		int d=ob[no]-1;
		ll bs=oc[no]-od[no];
		if(d>0&&d-1<hi[no]){
			up[no][d-1]=min(up[no][d-1],bs-(ll)(d-1)*(n-si[no]));
		}
		if(d<hi[no]){
			up[no][d]=min(up[no][d],bs-(ll)d*(n-si[no]));
		}
	}
	ans[no]=min(ans[no],td[no]+up[no][0]);
	for(int to:e[no]){
		if(to==fa||to==hs[no])continue;
		for(int d=0;d<hi[to];++d){
			up[to][d]=min(up[to][d],up[no][d+1]);
		}
	}
	for(int to:e[no]){
		if(to==fa||to==hs[no])continue;
		for(int d=2;d<=hi[to];++d){
			up[no][d-1]=min(up[no][d-1],down[to][d]);
		}
	}
	for(int to:e[no]){
		if(to==fa)continue;
		push_dp(to,no);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>op;
		for(int i=1;i<=n;++i){
			e[i].clear();
		}
		for(int i=1;i<n;++i){
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		if(n==1){
			cout<<"0\n";
			continue;
		}
		de[0]=-1;
		find_rt(1,0);
		dfs_sub(root,0);
		od[root]=0;
		dfs_od(root,0);
		fill(pk,pk+n+1,0);
		pk[0]=root;
		for(int no=hs[root];no;no=hs[no]){
			pk[n-2*si[no]]=no;
		}
		for(int i=1;i<=n;++i){
			if(!pk[i])pk[i]=pk[i-1];
		}
		int se=0;
		for(int to:e[root]){
			if(to==hs[root])continue;
			dfs_oinf(to,root);
			if(si[to]>si[se])se=to;
		}
		fill(pk,pk+n+1,0);
		pk[0]=root;
		for(int no=se;no;no=hs[no]){
			pk[n-2*si[no]]=no;
		}
		for(int i=1;i<=n;++i){
			if(!pk[i])pk[i]=pk[i-1];
		}
		dfs_oinf(hs[root],root);
		for(int i=1;i<=n;++i){
			td[i]=sd[i]+od[i];
			ans[i]=td[i];
		}
		dfs_hi(root,0);
		fill(A,A+3*n+5,inf);
		ptr=A;
		ptr+=hi[root];
		down[root]=ptr;
		ptr+=hi[root];
		up[root]=ptr;
		ptr+=hi[root];
		pull_dp(root,0);
		push_dp(root,0);
		if(op==1){
			ll as=ans[1];
			for(int i=2;i<=n;++i)as=min(as,ans[i]);
			cout<<as<<'\n';
		}
		else if(op==2){
			cout<<ans[1]<<'\n';
		}
		else{
			for(int i=1;i<=n;++i){
				cout<<ans[i]<<' ';
			}
			cout<<'\n';
		}
	}
	return 0;
}