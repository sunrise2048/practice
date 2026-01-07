#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,m,k;
vector<int> e[N];
int d[N];
bool fl[N];
bool ch(int no){
    if(1ll*k*(k-1)/2>m)return 0;
    int cn=0;
    for(int i=0;i<e[no].size();++i){
        int to=e[no][i];
        if(!fl[to]){
            e[no][cn++]=to;
        }
    }
    e[no].resize(cn);
    for(int nd:e[no]){
        if(fl[nd])continue;
        auto it=lower_bound(e[nd].begin(),e[nd].end(),no);
        if(it==e[nd].end()||(*it)!=no)return 0;
        it=e[nd].begin();
        for(int to:e[no]){
            if(to==nd)continue;
            it=lower_bound(it,e[nd].end(),to);
            if(it==e[nd].end()||(*it)!=to)return 0;
        }
    }
    return 1;
}
bool solve(){
    fill(fl+1,fl+n+1,0);
    for(int i=1;i<=n;++i){
        sort(e[i].begin(),e[i].end());
    }
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(d[i]<k)q.push(i);
    }
    while(!q.empty()){
        int no=q.front();
        q.pop();
        if(d[no]==k-1){
            if(ch(no)){
                cout<<2<<'\n';
                cout<<no<<' ';
                for(int to:e[no]){
                    if(fl[to])continue;
                    cout<<to<<' ';
                }cout<<'\n';
                return 1;
            }
        }
        fl[no]=1;
        for(int to:e[no]){
            if(fl[to])continue;
            d[to]--;
            --m;
            if(d[to]==k-1){
                q.push(to);
            }
        }
    }
    int cn=0;
    for(int i=1;i<=n;++i){
        if(fl[i])continue;
        ++cn;
    }
    if(cn){
        cout<<1<<' '<<cn<<'\n';
        for(int i=1;i<=n;++i){
            if(fl[i])continue;
            cout<<i<<' ';
        }
        cout<<'\n';
        return 1;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=n;++i){
            e[i].clear();
            d[i]=0;
        }
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
            d[u]++;d[v]++;
        }
        if(!solve()){
            cout<<"-1\n";
        }
    }
    return 0;
}