#include<bits/stdc++.h>
using namespace std;
class BCJ{
public:
    vector<int> fa;
    BCJ(int n){init(n);}
    void init(int n){
        fa.resize(n+1);
        iota(fa.begin(),fa.end(),0);
    }
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){fa[find(x)]=find(y);}
};
struct edge{
    int u,v,id;
};
int main(){
    freopen("redraw.in","r",stdin);
    freopen("redraw.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        vector<int> U(m+1),V(m+1),din(n+1),p(n+1),q(n+1);
        for(int i=1;i<=m;++i)cin>>U[i]>>V[i],++din[V[i]];
        string s;
        cin>>s;
        for(int i=1;i<=n;++i)p[i]=q[i]=din[i]-1;
        BCJ bcj(n);
        vector<int> dif;
        for(int i=1;i<=m;++i)if(s[i-1]=='1'){
            dif.push_back(i);
            bcj.merge(U[i],V[i]);
            ++q[U[i]],--q[V[i]];
        }
        bool fl=1;
        for(int i=1;i<=n;++i)if(q[i]<0)fl=0;
        if(!fl){
            cout<<"No\n";
            continue;
        }
        vector<vector<pair<int,int>>> g0(n+1);
        for(int i=1;i<=m;++i)
            if(s[i-1]=='0')g0[V[i]].push_back({U[i],i});
        vector<vector<int>> tid(n+1);
        for(int id:dif)tid[bcj.find(U[id])].push_back(id);
        vector<vector<int>> gv,ge,cyc;
        vector<char> ing(n+1);
        vector<int> vis(n+1),in(n+1),out(n+1),pre(n+1),pe(n+1);
        int tim=0;
        for(int rt=1;rt<=n;++rt)if(!tid[rt].empty()){
            ++tim;
            vector<int> vs;
            int sum=0;
            for(int id:tid[rt]){
                int u=U[id],v=V[id];
                if(vis[u]!=tim)vis[u]=tim,vs.push_back(u),sum+=p[u];
                if(vis[v]!=tim)vis[v]=tim,vs.push_back(v),sum+=p[v];
            }
            if(sum>0){
                for(int v:vs)ing[v]=1;
                gv.push_back(vs),ge.push_back(tid[rt]);
            }
            else{
                for(int v:vs)in[v]=out[v]=0;
                for(int id:tid[rt]){
                    int u=U[id],v=V[id];
                    ++out[u],++in[v];
                    pre[v]=u,pe[v]=id;
                }
                for(int v:vs)if(p[v]||q[v]||in[v]!=1||out[v]!=1)fl=0;
                cyc.push_back(vs);
            }
        }
        if(!fl){
            cout<<"No\n";
            continue;
        }
        vector<char> src(n+1);
        for(int i=1;i<=n;++i)if(ing[i]||p[i]>0)src[i]=1;
        vector<int> dis(n+1,-1),fa(n+1,-1),fe(n+1,-1);
        queue<int> q0;
        for(int i=1;i<=n;++i)if(src[i])dis[i]=0,q0.push(i);
        while (!q0.empty()){
            int x=q0.front();q0.pop();
            for(auto [y,id]:g0[x])if(dis[y]==-1){
                dis[y]=dis[x]+1;
                fa[y]=x;
                fe[y]=id;
                q0.push(y);
            }
        }
        vector<vector<int>> at(n+1);
        vector<char> usev(n+1),usee(m+1);
        for(auto& c:cyc){
            int st=-1;
            for(int v:c)if(dis[v]!=-1&&(st==-1||dis[v]<dis[st]))st=v;
            if(st==-1)fl=0;
            else{
                at[st].push_back(st);
                int x=st;usev[x]=1;
                while (fe[x]!=-1&&!usee[fe[x]]){
                    usee[fe[x]]=1;
                    usev[fa[x]]=1;
                    x=fa[x];
                }
            }
        }
        if(!fl){
            cout<<"No\n";
            continue;
        }
        vector<vector<pair<int,int>>> tr(n+1);
        vector<int> rt;
        for(int v=1;v<=n;++v)if(usev[v]){
            if(fe[v] ==-1)rt.push_back(v);
            else if(usee[fe[v]])tr[fa[v]].push_back({v,fe[v]});
        }
        vector<int> ans;
        ans.reserve(3*m);
        auto solve_cyc=[&](int st){
            int x=st;
            do ans.push_back(pe[x]),x=pre[x];
            while (x!=st);
        };
        auto solve=[&](int r){
            struct node{int x,it,in;bool ent;};
            vector<node> st(1,{r,0,-1,0});
            while (!st.empty()){
                auto &t=st.back();
                if(!t.ent){
                    t.ent=1;
                    for(int v:at[t.x])solve_cyc(v);
                }
                else if(t.it<tr[t.x].size()){
                    auto [y,id]=tr[t.x][t.it++];
                    ans.push_back(id);
                    st.push_back({y,0,id,0});
                }
                else{
                    int id=t.in;
                    st.pop_back();
                    if(id!=-1)ans.push_back(id);
                }
            }
        };
        vector<char> done(n+1);
        auto sol=[&](int v){
            if(src[v]&&!done[v])done[v]=1,solve(v);
        };
        for(int r:rt)if(!ing[r] && !done[r])done[r]=1,solve(r);
        vector<int> pos(n+1,-1);
        for(int t=0;t<gv.size();++t){
            auto &vs=gv[t];
            auto &es=ge[t];
            int sz=vs.size(),S=sz,T=sz+1,N=sz+2,K=0;
            for(int i=0;i<sz;++i)pos[vs[i]]=i;
            for(int v:vs)K+=p[v];
            vector<vector<int>> g(N);
            vector<edge> e;
            auto add=[&](int x,int y,int id){
                e.push_back({x,y,id});
                g[x].push_back(e.size()-1);
            };
            for(int id:es)add(pos[V[id]],pos[U[id]],id);
            for(int v:vs)for(int i=0;i<p[v];++i)add(S,pos[v],0);
            for(int v:vs)for(int i=0;i<q[v];++i)add(pos[v],T,0);
            for(int i=0;i<K;++i)add(T,S,0);
            vector<int> it(N),ord;
            vector<char> used(e.size());
            vector<pair<int,int>> st(1,{S,-1});
            while (!st.empty()){
                int x=st.back().first;
                while(it[x]<g[x].size()&&used[g[x][it[x]]])++it[x];
                if(it[x]==g[x].size()){
                    int id=st.back().second;
                    st.pop_back();
                    if(id!=-1)ord.push_back(id);
                }
                else{
                    int id=g[x][it[x]++];
                    if(used[id])continue;
                    used[id]=1;
                    st.push_back({e[id].v,id});
                }
            }
            reverse(ord.begin(),ord.end());
            for(int id:ord){
                if(!e[id].id){
                    if(e[id].u ==S)sol(vs[e[id].v]);
                }
                else{
                    ans.push_back(e[id].id);
                    sol(vs[e[id].v]);
                }
            }
            for(int v:vs)pos[v]=-1;
        }
        cout<<"Yes\n"<<ans.size()<<'\n';
        for(int no:ans){
            cout<<no<<' ';
        }
        cout<<'\n';
    }
    return 0;
}