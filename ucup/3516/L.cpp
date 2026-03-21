#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+5;
int T;
int n;
ll k;
vector<int> e[N];
vector<int> t[2];
int op[N];
void dfs(int no,int fa,int d){
    t[d].push_back(no);
    op[no]=d;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no,d^1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        n*=2;
        for(int i=1;i<=n;++i)e[i].clear();
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        t[0].clear();
        t[1].clear();
        dfs(1,0,0);
        if((k&1)!=(t[1].size()&1)){
            cout<<1<<' '<<e[1].back()<<'\n';
            cout<<1<<' '<<e[1].back()<<'\n';
            continue;
        }
        for(int i=2;i<=n;++i){
            if(e[i].size()>1)continue;
            if(t[op[i]].size()==1)continue;
            int fa=e[i][0];
            cout<<i<<' '<<fa<<'\n';
            int to;
            for(int x:t[op[i]]){
                if(x==i)continue;
                to=x;
                break;
            }
            cout<<i<<' '<<to<<'\n';
            break;
        }
    }
    return 0;
}