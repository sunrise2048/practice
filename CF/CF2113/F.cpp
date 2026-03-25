#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N],b[N];
set<pair<int,int>> e[N];
int d[N];
int c[2][N];
void dfs(int no){
    if(e[no].empty())return;
    auto [to,id]=*e[no].begin();e[no].erase(e[no].begin());
    d[no]--;d[to]--;
    c[0][id]=no;c[1][id]=to;
    e[to].erase({no,id});
    dfs(to);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=(n<<1);++i){
            d[i]=0;
            e[i].clear();
        }
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        for(int i=1;i<=n;++i){
            if(a[i]==b[i]){
                c[0][i]=c[1][i]=a[i];
            }
            else{
                e[a[i]].emplace(b[i],i);
                e[b[i]].emplace(a[i],i);
            }
            ++d[a[i]];++d[b[i]];
        }
        int cn=0;
        for(int i=1;i<=2*n;++i)cn+=min(2,d[i]);
        for(int i=1;i<=2*n;++i){
            if(d[i]&1){
                dfs(i);
            }
        }
        for(int i=1;i<=2*n;++i){
            while(!e[i].empty())dfs(i);
        }
        cout<<cn<<'\n';
        for(int i=1;i<=n;++i)cout<<c[0][i]<<' ';
        cout<<'\n';
        for(int i=1;i<=n;++i)cout<<c[1][i]<<' ';
        cout<<'\n';
    }
    return 0;
}