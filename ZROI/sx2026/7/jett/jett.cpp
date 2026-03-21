#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e4+5;
int n,m;
vector<int> e[N],t[N];
bitset<N> bs[N];
int cn;
int d[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;++i){
        cin>>d[i];
        if(d[i]<0)continue;
        ++cn;
        t[d[i]].push_back(i);
        bs[i][i]=1;
    }
    if(cn==0){
        cout<<n<<'\n';
        for(int i=1;i<=n;++i){
            cout<<i<<' ';
        }cout<<'\n';
        return 0;
    }
    queue<int> q,nq;
    for(int nd=n;nd>=0;--nd){
        while(!q.empty()){
            int no=q.front();
            q.pop();
            for(int to:e[no]){
                if(d[to]==-1){
                    d[to]=d[no]-1;
                    bs[to]=bs[no];
                    nq.push(to);
                    continue;
                }
                if(d[to]<d[no]-1){
                    cout<<"0\n";
                    exit(0);
                }
                if(d[to]>=d[no])continue;
                bs[to]|=bs[no];
            }
        }
        for(int no:t[nd]){
            nq.push(no);
        }
        swap(q,nq);
    }
    vector<int> ans;
    for(int i=1;i<=n;++i){
        if(d[i])continue;
        if(bs[i].count()==cn)ans.push_back(i);
    }
    if(ans.empty()){
        cout<<"0\n";
        return 0;
    }
    cout<<ans.size()<<'\n';
    for(int no:ans)cout<<no<<' ';
    cout<<'\n';
    return 0;
}