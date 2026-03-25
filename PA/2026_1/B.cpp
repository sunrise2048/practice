#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n;
vector<int> las[N],cnt[N];
int ans;
int bs[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        int cn;
        cin>>cn;
        if(i==1){
            cnt[i].resize(cn);
            continue;
        }
        cnt[i].resize(cn);las[i].resize(cn);
        for(int j=0;j<cn;++j){
            cin>>las[i][j];
            --las[i][j];
        }
    }
    for(int i=n;i;--i){
        for(int j=0;j<cnt[i].size();++j){
            if(bs[i]&&cnt[i][j]==0){
                --bs[i];
            }
            cnt[i][j]=max(cnt[i][j],1);
            if(i>1&&las[i][j]>=0){
                cnt[i-1][las[i][j]]+=cnt[i][j];
            }
            else bs[i-1]+=cnt[i][j];
        }
        bs[i-1]+=bs[i];
    }
    ans=bs[1];
    for(int i=0;i<cnt[1].size();++i)ans+=cnt[1][i];
    cout<<ans<<'\n';
    return 0;
}