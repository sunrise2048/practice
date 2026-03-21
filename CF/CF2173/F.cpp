#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1.5e5+5;
const int lim=400;
int T;
int n,q;
int a[N];
ll s[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        while(q--){
            int no,r,x;
            cin>>no>>r>>x;
            int cn=0;
            --no;
            for(int i=1;i<=lim;++i){
                if(no+i>r)break;
                if(s[no+i]-s[no]<x)continue;
                int el=1,er=(r-no)/i+1;
                while(el<er-1){
                    int mid=(el+er)>>1;
                    if(s[no+mid*i]-s[no+(mid-1)*i]>=x)el=mid;
                    else er=mid;
                }
                cn+=el;
                no+=el*i;
            }
            while(s[r]-s[no]>=x){
                int ne=lower_bound(s+1,s+n+1,s[no]+x)-s;
                ++cn;
                no=ne;
            }
            cout<<cn<<' '<<s[r]-s[no]<<'\n';
        }
    }
    return 0;
}