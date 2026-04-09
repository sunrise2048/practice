#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
int n;
int a[N];
int b[N];
int c[N];
vector<pair<int,int>> ve;
void ope(int l,int r){
    if(l==r)return;
    for(int i=1;i<=r-l+1;++i)c[i]=b[i+l-1];
    int mid=(r-l+1)/2;
    ve.emplace_back(l,r);
    for(int i=1;i<=r-l+1;++i){
        if(i<=mid)b[l+2*i-1]=c[i];
        else b[l+2*(i-mid)-2]=c[i];
    }
}
void shuff(){
    mt19937 mt(time(0));
    int T=100;
    while(T--){
        int l=mt()%n+1,r=mt()%n+1;
        if(l>r)swap(l,r);
        if(mt()%20==0)l=1;
        else if(mt()%20==0)r=n;
        ope(l,r);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    iota(b+1,b+n+1,1);
    shuff();
    for(int i=n;i;--i){
        int x=1;
        while(b[x]!=a[i])++x;
        while(2*x<=i){
            ope(1,i);
            x*=2;
        }
        if(i!=x)ope(x-(i-x)+1,i);
    }
    reverse(ve.begin(),ve.end());
    cout<<ve.size()<<'\n';
    for(auto [l,r]:ve){
        cout<<l<<' '<<r<<'\n';
    }
    return 0;
}