#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int T;
int n;
int s[4];
int a[N][N];
int sm[N][N];
int mif[N][N],mxf[N][N];
pair<int,int> pp[N][N],ps[N][N],sp[N][N],ss[N][N];
void cj(pair<int,int>& x,pair<int,int> y){
    x.first=max(x.first,y.first);
    x.second=min(x.second,y.second);
}
void cl(){
    for(int i=0;i<=n+1;++i){
        memset(mif[i],0,sizeof(int)*(n+2));
        memset(mxf[i],0,sizeof(int)*(n+2));
    }
}
void solve(){
    if(sm[n][n]!=s[0]+s[1]+s[2]+s[3]){
        cout<<"NIE\n";
        return;
    }
    for(int i=0;i<=n+1;++i){
        for(int j=0;j<=n+1;++j){
            pp[i][j]=ps[i][j]=sp[i][j]=ss[i][j]={0,0};
        }
    }
    cl();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            mif[i][j]=min(mif[i-1][j],mif[i][j-1]+sm[i][j]-sm[i][j-1]);
            mxf[i][j]=max(mxf[i-1][j],mxf[i][j-1]+sm[i][j]-sm[i][j-1]);
            pp[i][j].first=sm[i][j]-mxf[i][j];
            pp[i][j].second=sm[i][j]-mif[i][j];
        }
    }
    cl();
    for(int i=1;i<=n;++i){
        for(int j=n;j;--j){
            mif[i][j]=min(mif[i-1][j],mif[i][j+1]+sm[i][j]-sm[i][j-1]);
            mxf[i][j]=max(mxf[i-1][j],mxf[i][j+1]+sm[i][j]-sm[i][j-1]);
            ps[i][j].first=sm[i][n]-sm[i][j-1]-mxf[i][j];
            ps[i][j].second=sm[i][n]-sm[i][j-1]-mif[i][j];
        }
    }
    cl();
    for(int j=1;j<=n;++j){
        mif[n+1][j]=mxf[n+1][j]=sm[n][j];
    }
    for(int i=n;i;--i){
        for(int j=1;j<=n;++j){
            mif[i][j]=min(mif[i+1][j],mif[i][j-1]+sm[i-1][j]-sm[i-1][j-1]);
            mxf[i][j]=max(mxf[i+1][j],mxf[i][j-1]+sm[i-1][j]-sm[i-1][j-1]);
            sp[i][j].first=mif[i][j]-sm[i-1][j];
            sp[i][j].second=mxf[i][j]-sm[i-1][j];
        }
    }
    cl();
    for(int j=n;j;--j){
        mif[n+1][j]=mxf[n+1][j]=sm[n][n]-sm[n][j-1];
    }
    for(int i=n;i;--i){
        for(int j=n;j;--j){
            mif[i][j]=min(mif[i+1][j],mif[i][j+1]+sm[i-1][j]-sm[i-1][j-1]);
            mxf[i][j]=max(mxf[i+1][j],mxf[i][j+1]+sm[i-1][j]-sm[i-1][j-1]);
            ss[i][j].first=mif[i][j]-(sm[i-1][n]-sm[i-1][j-1]);
            ss[i][j].second=mxf[i][j]-(sm[i-1][n]-sm[i-1][j-1]);
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j){
            pair<int,int> nq=pp[i][j];
            int sa=sm[n][j]-sm[i][j];
            cj(nq,{s[0]-sp[i+1][j].second,s[0]-sp[i+1][j].first});
            int sb=sm[n][n]-sm[n][j]-sm[i][n]+sm[i][j];
            int tmx=(sm[n][n]-sm[i][n]-sm[n][j]+sm[i][j]-ss[i+1][j+1].first),tmi=(sm[n][n]-sm[i][n]-sm[n][j]+sm[i][j]-ss[i+1][j+1].second);
            cj(nq,{s[1]-sa+s[0]-tmx,s[1]-sa+s[0]-tmi});
            int sc=sm[i][n]-sm[i][j];
            cj(nq,{s[2]-sb+s[1]-sa+s[0]-ps[i][j+1].second,s[2]-sb+s[1]-sa+s[0]-ps[i][j+1].first});
            if(nq.first<=nq.second){
                cout<<"TAK\n";
                return;
            }
        }
    }
    cout<<"NIE\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int op:{0,1,2,3})cin>>s[op];
        for(int i=0;i<=n+1;++i){
            for(int j=0;j<=n+1;++j){
                sm[i][j]=0;
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cin>>a[i][j];
                sm[i][j]=sm[i-1][j]+sm[i][j-1]+a[i][j]-sm[i-1][j-1];
            }
        }
        solve();
    }
    return 0;
}