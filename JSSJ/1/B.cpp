#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5+505;
const int M=505;
const int mod=1e9+7;
int T;
int n,m,k;
vector<int> e[N],ee[N];
int p[N];
double st;
double dur_time(){
    return (clock()-st)/CLOCKS_PER_SEC;
}
mt19937 mt(time(0));
bool vis[N];
vector<int> id;
int dfs(int no){
    shuffle(e[no].begin(),e[no].end(),mt);
    vis[no]=1;id.push_back(no);
    for(int to:e[no]){
        if(!p[to]){
            p[to]=no;
            p[no]=to;
            return 1;
        }
    }
    for(int to:e[no]){
        int pt=p[to];
        if(vis[pt])continue;
        p[no]=to;p[to]=no;p[pt]=0;
        if(dfs(pt))return 1;
        p[no]=0;p[to]=pt;p[pt]=to;
    }
    return 0;
}
int f[M][M];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void gs(){
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;++i){
        for(int to:e[i]){
            if(to<i)continue;
            f[i][to]=mt()%mod;
            f[to][i]=(mod-f[i][to])%mod;
        }
    }
    int cn=0;
    for(int i=1;i<=n;++i){
        if(!f[cn+1][i]){
            for(int j=cn+2;j<=n;++j){
                if(f[j][i]){
                    for(int k=i;k<=n;++k)swap(f[cn+1][k],f[j][k]);
                    break;
                }
            }
        }
        if(!f[cn+1][i])continue;
        ++cn;
        for(int j=cn+1;j<=n;++j){
            if(!f[j][i])continue;
            ll bs=ksm(f[cn][i])*f[j][i]%mod;
            for(int k=cn;k<=n;++k){
                f[j][k]=(f[j][k]-f[cn][k]*bs%mod+mod)%mod;
            }
        }
    }
    cout<<cn/2<<'\n';
}
int main(){
    freopen("threesome.in","r",stdin);
    freopen("threesome.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    double lim=0.6/T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=m;++i)ee[i].clear();
        for(int i=1;i<=2*m+n;++i){
            e[i].clear();
            p[i]=0;
        }
        for(int i=1;i<=k;++i){
            int x,y;
            cin>>x>>y;
            ee[y].push_back(x);
        }
        bool fl=0;
        for(int i=1;i<=m;++i){
            if(ee[i].size()<2)continue;
            if(ee[i].size()==2){
                int x=ee[i][0],y=ee[i][1];
                e[x].push_back(y);
                e[y].push_back(x);
                continue;
            }
            fl=1;
            p[n+i]=n+m+i;
            p[n+m+i]=n+i;
            e[n+i].push_back(n+m+i);
            e[n+m+i].push_back(n+i);
            for(int to:ee[i]){
                e[to].push_back(n+i);
                e[n+i].push_back(to);
                e[to].push_back(n+m+i);
                e[n+m+i].push_back(to);
            }
        }
        if(!fl){
            gs();
            continue;
        }
        st=clock();
        int cn=0;
        while(dur_time()<lim){
            for(int i=1;i<=n;++i){
                if(p[i])continue;
                cn+=dfs(i);
                for(int no:id)vis[no]=0;
                id.clear();
            }
        }
        cout<<cn<<'\n';
    }
    return 0;
}