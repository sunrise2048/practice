#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,m,k;
vector<ll> a[N],mx[N];
vector<ll> vb;
ll sm[N];
bool fl[N];
int id[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        a[i].resize(m);
        bool fl=0;
        for(int j=0;j<m;++j){
            cin>>a[i][j];
            if(j&&a[i][j-1]<a[i][j]){
                fl=1;
            }
        }
        if(!fl){
            for(int j=0;j<m;++j){
                vb.push_back(a[i][j]);
            }
            a[i].clear();
        }
    }
    sort(vb.begin(),vb.end());
    for(int i=1;i<=n;++i){
        mx[i].resize(m);
        if(a[i].empty()){
            fl[i]=1;
            while(a[i].size()<m){
                a[i].push_back(vb.back());
                vb.pop_back();
            }
        }
        for(int j=1;j<m;++j){
            a[i][j]+=a[i][j-1];
        }
    }
    iota(id+1,id+n+1,1);
    sort(id+1,id+n+1,[](const int& x,const int& y){
        return a[x].back()>a[y].back();
    });
    mx[n+1].resize(m);
    for(int i=n;i;--i){
        int x=id[i];
        for(int j=0;j<m;++j){
            mx[i][j]=max(mx[i+1][j],a[x][j]);
        }
    }
    for(int i=1;i<=n;++i){
        sm[i]=sm[i-1]+a[id[i]].back();
    }
    ll ans=0;
    for(int i=1;i<=n;++i){
        int x=id[i];
        for(int j=1;j<=m;++j){
            if(j>k)continue;
            ll ns=a[x][j-1];
            int cn=(k-j)/m;
            int ys=(k-j)%m;
            int t=n+1;
            if(cn<i){
                ns+=sm[cn];
                if(ys)ns+=mx[i+1][ys-1];
            }
            else{
                ns+=sm[cn+1]-a[x].back();
                if(ys)ns+=mx[cn+2][ys-1];
            }
            ans=max(ans,ns);
        }
    }
    cout<<ans<<'\n';
    return 0;
}