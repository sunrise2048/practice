#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=15;
int n;
pair<int,int> nx[N],ny[N];
int xl[N],yl[N];
int get_val(pair<int,int> nd){
    if(nd.second==0)return nd.first;
    else if(nd.first==n)return n+nd.second;
    else if(nd.second==n)return 2*n+n-nd.first;
    else if(nd.first==0)return 3*n+n-nd.second;
    return -1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>nx[i].first>>nx[i].second>>ny[i].first>>ny[i].second;
        xl[i]=get_val(nx[i]);yl[i]=get_val(ny[i]);
        if(xl[i]>yl[i])swap(xl[i],yl[i]);
    }
    bool fl=1;
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
            if(xl[i]==-1||yl[i]==-1||xl[j]==-1||yl[j]==-1)continue;
            if(xl[i]<xl[j]&&xl[j]<yl[i]&&yl[i]<yl[j])fl=0;
            if(xl[j]<xl[i]&&xl[i]<yl[j]&&yl[j]<yl[i])fl=0;
        }
    }
    if(fl)cout<<"YES\n";
    else cout<<"NO\n";
    return 0;
}