#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
vector<int> e[N];
int dg[N];
int d[N];
int t[N];
int mxs[N];
int fa[N];
int dfn[N],cn_dfn;
void dfs(int no,int fa){
    d[no]=d[fa]+1;
    t[d[no]]++;
    ::fa[no]=fa;
    dfn[no]=++cn_dfn;
    mxs[d[no]]=max(mxs[d[no]],(int)(e[no].size()-(no!=1)));
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);dg[no]++;
    }
}
bool fl[N];
bool vis[N];
bool flc[N];
set<pair<int,int>> st[N];
vector<int> xzd[N],xzc[N];
struct node{
    int d;
    int op;
    int id;
    node()=default;
    node(int d,int op,int id):d(d),op(op),id(id){}
};
void era(int no){
    flc[d[no]]=1;
    t[d[no]]--;
    fl[no]=1;
    for(int to:e[no])vis[to]=1;
    st[d[no]].erase({dfn[no],no});
    dg[fa[no]]--;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        cn_dfn=0;
        for(int i=1;i<=n;++i){
            st[i].clear();
            e[i].clear();
            d[i]=t[i]=mxs[i]=0;
            dg[i]=0;
            vis[i]=0;
            fl[i]=0;
            flc[i]=0;
            xzd[i].clear();
            xzc[i].clear();
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        int mx=0;
        for(int i=1;i<=n;++i){
            st[d[i]].emplace(dfn[i],i);
        }
        for(int i=1;i<=n;++i)mx=max(mx,t[i]);
        for(int i=1;i<=n;++i){
            if(t[i+1]==mx&&mxs[i]==mx){
                ++mx;
                break;
            }
        }
        cout<<mx<<'\n';
        for(int i=1;i<=n;++i){
            xzc[t[i]].push_back(i);
            xzd[dg[i]+1].push_back(i);
        }
        for(int bs=mx;bs;--bs){
            vector<node> ve;
            for(int no:xzc[bs]){
                if(t[no]!=bs){
                    xzc[t[no]].push_back(no);
                    continue;
                }
                ve.emplace_back(no,0,no);
            }
            for(int no:xzd[bs]){
                if(fl[no])continue;
                if(dg[no]+1!=bs){
                    xzd[dg[no]+1].push_back(no);
                    continue;
                }
                ve.emplace_back(d[no],1,no);
            }
            sort(ve.begin(),ve.end(),[](const node& x,const node& y){
                return x.d!=y.d?x.d<y.d:x.op>y.op;
            });
            vector<int> id;
            for(node nd:ve){
                if(nd.op){
                    if(fl[nd.id])continue;
                    if(!vis[nd.id]&&!flc[nd.d]){
                        id.push_back(nd.id);
                        era(nd.id);
                    }
                    else{
                        auto it=st[nd.d+1].lower_bound({dfn[nd.id],0})->second;
                        id.push_back(it);
                        era(it);
                    }
                }
                else{
                    if(flc[nd.d])continue;
                    auto it=st[nd.d].begin()->second;
                    if(vis[it])it=st[nd.d].rbegin()->second;
                    id.push_back(it);
                    era(it);
                }
            }
            cout<<id.size()<<' ';
            for(int no:id)cout<<no<<' ';
            cout<<'\n';
            for(int no:id){
                flc[d[no]]=0;
                for(int to:e[no])vis[to]=0;
            }
            for(node nd:ve){
                if(nd.op){
                    if(fl[nd.id])continue;
                    xzd[dg[nd.id]+1].push_back(nd.id);
                }
                else{
                    xzc[t[nd.d]].push_back(nd.d);
                }
            }
        }
    }
    return 0;
}