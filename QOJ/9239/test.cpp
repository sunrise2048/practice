#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
//#define int long long
//#define ull unsigned long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 200005
#define inf 0x3f3f3f3f

template<class info>
struct segt1{
	int n;
	vector<info>tr;
	vector<int>leaf;
	void init(vector<info>a){
		n=a.size(); assert(n);
		tr.assign(4<<__lg(n),info());
		leaf.resize(n);
		function<void(int,int,int)>build=[&](int p,int l,int r){
			if(l==r)return leaf[l]=p,tr[p]=a[l],void();
			int mid=l+r>>1;
			build(p<<1,l,mid),build(p<<1|1,mid+1,r),up(p);
		};
		build(1,0,n-1);
	}
	void init(int _n){
		init(vector<info>(_n));
	}
	void up(int p){
		tr[p]=tr[p<<1]+tr[p<<1|1];
	}
	void upd(int x,info y){
		--x;
		x=leaf[x],tr[x]=y;
		while(x>>=1)up(x);
	}
	info ask(int p,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tr[p];
		int mid=l+r>>1;
		if(qr<=mid)return ask(p<<1,l,mid,ql,qr);
		if(ql>mid)return ask(p<<1|1,mid+1,r,ql,qr);
		return ask(p<<1,l,mid,ql,qr)+ask(p<<1|1,mid+1,r,ql,qr);
	}
	info ask(int l,int r){
		if(l>r)return info();
		--l,--r;
		return ask(1,0,n-1,l,r);
	}
};
struct info{
	int x;
	info (int xx=inf){
		x=xx;
	}
};
info operator +(info a,info b){
	return info(min(a.x,b.x));
}

vi NO={-1};
int n,m,a[maxn],b[maxn];

/*
int f[3005][3005];
vi brute(){
	For(i,1,n){
		For(j,1,m)
			f[i][j]=max({f[i-1][j],f[i][j-1],f[i-1][j-1]+(a[i]==b[j])});
	}
	int u=n,v=m;
	vi t;
	while(u>1 || v>1){
		if(a[u]==b[v]) t.pb(a[u]),--u,--v;
		else if(v && f[u][v]==f[u][v-1]) --v;
		else --u;
	}
	reverse(ALL(t));
	return t;
}
*/

vi va[maxn],vb[maxn];
int opa[maxn],opb[maxn];

int find(vi &o,int x){
	auto it=upper_bound(ALL(o),x);
	if(it==o.end()) return inf;
	return *it;
}

int geta(int x,int c){
	return find(va[c],x);
}
int getb(int x,int c){
	return find(vb[c],x);
}

int cnta[maxn],cntb[maxn];

vi get(){
	For(i,1,n) va[a[i]].pb(i),++cnta[a[i]];
	For(i,1,m) vb[b[i]].pb(i),++cntb[b[i]];
	For(i,0,200000)
		if(va[i].size()<=vb[i].size()) {
			for(int x:va[i]) opa[x]=1;
		}else{
			for(int x:vb[i]) opb[x]=1;
		}
	vi res;
	int pa=1,pb=1;
	
	int ua=0,ub=0; // <=ua used.
	auto A=[&](){
		--cnta[a[pa]],res.pb(a[pa]),++pa;
	};
	auto B=[&](){
		--cntb[b[pb]],res.pb(b[pb]),++pb;
	};
	
	//For(i,0,1) cout<<va[i].size()<<" "<<vb[i].size()<<" sz\n";
	
	while(pa<=n || pb<=m){
		while(pa<=n && !opa[pa]) --cnta[a[pa]],++pa;
		while(pb<=m && !opb[pb]) --cntb[b[pb]],++pb;
		
		if(pa>n && pb>m) break;
		if(pa<ua || pb<ub) return NO;
		
		bool oka=(pa<=n),okb=(pb<=m);
		
		int qb=geta(ua,b[pb]);
		int qa=getb(ub,a[pa]);
//		cout<<pa<<" "<<qb<<"\n";
//		cout<<pb<<" "<<qa<<"\n";
//		cout<<"-----\n";
		if(qa>pb) oka=0;
		if(qb>pa) okb=0;
		
		if(cnta[b[pb]]<cntb[b[pb]]) oka=0;
		if(cntb[a[pa]]<cnta[a[pa]]) okb=0;
		
	//	if(oka==okb) cout<<"ok "<<oka<<" "<<okb<<"\n";
		if(!oka && !okb) return NO;
		if(oka && okb) return NO;
		if(oka) ub=qa,A();
		else ua=qb,B();
	}
	return res;
}

int c[maxn],len;
int toa[maxn],tob[maxn];

int f[maxn];
int prec[maxn];
bool vis[maxn];

bool chk(vi o){
	if(o==NO)return 0;
	if(!o.size()) return 1;
	
	len=o.size();
	For(i,1,len)c[i]=o[i-1];
	
	int p=1;
	For(i,1,len){
		while(p<=n && a[p]!=c[i])++p;
		if(p>n)return 0;
		toa[i]=p,++p;
	}
	p=1;
	For(i,1,len){
		while(p<=m && b[p]!=c[i])++p;
		if(p>m)return 0;
		tob[i]=p,++p;
	}

	For(_,0,1){
		
		segt1<info>T;
		T.init(len);
		
		memset(prec,0,sizeof prec);
		For(i,1,len){
			f[i]=tob[i];
			int mn=inf,hav=0;
			
			auto it=lower_bound(ALL(va[c[i]]),toa[i]);
			int pre=0;
			if(it!=va[c[i]].begin()) pre=*prev(it);
			
			if(!prec[c[i]]) {
				int fira=va[c[i]][0],firb=vb[c[i]][0];
				if(fira<toa[i] && firb<tob[i]) return 0;
				f[i]=min(f[i],firb);
			}
			
			int l2=prec[c[i]]; prec[c[i]]=i;
			l2=max(l2,1);
			int l1=lower_bound(toa+1,toa+len+1,pre)-toa;
			// toa[l1]>=pre
			
			int mn1=inf,mn2=inf;
//			Rep(j,i-1,1){
//				if(toa[j]<pre) mn2=min(mn2,f[j]);
//				else mn1=min(mn1,f[j]);
//				if(c[j]==c[i]) break;
//			}
		//	cout<<"l2,l1 "<<l2<<" "<<l1<<"\n";
			
			mn1=T.ask(l1,i-1).x;
			mn2=T.ask(l2,l1-1).x;
			
		//	cout<<"mn1 "<<mn1<<" "<<mn2<<"\n";
			
			int nxt1=getb(mn1,c[i]),nxt2=getb(mn2,c[i]);
			if(nxt2<tob[i]) return 0;
			f[i]=min(f[i],nxt1);
			T.upd(i,f[i]);
		//	cout<<"i: "<<i<<" "<<f[i]<<"\n";
		}
		
		memset(vis,0,sizeof vis);
		
		Rep(i,len,1) if(!vis[c[i]]) {
			vis[c[i]]=1;
			if(va[c[i]].size() && vb[c[i]].size() && toa[i]<va[c[i]].back()){
				int lim=lower_bound(toa+1,toa+len+1,va[c[i]].back())-toa;
				int mn=T.ask(i,lim-1).x;
				if(mn<vb[c[i]].back()) return 0;
//				For(j,i,lim-1){
//					if(f[j]<vb[c[i]].back()) return 0;
//				}
			}
		}
		
		if(_==0){
			swap(n,m),swap(a,b),swap(va,vb),swap(toa,tob);
		}
	}
	
	return 1;
}

vi ucs(vi A,vi B)
{
	n=A.size(),m=B.size();
	For(i,1,n)a[i]=A[i-1];
	For(i,1,m)b[i]=B[i-1];
	vi o=get();
	if(!chk(o)) return NO;
	return o;
}
int main() {
    freopen("01.in","r",stdin);
    freopen("01.ans","w",stdout);
    int N, M;
    assert(2 == scanf("%d%d", &N, &M));
    std::vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
        assert(1 == scanf("%d", &A[i]));
    for (int j = 0; j < M; j++)
        assert(1 == scanf("%d", &B[j]));
    fclose(stdin);

    std::vector<int> R = ucs(A, B);

    int T = (int)R.size();
    printf("%d\n", T);
    for (int i = 0; i < T; i++)
        printf("%s%d", (i == 0 ? "" : " "), R[i]);
    printf("\n");
    fclose(stdout);

    return 0;
}