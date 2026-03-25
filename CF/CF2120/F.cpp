#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=305;
int T;
int n,k,m;
bitset<N> bs[N],ls;
vector<int> e[N<<1];
int low[N<<1],dfn[N<<1];
int scc[N<<1],scn,cn;
stack<int> st;
void tarjan(int no){
    st.push(no);
    dfn[no]=low[no]=++cn;
    for(int to:e[no]){
        if(!dfn[to]){
            tarjan(to);
            low[no]=min(low[no],low[to]);
        }
        else if(!scc[to])low[no]=min(low[no],dfn[to]);
    }
    if(low[no]==dfn[no]){
        ++scn;
        while(!st.empty()&&dfn[st.top()]>=dfn[no]){
            scc[st.top()]=scn;
            st.pop();
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        scn=cn=0;
        while(!st.empty())st.pop();
        for(int i=1;i<=(n<<1);++i){
            e[i].clear();
            low[i]=dfn[i]=0;
            scc[i]=0;
        }
        while(k--){
            cin>>m;
            for(int i=1;i<=n;++i)bs[i].reset();
            for(int i=1;i<=m;++i){
                int u,v;
                cin>>u>>v;
                bs[u][v]=bs[v][u]=1;
            }
            for(int i=1;i<=n;++i){
                for(int j=i+1;j<=n;++j){
                    ls=bs[i]^bs[j];
                    if(bs[i][j])ls[i]=ls[j]=0;
                    if(ls.any())continue;
                    if(bs[i][j]){
                        e[i].push_back(j+n);e[j].push_back(i+n);
                    }
                    else{
                        e[i+n].push_back(j);e[j+n].push_back(i);
                    }
                }
            }
        }
        for(int i=1;i<=(n<<1);++i){
            if(dfn[i])continue;
            tarjan(i);
        }
        bool fl=1;
        for(int i=1;i<=n;++i){
            if(scc[i]==scc[i+n]){
                fl=0;
                break;
            }
        }
        if(fl)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}