#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int T;
int n,k,q;
int a[N];
vector<pair<int,int>> pt[2];
int cn[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        memset(cn,0,sizeof(cn));
        memset(a,-1,sizeof(a));
        pt[0].clear();pt[1].clear();
        cin>>n>>k>>q;
        for(int i=1;i<=q;++i){
            int op,l,r;
            cin>>op>>l>>r;
            --op;
            pt[op].emplace_back(l,r);
            for(int j=l;j<=r;++j){
                cn[j]|=(1<<op);
            }
        }
        for(int i=1;i<=n;++i){
            if(cn[i]==3)a[i]=k+1;
            else if(cn[i]==0)a[i]=0;
            else if(cn[i]==1)a[i]=k;
        }
        sort(pt[1].begin(),pt[1].end());
        for(auto [l,r]:pt[1]){
            set<int> ts;
            for(int i=0;i<k;++i)ts.insert(i);
            for(int i=l;i<=r;++i){
                if(a[i]!=-1)ts.erase(a[i]);
            }
            for(int i=l;i<=r;++i){
                if(a[i]==-1&&ts.size()){
                    a[i]=*ts.begin();
                    ts.erase(a[i]);
                }
            }
        }
        for(int i=1;i<=n;++i){
            if(a[i]==-1)a[i]=0;
            cout<<a[i]<<' ';
        }cout<<'\n';
    }
    return 0;
}