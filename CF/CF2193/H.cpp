#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
int si[N];
int p[N];
int op[N];
vector<int> e[N];
bool dfs(int no,int fa){
    for(int to:e[no]){
        if(to==fa)continue;
        if(!dfs(to,no))return 0;
    }
    op[no]=1;
    si[no]^=a[fa];
    if(!p[no]&&si[no]==a[no]){
        if(a[fa]){
            op[no]=0;
            si[no]^=a[fa];
            si[fa]^=a[no];
            return 1;
        }
        return 0;
    }
    if(a[no]&&(p[no]||!a[fa])){
        p[fa]=no;
    }
    return 1;
}
vector<int> ve;
void dfs1(int no,int fa){
    if(si[no]==a[no]){
        op[p[no]]=0;
        si[p[no]]^=a[no];
    }
    for(int to:e[no]){
        if(to==fa)continue;
        if(op[to])dfs1(to,no);
    }
    ve.push_back(no);
    for(int to:e[no]){
        if(to==fa)continue;
        if(!op[to])dfs1(to,no);
    }
}
void solve(){
    if(!dfs(1,0)){
        cout<<"NO\n";
        return;
    }
    ve.clear();
    dfs1(1,0);
    cout<<"YES\n";
    for(int no:ve)cout<<no<<' ';
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            e[i].clear();
            si[i]=0;
            op[i]=0;
            p[i]=0;
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
            a[i]&=1;
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        solve();
    }
    return 0;
}