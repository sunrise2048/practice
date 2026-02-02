#include<bits/stdc++.h>
using namespace std;
using ll=unsigned long long;
using I128=__int128;
const int N=1e6+5;
int T;
int n,k;
ll a[N];
int m;
I128 b[N];
ll tg;
pair<int,ll> st[N];
int str;
ll g[N];
I128 s[N];
I128 ans;
void prt(I128 no){
    if(!no)return;
    prt(no/10);
    cout<<(int)(no%10);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>a[1]>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        {
            int ln=n;
            n=m=0;
            ll la=0;
            for(int i=1;i<=ln;++i){
                if(a[i]!=la){
                    a[++n]=a[i];
                    la=a[i];
                }
                else b[++m]=a[i];
            }
        }
        for(int i=1;i<=n;++i){
            g[i]=__gcd(g[i-1],a[i]);
        }
        for(int i=1;i<=m;++i)b[i]+=b[i-1];
        for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
        int no=1;
        ans=0;
        str=0;
        tg=0;
        for(int i=1;i<=n;++i){
            if(i>k+1)break;
            if(tg!=g[i-1]){
                no=1;
                str=0;
                tg=g[i-1];
            }
            if(k+1-i>m)continue;
            if(str==0){
                for(int j=i;j<=n;++j){
                    ll ng=a[j]-__gcd(a[j],tg);
                    while(str&&st[str].second>=ng)--str;
                    st[++str]={j,ng};
                }
            }
            while(st[no].first<i)++no;
            ans=max(ans,s[n]-s[i-1]-st[no].second+b[m]-b[k+1-i]);
        }
        if(!ans){
            cout<<"0\n";
            continue;
        }
        prt(ans);
        cout<<'\n';
    }
    return 0;
}