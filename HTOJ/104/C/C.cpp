#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m,k;
vector<int> e[N];
class SOL{
public:
    int f[1<<10],g[1<<10];
    int z[10][10];
    void sol(){
        memset(g,0,sizeof(g));
        memset(f,0x3f,sizeof(f));
        memset(z,0,sizeof(z));
        for(int i=0;i<n;++i){
            z[i][0]=z[i][1]=(1<<i);
            for(int to:e[i+1])z[i][1]|=(1<<to-1);
        }
        for(int i=0;i<n;++i){
            for(int j=2;j<n;++j){
                z[i][j]=z[i][j-1];
                for(int k=0;k<n;++k){
                    if(z[i][j-1]&(1<<k))z[i][j]|=z[k][1];
                }
            }
        }
        k=min(k,n-1);
        f[0]=0;
        for(int i=0;i<(1<<n);++i){
            for(int j=0;j<n;++j){
                int tj=i|z[j][k];
                if(f[tj]>f[i]+1){
                    f[tj]=f[i]+1;
                    g[tj]=g[i]|(1<<j);
                }
            }
        }
        cout<<f[(1<<n)-1]<<'\n';
        for(int i=0;i<n;++i){
            if(g[(1<<n)-1]&(1<<i))cout<<"1";
            else cout<<"0";
        }cout<<'\n';
    }
}sol_bl;
bool fl[N];
int md[N],xd[N];
int cn;
void dfs(int no,int fa){
    md[no]=k;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        xd[no]=min(xd[no],xd[to]+1);
        md[no]=min(md[no],md[to]-1);
    }
    if(xd[no]<=md[no]){
        md[no]=n+1;
        return;
    }
    if(!md[no]||no==1){
        ++cn;
        fl[no]=1;
        xd[no]=0;
        md[no]=n+1;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        if(n<=10){
            sol_bl.sol();
            for(int i=1;i<=n;++i)e[i].clear();
            continue;
        }
        if(m==n-1){
            fill(xd+1,xd+n+1,n+1);
            dfs(1,0);
            cout<<cn<<'\n';
            cn=0;
            for(int i=1;i<=n;++i){
                if(fl[i]){
                    cout<<"1";
                }
                else{
                    cout<<"0";
                }
                fl[i]=0;
                e[i].clear();
            }
            cout<<'\n';
            continue;
        }
    }
    return 0;
}