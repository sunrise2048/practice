#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int n,m;
int a[N];
int c[N<<1];

int chk(int x,int mid) {
    for(int i=1;i<=n;i++) {
        c[i]=c[i+n]=a[i]>>x&1;
    }
    int c1=0,c2=0;
    for(int i=1;i<=n<<1;i++) {
        if(c[i]) c2++;
        else {
            if(c2<mid) {
                if(c2!=i) c1+=c2;
                c2=0;
            }
            else {
                c1=c2=0;
            }
            c1++;
            if(c1>2) return 0;
        }
    }
    return 1;
}

int solve(int x) {
    int L=2,R=n,mid,res=1;
    while(L<=R) {
        mid=L+R>>1;
        if(chk(x,mid)) res=mid,L=mid+1;
        else R=mid-1;
    }
    return res;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    // printf("%d\n",chk(2,2));
    // return 0;
    int ans=n;
    for(int i=0;i<m;i++) ans=min(ans,solve(i));
    printf("%d",ans);
    return 0;
}