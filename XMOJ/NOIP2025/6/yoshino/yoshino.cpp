#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
struct line{
    int x,yl,yr;
}le[N];
bool ch(){
    for(int i=1;i<=n;++i){
        if(le[i].x)return 0;
    }
    return 1;
}
class SOL{
public:
    void sol(){
        sort(le+1,le+n+1,[](const line& x,const line& y){
            return x.yl<y.yl;
        });
        double ans=0;
        for(int i=1;i<=n;++i){
            int j=i;
            ll ty=le[i].yr;
            while(j!=n&&le[j+1].yl<=ty){
                ty=max(ty,(ll)le[j+1].yr);
                ++j;
            }
            ans+=1.0*(ty-le[i].yl)*(ty-le[i].yl)/2;
            i=j;
        }
        printf("%.2f\n",ans);
    }
}sol;
int main(){
    freopen("yoshino.in","r",stdin);
    freopen("yoshino.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d%d%d",&le[i].x,&le[i].yl,&le[i].yr);
    }
    if(true){
        sol.sol();
    }
    return 0;
}