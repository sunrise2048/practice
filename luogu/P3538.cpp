#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=5e5+5;
const ull bas=19260817;
int n;
ull ha[N],mi[N];
bool isp[N];
int mip[N];
vector<int> p;
ull get_ha(int l,int r){
    return ha[r]-ha[l-1]*mi[r-l+1];
}
bool ch(int g,int l,int r){
    return get_ha(l,r-g)==get_ha(l+g,r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        char c;
        cin>>c;
        ha[i]=ha[i-1]*bas+c;
    }
    mi[0]=1;
    for(int i=1;i<=n;++i)mi[i]=mi[i-1]*bas;
    mip[1]=1;
    for(int i=2;i<=n;++i){
        if(!isp[i]){
            p.push_back(i);
            mip[i]=i;
        }
        for(int pr:p){
            if(pr*i>n)break;
            mip[i*pr]=pr;
            isp[i*pr]=1;
            if(i%pr==0)break;
        }
    }
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int nl=y-x+1;
        int ans=nl;
        while(nl!=1){w
            int np=mip[nl];
            while(nl%np==0)nl/=np;
            while(ans%np==0&&ch(ans/np,x,y))ans/=np;
        }
        cout<<ans<<'\n';
    }
    return 0;
}