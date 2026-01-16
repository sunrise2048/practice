#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
int n,m;
int d[N];
int id[N];
bool fl[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            char c;
            cin>>c;
            if(c=='1')d[i]++,d[j]--;
        }
    }
    iota(id+1,id+n+1,1);
    sort(id+1,id+n+1,[](const int& x,const int& y){
        return d[x]<d[y];
    });
    while(m--){
        memset(fl,0,sizeof(fl));
        int t;
        cin>>t;
        fl[t]=1;
        int sum=0;
        int si;
        cin>>si;
        for(int i=1;i<=si;++i){
            int s;
            cin>>s;
            fl[s]=1;
            sum+=d[s];
        }
        int ans=si*(n-si)+sum;
        for(int i=1;i<=n;++i){
            int no=id[i];
            if(fl[no])continue;
            ++si;
            sum+=d[no];
            ans=min(ans,si*(n-si)+sum);
        }
        cout<<ans/2<<'\n';
    }
    return 0;
}