#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e4+5;
const ll inf=1e10;
int n,l,r;
int a[N];
ll sl[N],sr[N];
ll tl[N],tr[N];
ll b[N];
int main(){
    freopen("plan.in","r",stdin);
    freopen("plan.out","w",stdout);
    scanf("%d%d%d",&n,&l,&r);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    for (int i=1;i<n;++i) {
        sl[i]=l-a[i]-a[i+1];
        sr[i]=r-a[i]-a[i+1];
    }
    tl[1]=0;
    tr[1]=inf;
    for (int i=2;i<=n;++i) {
        tl[i]=max(0ll,sl[i-1]-tr[i-1]);
        tr[i]=sr[i-1]-tl[i-1];
        if (tl[i]>tr[i]) {
            printf("-1\n");
            return 0;
        }
    }
    ll sum=tl[n];
    b[n]=tl[n];
    for (int i=n-1;i;--i) {
        b[i]=max(tl[i],sl[i]-b[i+1]);
        sum+=b[i];
    }
    printf("%lld\n",sum);
    for (int i=1;i<=n;++i) {
        printf("%lld ",a[i]+b[i]);
    }
    return 0;
}