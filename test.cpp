#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
inline int read()
{
	int d=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') {d=d*10+c-48;c=getchar();}
	return d*f;
}

class SimpleX{
   public:
   const int inf=1e12;
   int head[1005];
   int nxt[502005];
   short from[502005];
   short to[502005];
   short flow[502005];
   int cost[502005];
   int cnt=1;
   void addedge(int u,int v,int fl,int co){
      cnt++;
      to[cnt]=v;
      from[cnt]=u;//
      nxt[cnt]=head[u];
      head[u]=cnt;
      flow[cnt]=fl;
      cost[cnt]=co;
      return;
   }
   void Add(int u,int v,int fl,int co){
      addedge(u,v,fl,co);
      addedge(v,u,0,-co);
      return;
   }

   short fa[1005];
   int fe[1005];
   int tag[1005];
   int pos;
   void gettree(int cur){
      tag[cur]=pos;
      for(int i=head[cur];i;i=nxt[i]){
         int v=to[i];
         if(tag[v]||!flow[i])continue;
         fa[v]=cur;
         fe[v]=i;
         gettree(v);
      }
   }
   int pushflow(int id){
      pos++;
      int u=from[id],v=to[id];
      int lca=u;
      while(lca){
         tag[lca]=pos;
         lca=fa[lca];
      }
      lca=v;
      while(tag[lca]!=pos){
         tag[lca]=pos;
         lca=fa[lca];
      }
      int p=2,minflow=flow[id],del;
      for(int now=u;now^lca;now=fa[now]){
         int eg=fe[now];
         if(flow[eg]<minflow){
            p=0;
            minflow=flow[eg];
            del=now;
         }
      }
      for(int now=v;now^lca;now=fa[now]){//
         int eg=fe[now]^1;
         if(flow[eg]<minflow){
            p=1;
            minflow=flow[eg];
            del=now;
         }
      }
      int C=0;
      for(int now=u;now^lca;now=fa[now]){
         int eg=fe[now];
         flow[eg]-=minflow;
         flow[eg^1]+=minflow;
         C=(C+minflow*cost[eg]);
      }
      for(int now=v;now^lca;now=fa[now]){
         int eg=fe[now]^1;
         flow[eg]-=minflow;
         flow[eg^1]+=minflow;
         C=(C+minflow*cost[eg]);
      }
      flow[id]-=minflow;
      flow[id^1]+=minflow;
      C=(C+minflow*cost[id]);
      if(p==2){
         return C;
      }
      if(p)swap(u,v);
      int Le=id^p,Lu=v;
      while(Lu!=del){
         Le^=1;
         tag[u]=0;
         swap(fe[u],Le);
         int need=fa[u];
         fa[u]=Lu;
         Lu=u;
         u=need;
      }
      return C;
   }
   int dep[1005];
   int getdep(int x){
      if(tag[x]==pos)return dep[x];
      tag[x]=pos;
      return dep[x]=getdep(fa[x])+cost[fe[x]];
   }
   pair<int,int> getflow(int s,int t){
      Add(t,s,inf,-inf);
      pos++;
      gettree(t);
      fa[t]=0;
      pos++;
      tag[t]=pos;
      bool flag=true;
      while(flag){
         flag=false;
         for(int i=2;i<=cnt;i++){
            int u=from[i],v=to[i];
            if(!flow[i])continue;
            if(cost[i]+getdep(u)-getdep(v)<0){
               flag=true;
               pushflow(i);
            }
         }
      }
      long long ansflow=flow[cnt];
      long long anscost=0;
      for(int i=2;i<=cnt;i+=2){
         anscost=anscost+flow[i^1]*cost[i];
      }
      return make_pair(ansflow,anscost+(ansflow*inf));
   }
}G;
int n,m;
int pre[505];
signed main(){
   n=read(),m=read();
   for(int i=1;i<=m;i++){
      int u,v,w;
      u=read(),v=read(),w=read();
      G.Add(u,v+n,1,-w);
   }
   int s=2*n+1,t=2*n+2;
   for(int i=1;i<=n;i++){
      G.Add(s,i,1,0);
      G.Add(i+n,t,1,0);
   }
   printf("%lld\n",-G.getflow(s,t).second);
   for(int i=2;i<=G.cnt;i+=2){
      if(G.flow[i^1]){
         if(G.from[i]==s||G.to[i]==t)continue;
         pre[G.to[i]-n]=G.from[i];
      }
   }
   for(int i=1;i<=n;i++){
      printf("%lld ",pre[i]);
   }
   puts("");
   return 0;
}
