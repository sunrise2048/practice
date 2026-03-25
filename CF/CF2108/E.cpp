#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
vector<int> e[N];
int si[N];
ll sf[N],sg[N];
ll mx;
pair<int,int> se;
void dfs1(int no,int fa){
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
        si[no]+=si[to];
        sf[no]+=sf[to];
    }
    sf[no]+=min(si[no],n-1-si[no]);
}
void dfs2(int no,int fa){
    for(int to:e[no]){
        if(to==fa)continue;
        sg[to]=sg[no]+sf[no]-sf[to]-min(si[no],n-1-si[no])+min(n-si[to],si[to]-1);
        ll ns=sf[to]+sg[to]-min(n-si[to],si[to]-1)-min(si[to],n-1-si[to]);
        if(ns>mx){
            mx=ns;se={no,to};
        }
        dfs2(to,no);
    }
}
int c[N];
int rt;
int mxs[N];
int nc;
void dfs3(int no,int fa){
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs3(to,no);
        si[no]+=si[to];
        mxs[no]=max(mxs[no],si[to]);
    }
    mxs[no]=max(mxs[no],n-1-si[no]);
    if(mxs[rt]>mxs[no])rt=no;
}
void dfs4(int no,int fa){
    c[no]=nc;
    nc=nc%((n-1)/2)+1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs4(to,no);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        mx=-1;se={0,0};
        for(int i=1;i<=n;++i){
            e[i].clear();
            sf[i]=sg[i]=0;
            c[i]=0;
            mxs[i]=0;
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs1(1,0);
        dfs2(1,0);
        if(se.first>se.second)swap(se.first,se.second);
        for(int i=1;i<=n;++i){
            if(i==se.second)continue;
            vector<int> ne;
            for(int to:e[i]){
                if(to==se.second){
                    if(i==se.first)continue;
                    to=se.first;
                    ne.push_back(to);
                    e[to].push_back(i);
                    continue;
                }
                ne.push_back(to);
            }
            swap(ne,e[i]);
        }
        rt=0;mxs[0]=n+1;
        dfs3(se.first,0);
        nc=1;
        dfs4(rt,0);
        cout<<se.first<<' '<<se.second<<'\n';
        for(int i=1;i<=n;++i)cout<<c[i]<<' ';
        cout<<'\n';
    }
    return 0;
}