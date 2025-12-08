#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m,k;
pair<ll,int> a[N],b[N];
ll f[N][3][2];
pair<int,int> las[N][3][2];
void zy(int id0,int id1,int top,ll val,int lid,int lop){
    if(abs(id0-id1)>1)return;
    int ti=min(id0,id1);
    int tl=1;
    if(id0>id1)tl=0;
    else if(id0<id1)tl=2;
    if(f[ti][tl][top]<=val)return;
    f[ti][tl][top]=val;
    las[ti][tl][top]={lid,lop};
}
void gz(int i,int tp,int op){
    if(i==0&&tp==1)return;
    auto [lp,lop]=las[i][tp][op];
    int id0=i+(tp==0);
    int id1=i+(tp==2);
    if(lp==0){
        int li0=id0-1,li1=id1;
        int ti=min(li0,li1);
        int lpp=1;
        if(li0>li1)lpp=0;
        else if(li0<li1)lpp=1;
        gz(ti,lpp,lop);
        if(id0<=n)cout<<f[i][tp][op]-k<<' '<<0<<' '<<a[id0].second<<'\n';
    }
    else{
        int li0=id0,li1=id1-1;
        int ti=min(li0,li1);
        int lpp=1;
        if(li0>li1)lpp=0;
        else if(li0<li1)lpp=1;
        gz(ti,lpp,lop);
        if(id1<=m)cout<<f[i][tp][op]-k<<' '<<1<<' '<<b[id1].second<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i].first;
        a[i].second=i;
    }
    for(int i=1;i<=m;++i){
        cin>>b[i].first;
        b[i].second=i;
    }
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    memset(f,0x3f,sizeof(f));
    f[0][1][0]=f[0][1][1]=0;
    for(int i=0;i<=max(n,m);++i){
        for(int d:{1,0,2}){
            for(int op:{0,1}){
                int id0=i+(d==0);
                int id1=i+(d==2);
                if(id0>=n){
                    zy(id0+1,id1,op,f[i][d][op],0,op);
                }
                else{
                    ll ti=f[i][d][op];
                    if(op==1)ti=max(ti+k,a[id0+1].first);
                    else ti=max(ti,a[id0+1].first);
                    ti+=k;
                    zy(id0+1,id1,1,ti,0,op);
                }
                if(id1>=m){
                    zy(id0,id1+1,op,f[i][d][op],1,op);
                }
                else{
                    ll ti=f[i][d][op];
                    if(op==0)ti=max(ti+k,b[id1+1].first);
                    else ti=max(ti,b[id1+1].first);
                    ti+=k;
                    zy(id0,id1+1,0,ti,1,op);
                }
            }
        }
    }
    if(f[max(n,m)][1][0]<=f[max(n,m)][1][1]){
        cout<<f[max(n,m)][1][0]<<'\n';
        gz(max(n,m),1,0);
    }
    else{
        cout<<f[max(n,m)][1][1]<<'\n';
        gz(max(n,m),1,1);
    }
    return 0;
}