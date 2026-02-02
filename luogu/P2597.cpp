#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
vector<int> e[N],fe[N];
int idom[N],sdom[N];
int dfn[N],cn;
int nfd[N];
int tf[N],mi[N];
int fa[N];
vector<int> ts[N];
void dfs(int no){
    dfn[no]=++cn;
    nfd[cn]=no;
    for(int to:e[no]){
        if(dfn[to])continue;
        tf[to]=no;
        dfs(to);
    }
}
int find(int x){
    if(fa[x]==x)return x;
    int lf=fa[x];
    fa[x]=find(fa[x]);
    if(dfn[sdom[mi[lf]]]<dfn[sdom[mi[x]]])mi[x]=mi[lf];
    return fa[x];
}
int si[N];
void get_idom(){
    dfs(1);
    iota(sdom+1,sdom+n+2,1);
    iota(fa+1,fa+n+2,1);
    iota(mi+1,mi+n+2,1);
    for(int i=n+1;i;--i){
        int no=nfd[i];
        for(int s:ts[no]){
            find(s);
            if(sdom[mi[s]]==no)idom[s]=no;
            else idom[s]=mi[s];
        }
        if(i==1)break;
        for(int la:fe[no]){
            if(dfn[la]<dfn[sdom[no]])sdom[no]=la;
            else if(dfn[la]>dfn[no]){
                find(la);
                if(dfn[sdom[mi[la]]]<dfn[sdom[no]])sdom[no]=sdom[mi[la]];
            }
        }
        ts[sdom[no]].push_back(no);
        fa[no]=tf[no];
    }
    for(int i=2;i<=n+1;++i){
        int no=nfd[i];
        if(idom[no]!=sdom[no])idom[no]=idom[idom[no]];
    }
    for(int i=n+1;i;--i){
        int no=nfd[i];
        si[no]++;
        if(i!=1)si[idom[no]]+=si[no];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=2;i<=n+1;++i){
        int la;
        cin>>la;
        while(la){
            e[la+1].push_back(i);
            fe[i].push_back(la+1);
            cin>>la;
        }
        if(fe[i].empty()){
            e[1].push_back(i);
            fe[i].push_back(1);
        }
    }
    get_idom();
    for(int i=2;i<=n+1;++i){
        cout<<si[i]-1<<'\n';
    }
    return 0;
}