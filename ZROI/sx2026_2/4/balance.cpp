#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
vector<int> e[N];
vector<int> yz;
int d[N];
int f[N][18];
int fa[N];
int fl[N];
void dfs(int no,int fa){
    f[no][0]=fa;
    for(int i=1;i<18;++i)f[no][i]=f[f[no][i-1]][i-1];
    d[no]=d[fa]+1;
    if(e[no].size()==1){
        yz.push_back(no);
        return;
    }
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
    }
}
int lca(int x,int y){
    if(d[x]<d[y])swap(x,y);
    for(int i=17;i>=0;--i){
        if(d[f[x][i]]>=d[y])x=f[x][i];
    }
    if(x==y)return x;
    for(int i=17;i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    freopen("balance.in","r",stdin);
    freopen("balance.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            e[i].clear();
            d[i]=0;
        }
        yz.clear();
        for(int i=1;i<n;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
            d[u]++;d[v]++;
        }
        for(int i=1;i<=n;++i)fa[i]=i;
        int cn=0;
        for(int i=1;i<=n;++i){
            cn+=(d[i]==1);
        }
        printf("%d\n",(cn+1)/2);
        if(n==2){
            printf("0 1\n");
            continue;
        }
        int rt=0;
        for(int i=1;i<=n;++i){
            if(d[i]>1){ 
                rt=i;
                break;
            }
        }
        for(int i=1;i<=n;++i)d[i]=0;
        dfs(rt,0);
        int op=0;
        for(int i=0;i<(yz.size()+1)/2;i++){
            if(i==yz.size()-i-1){
                int no=yz[i];
                while(no){
                    fl[no]=op;op^=1;
                    fa[no]=find(f[no][0]);
                    no=find(f[no][0]);
                }
                continue;
            }
            int nx=yz[i],ny=yz[i+(yz.size()+1)/2];
            int lc=lca(nx,ny);
            vector<int> nd;
            int no=nx;
            while(d[no]>=d[lc]){
                fl[no]=op;op^=1;
                fa[no]=find(f[no][0]);
                no=find(f[no][0]);
            }
            no=ny;
            while(d[no]>=d[lc]){
                nd.push_back(no);
                fa[no]=find(f[no][0]);
                no=find(f[no][0]);
            }
            reverse(nd.begin(),nd.end());
            for(int nn:nd){
                fl[nn]=op;
                op^=1;
            }
        }
        for(int i=1;i<=n;++i){
            printf("%d ",fl[i]);
        }
        printf("\n");
    }
    return 0;
}