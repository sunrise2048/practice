#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
struct edge
{
	int v,nxt;
}e[2000005];
namespace qwq
{
	int st[22][1000005],val[1000005],b[1000005],lg[1000005];
	void build(int n)
	{
		lg[1]=0;
		for(int i=2;i<=n;i++)
			lg[i]=lg[i/2]+1;
	//	printf("build:n=%d\n",n);
		for(int i=1;i<=n;i++)
		{
			st[0][i]=b[i];
	//		printf("%d ",b[i]);
		}
	//	printf("\n");
		for(int i=1;i<=20;i++)
			for(int j=1;j<=n;j++)
				if(val[st[i-1][j]]<=val[st[i-1][j+(1<<(i-1))]])
					st[i][j]=st[i-1][j];
				else st[i][j]=st[i-1][j+(1<<(i-1))];
	}
	int query(int l,int r)
	{
		int nw=lg[r-l+1];
		if(val[st[nw][l]]<val[st[nw][r-(1<<nw)+1]])
			return st[nw][l];
		return st[nw][r-(1<<nw)+1];
	}
}
int getans(int u,int v);
namespace SGT
{
	int tans[30000005];
	int sum[30000005][2],ls[30000005],rs[30000005],ct;
	void pushup(int x)
	{
		if(!ls[x]||!rs[x])
		{
			sum[x][0]=sum[ls[x]+rs[x]][0];
			sum[x][1]=sum[ls[x]+rs[x]][1];
			tans[x]=tans[ls[x]+rs[x]];
			return;
		}
		sum[x][0]=sum[ls[x]][0];
		sum[x][1]=sum[rs[x]][1];
		tans[x]=tans[ls[x]]+tans[rs[x]]+getans(sum[ls[x]][1],sum[rs[x]][0]);
	}
	int merge(int x,int y)
	{
		if(!x||!y) return x+y;
		ls[x]=merge(ls[x],ls[y]);
		rs[x]=merge(rs[x],rs[y]);
		if(ls[x]||rs[x]) pushup(x);
		return x;
	}
	int modify(int x,int l,int r,int qx,int v)
	{
		if(l>qx||r<qx) return x;
		if(!x)
		{
			x=++ct;
			sum[x][0]=sum[x][1]=ls[x]=rs[x]=tans[x]=0;
		}
		if(l==r)
		{
			sum[x][0]=sum[x][1]=v;
			return x;
		}
		int mid=(l+r)/2;
		ls[x]=modify(ls[x],l,mid,qx,v);
		rs[x]=modify(rs[x],mid+1,r,qx,v);
		pushup(x);
		return x;
	}
	int F(int x)
	{
		return tans[x]+getans(sum[x][0],sum[x][1]);
	}
}
int n,m,h[1000005],t,sz[1000005],rt,vis[1000005],d[1000005],g[1000005],cov[1000005];
int gg[22][1000005],nid[1000005],sum[1000005],dfn[1000005],cnt,udfn[1000005];
ll nans[1000005],sumnans[1000005],qans[1000005],srt[1000005];
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
void dfs1(int u,int fa,int ssz)
{
	sz[u]=1;
	int mx=0;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		dfs1(v,u,ssz);
		sz[u]+=sz[v];
		mx=max(mx,sz[v]);
	}
	mx=max(mx,ssz-sz[u]);
	if(mx*2<=ssz) rt=u;
}
int bt,fir[1000005],las[1000005];
int lca(int u,int v)
{
	if(fir[u]>fir[v]) swap(u,v);
	return qwq::query(fir[u],fir[v]);
}
void dfs2(int u,int fa,int dep)
{
	qwq::val[u]=d[u]=dep;
	qwq::b[++bt]=u;
	fir[u]=bt;
	g[u]=u;
	cov[u]=sum[u]=srt[u]=0;
	dfn[u]=++cnt;
	udfn[cnt]=u;
	sz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		dfs2(v,u,dep+1);
		qwq::b[++bt]=u;
		sz[u]+=sz[v];
	}
}
void dfs3(int u,int fa)
{
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		dfs3(v,u);
		if(d[g[v]]<d[g[u]]) g[u]=g[v];
		cov[u]|=cov[v];
	}
}
void dfs4(int u,int fa)
{
	if(cov[u]) nans[u]=0,nid[u]=u;
	else nans[u]=nans[g[u]]+1,nid[u]=nid[g[u]];
	sum[nid[u]]++;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		dfs4(v,u);
	}
//	printf("dfs4:u=%d,fa=%d,nans=%lld,nid=%d\n",u,fa,nans[u],nid[u]);
}
void dfs5(int u,int fa)
{
	sumnans[u]=nans[u];
//	printf("u=%d,sum=%d\n",u,sum[u]);
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		sum[v]+=sum[u];
		dfs5(v,u);
		sumnans[u]+=sumnans[v];
	}
}
int getans(int u,int v)
{
	return sum[u]+sum[v]-2*sum[lca(u,v)];
}
int tmp[1000005];
void dfs6(int u,int fa)
{
	srt[u]=SGT::modify(srt[u],1,n,dfn[rt],rt);
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		dfs6(v,u);
		srt[u]=SGT::merge(srt[u],srt[v]);
	}
//	printf("dfs6:u=%d,fa=%d,sum=%d,%d,tans=%d\n",u,fa,SGT::sum[srt[u]][0],SGT::sum[srt[u]][1]
//	,SGT::tans[srt[u]]);
	tmp[u]=SGT::F(srt[u])/2;
	//qans[u]-=SGT::F(srt[u]);
}
int col[1000005];
void dfz(int u,vector<pair<int,int> > p)
{
	SGT::ct=0;
	int len=p.size();
	for(int i=0;i<len;i++)
		if(p[i].first>p[i].second)
			swap(p[i].first,p[i].second);
	sort(p.begin(),p.end());
	len=unique(p.begin(),p.end())-p.begin();
//	printf("dfz:u=%d,len=%d----\n",u,len);
	p.resize(len);
	dfs1(u,0,0);
	dfs1(u,0,sz[u]);
	int nrt=rt;
	bt=cnt=0;
	dfs2(nrt,0,1);
	qwq::build(bt);
	len=p.size();
//	printf("dfz:u=%d,nrt=%d----\n",u,nrt);
	for(int i=0;i<len;i++)
	{
		int u=p[i].first,v=p[i].second,l=lca(u,v);
		if(d[g[u]]>d[l]) g[u]=l;
		if(d[g[v]]>d[l]) g[v]=l;
		if(l==nrt) cov[u]=cov[v]=1;
	}
	dfs3(nrt,0);
	dfs4(nrt,0);
	dfs5(nrt,0);
//	printf("dfz:u=%d----\n",u);
	int nw=0;
	vector<int> son;
	qans[nrt]+=sumnans[nrt]+sz[nrt]-sum[nrt];
	for(int i=h[nrt];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]) continue;
		son.push_back(v);
		for(int j=dfn[v];j<dfn[v]+sz[v];j++)
		{
			int x=udfn[j];
			qans[x]+=(sumnans[nrt]-sumnans[v])-sum[nrt]+1ll*(sz[nrt]-sz[v])*(nans[x]+1);
			if(nid[x]!=nrt)
				qans[x]+=(sz[nrt]-sz[v]);
			col[x]=nw;
	//		printf("v=%d,x=%d,qans=%lld\n",v,x,qans[x]);
		}
		nw++;
	}
//	printf("dfz:u=%d----\n",u);
	vector<vector<pair<int,int> > > ps;
	ps.resize(nw);
	for(int i=0;i<len;i++)
	{
		int u=p[i].first,v=p[i].second,l=lca(u,v);
	//	printf("i=%d,u=%d,v=%d,l=%d,dfn=%d,%d\n",i,u,v,l,dfn[u],dfn[v]);
		if(l==nrt)
		{
			srt[u]=SGT::modify(srt[u],1,n,dfn[v],v);
			srt[v]=SGT::modify(srt[v],1,n,dfn[u],u);
		}
		if(l!=nrt)
			ps[col[l]].push_back(p[i]);
		else 
		{
			if(u!=nrt) ps[col[u]].push_back(make_pair(u,son[col[u]]));
			if(v!=nrt) ps[col[v]].push_back(make_pair(v,son[col[v]]));
		}
	}
	dfs6(nrt,0);
	for(int i=dfn[nrt]+1;i<dfn[nrt]+sz[nrt];i++)
	{
		int x=udfn[i];
		if(nid[x]!=nrt)
			qans[x]-=tmp[nid[x]];
	}
	//printf("dfz:u=%d----\n",u);
	for(int i=dfn[nrt];i<dfn[nrt]+sz[nrt];i++)
	{
		int x=udfn[i];
//		printf("x=%d,qans=%lld\n",x,qans[x]);
	}
	nw=0; 
	vis[nrt]=1;
	for(int i=h[nrt];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(vis[v]) continue;
		dfz(v,ps[nw]);
		nw++;
	}
}
int main()
{
    freopen("bus.in","r",stdin);
    freopen("bus.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	vector<pair<int,int> > p;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		p.push_back(make_pair(u,v));
	}
	dfz(1,p);
	for(int i=1;i<=n;i++)
		printf("%lld ",qans[i]);
	printf("\n");
	return 0;
}