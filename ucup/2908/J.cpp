#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n,m,k;
vector<pair<int,int>> e[N];
struct trie{
    int len;
    int s[8];
    vector<int> id;
}t[N<<3];
int cn;
int ans[N];
int ct;
void dfs(int no){
    if(ct==k)return;
    for(int i=0;i<8;++i){
        if(ct==k)return;
        for(int ti=0;ti<t[no].id.size();++ti){
            int id=t[no].id[ti];
            for(auto [tc,to]:e[id]){
                if(tc>i)break;
                if(tc!=i)continue;
                if(!t[no].s[i]){
                    t[no].s[i]=++cn;
                    t[cn].len=t[no].len+1;
                }
                ans[++ct]=t[no].len+1;
                if(ct==k)return;
                t[t[no].s[i]].id.push_back(to);
            }
        }
        if(t[no].s[i])dfs(t[no].s[i]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    memset(ans,-1,sizeof(int)*(k+1));
    for(int i=1;i<=m;++i){
        int u,v,c;
        cin>>u>>v>>c;
        --c;
        e[u].emplace_back(c,v);
    }
    for(int i=1;i<=n;++i){
        sort(e[i].begin(),e[i].end());
    }
    for(int i=1;i<=n;++i)t[0].id.push_back(i);
    dfs(0);
    for(int i=1;i<=k;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}