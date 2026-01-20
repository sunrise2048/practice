#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int K=4;
const int inf=1e9;
int n,k;
struct squ{
    int xl,xr;
    int yl,yr;
    squ()=default;
    squ(int xl,int xr,int yl,int yr):xl(xl),xr(xr),yl(yl),yr(yr){}
};
squ a[N];
squ id[K];
mt19937 mt(time(0));
bool ch(squ& x,squ& y){
    return max(x.xl,y.xl)<=min(x.xr,y.xr)&&max(x.yl,y.yl)<=min(x.yr,y.yr);
}
void get_squ(squ& x,squ y){
    x.xl=max(x.xl,y.xl);
    x.xr=min(x.xr,y.xr);
    x.yl=max(x.yl,y.yl);
    x.yr=min(x.yr,y.yr);
}
void solve(){
    while(true){
        for(int j=0;j<k;++j){
            id[j]=squ(1,inf,1,inf);
        }
        bool as=1;
        for(int i=1;i<=n;++i){
            int fl=-1;
            for(int j=0;j<k;++j){
                if(ch(id[j],a[i])){
                    fl=j;
                    break;
                }
            }
            if(fl==-1){
                swap(a[i],a[mt()%i+1]);
                as=0;
                break;
            }
            get_squ(id[fl],a[i]);
        }
        if(!as)continue;
        for(int i=0;i<k;++i){
            cout<<id[i].xl<<' '<<id[i].yl<<'\n';
        }
        return;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i].xl>>a[i].yl>>a[i].xr>>a[i].yr;
    }
    shuffle(a+1,a+n+1,mt);
    solve();
    return 0;
}