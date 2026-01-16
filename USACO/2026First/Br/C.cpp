#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,k;
int q;
ll s[505][505];
ll vl[505][505];
ll ans;
int main(){
    cin>>n>>k;
    cin>>q;
    while(q--){
        int x,y,d;
        cin>>x>>y>>d;
        d-=vl[x][y];
        vl[x][y]+=d;
        for(int i=-k+1;i<=0;++i){
            if(i+x<0)continue;
            for(int j=-k+1;j<=0;++j){
                if(j+y<0)continue;
                s[x+i][y+j]+=d;
                ans=max(ans,s[x+i][y+j]);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}