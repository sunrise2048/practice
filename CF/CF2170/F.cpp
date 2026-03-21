#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
const int M=1e6+5;
const int K=12;
int n,q;
int a[N];
int f[1<<K][K+1];
struct ques{
    int r,x,id;
};
vector<ques> qs[N];
int ans[M];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    cin>>q;
    for(int i=1;i<=q;++i){
        int l,r,x;
        cin>>l>>r>>x;
        qs[l].push_back({r,x,i});
    }
    for(int l=n;l;--l){
        for(int i=0;i<(1<<K);++i){
            for(int j=0;j<K;++j){
                f[i^a[l]][j+1]=min(f[i^a[l]][j+1],max(f[i][j],l));
            }
        }
        for(auto [r,x,id]:qs[l]){
            int as=0;
            for(int i=0;i<=K;++i){
                if(f[x][i]<=r){
                    as=i;
                    break;
                }
            }
            ans[id]=as;
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<' ';
    }
    return 0;
}