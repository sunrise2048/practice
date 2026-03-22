#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int inf=1e9+7;
int T;
int n;
int a[N];
int cn[N];
vector<int> zy[N];
bool ch(int x){
    memset(cn,0,sizeof(int)*(n+1));
    for(int i=1;i<=n;++i)zy[i].clear();
    vector<int> id;
    int tc=0;
    for(int i=1;i<=n;++i){
        for(int to:id){
            if(a[i]-a[to]>=x){
                zy[i].push_back(to);
            }
        }
        id.push_back(i);
        sort(id.begin(),id.end(),[](const int& x,const int& y){
            return a[x]<a[y];
        });
        if(id.size()>3)id.pop_back();
    }
    id.clear();
    for(int i=n;i;--i){
        for(int to:id){
            if(a[to]-a[i]>=x){
                zy[i].push_back(to);
            }
        }
        id.push_back(i);
        sort(id.begin(),id.end(),[](const int& x,const int& y){
            return a[x]>a[y];
        });
        if(id.size()>3)id.pop_back();
    }
    for(int i=1;i<=n;++i){
        if(zy[i].size()<2)continue;
        ++tc;
        cn[i]++;
        if(zy[i].size()==2)cn[zy[i][0]]++,cn[zy[i][1]]++;
    }
    for(int i=1;i<=n;++i){
        if(cn[i]==tc)return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        int l=-inf,r=inf;
        while(l<r-1){
            int mid=l+(r-l)/2;
            if(ch(mid))l=mid;
            else r=mid;
        }
        cout<<l<<'\n';
    }
    return 0;
}