#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e7+5;
int T;
int n,m;
bool isp[N];
vector<int> pr;
int mi[N];
void init(){
    const int n=1e7;
    for(int i=2;i<=n;++i){
        if(!isp[i]){
            pr.push_back(i);
            mi[i]=i;
        }
        for(int p:pr){
            if(i*p>n)break;
            isp[i*p]=1;
            mi[i*p]=p;
            if(i%p==0)break;
        }
    }
}
int calc(int x,int p){
    int s=0;
    ll bs=p;
    while(bs<=x){
        s+=x/bs;
        bs*=p;
    }
    return s;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n>>m;
        int lp=n;
        while(lp!=1&&isp[lp])--lp;
        vector<int> np;
        for(int x=lp+1;x<=n;++x){
            int y=x;
            while(y!=1){
                np.push_back(mi[y]);
                int mp=mi[y];
                while(y%mp==0)y/=mp;
            }
        }
        sort(np.begin(),np.end());
        np.erase(unique(np.begin(),np.end()),np.end());
        ll ans=0;
        for(int x=lp;x<n;++x){
            int mi=1e9+7;
            for(int p:np){
                int cx=calc(x,p),cn=calc(n,p);
                ll tp=p;
                int ct=1;
                while(tp<=m){
                    if(cx/ct!=cn/ct)mi=min(mi,cx/ct);
                    tp*=p;
                    ++ct;
                }
            }
            ans+=mi;
        }
        cout<<ans<<'\n';
    }
    return 0;
}