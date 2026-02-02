#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll inf=(1ll<<31);
int T;
ll x,y;
ll f[31][3][3];
pair<int,int> la[31][3][3];
pair<int,int> ne[31][3][3];
ll dfs(int k,int op0,int op1){
    if(k==-1)return 0;
    if(f[k][op0][op1]<=inf)return f[k][op0][op1];
    ll ans=inf;
    for(int a0:{0,1}){
        for(int a1:{0,1}){
            if(a0&&a1)continue;
            int tp0=op0;
            int tp1=op1;
            ll ts=0;
            if(op0==1){
                if(a0){
                    if((x&(1ll<<k))==0){
                        tp0=2;
                        ts+=(1ll<<k);
                    }
                }
                else{
                    if(x&(1ll<<k)){
                        tp0=0;
                        ts+=(1ll<<k);
                    }
                }
            }
            else if(op0==0)ts+=(x&(1ll<<k))-(1ll<<k)*a0;
            else ts+=(1ll<<k)*a0-(x&(1ll<<k));
            if(op1==1){
                if(a1){
                    if((y&(1ll<<k))==0){
                        tp1=2;
                        ts+=(1ll<<k);
                    }
                }
                else{
                    if(y&(1ll<<k)){
                        tp1=0;
                        ts+=(1ll<<k);
                    }
                }
            }
            else if(op1==0)ts+=(y&(1ll<<k))-(1ll<<k)*a1;
            else ts+=(1ll<<k)*a1-(y&(1ll<<k));
            ts+=dfs(k-1,tp0,tp1);
            if(ans>ts){
                la[k][op0][op1]={a0,a1};
                ne[k][op0][op1]={tp0,tp1};
                ans=ts;
            }
        }
    }
    return f[k][op0][op1]=ans;
}
void find(int k,int op0,int op1,int x,int y){
    if(k==-1){
        cout<<x<<' '<<y<<'\n';
        return;
    }
    x+=la[k][op0][op1].first<<k;
    y+=la[k][op0][op1].second<<k;
    find(k-1,ne[k][op0][op1].first,ne[k][op0][op1].second,x,y);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>x>>y;
        memset(f,0x3f,sizeof(f));
        dfs(30,1,1);
        find(30,1,1,0,0);
    }
    return 0;
}