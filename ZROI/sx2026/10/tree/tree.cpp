#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=998244353;
int n,typ;
vector<int> e[N];
ll ans[3];
class SOL1{
public:
    int lm;
    int f[N];
    bool fl;
    void dfs(int no,int fa){
        if(e[no].size()-(fa!=0)==0){
            if(lm==0)fl=0;
            f[no]=1;
            return;
        }
        if(!fl)return;
        vector<int> ve;
        for(int to:e[no]){
            if(to==fa)continue;
            dfs(to,no);
            ve.push_back(f[to]);
        }
        int ds=e[no].size()-(fa!=0);
        if(!fa&&(ds&1))ve.push_back(0);
        if(fa&&(ds%2==0))ve.push_back(0);
        sort(ve.begin(),ve.end());
        if(!fa){
            int cn=ve.size()/2;
            for(int i=0;i<cn;++i){
                if(ve[i]+ve[ve.size()-1-i]>lm){
                    fl=0;
                    return;
                }
            }
        }
        else{
            int cn=ve.size()/2;
            bool nf=0;
            for(int i=0;i<ve.size();++i){
                bool lf=1;
                for(int j=0;j<cn;++j){
                    int k=ve.size()-j-1;
                    if(j>=i)++j;
                    if(k<=i)--k;
                    if(ve[j]+ve[k]>lm){
                        lf=0;
                        break;
                    }
                }
                if(lf){
                    nf=1;
                    f[no]=ve[i]+1;
                    if(f[no]>lm)fl=0;
                    break;
                }
            }
            if(!nf){
                fl=0;
                return;
            }
        }
    }
    bool ch(int len){
        lm=len;
        fl=1;
        dfs(1,0);
        return fl;
    }
}sol1;
void solve1(){
    int l=-1,r=n+1;
    while(l<r-1){
        int mid=l+r>>1;
        if(sol1.ch(mid))r=mid;
        else l=mid;
    }
    ans[1]=r;
}
int lm;
vector<pair<int,ll>> f[N];
const int M=17;
ll g[1<<M];
int lg[1<<M];
int vis[1<<M];
int nv;
ll gx[M][M];
ll get_f(int z){
    if(!z)return 1;
    if(vis[z]==nv)return g[z];
    g[z]=0;
    int i=lg[z&-z];
    int lz=z-(1<<i);
    while(lz){
        int j=lg[lz&-lz];
        if(gx[i][j]){
            g[z]=(g[z]+get_f(z-(1<<i)-(1<<j))*gx[i][j])%mod;
        }
        lz-=(1<<j);
    }
    vis[z]=nv;
    return g[z];
}
void dfs(int no,int fa){
    if(e[no].size()-(fa!=0)==0){
        f[no].emplace_back(1,1);
        return;
    }
    vector<int> so;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        so.push_back(to);
    }
    if(!fa){
        if(so.size()%2==1)so.push_back(n+1);
        nv=no;
        for(int i=0;i<so.size();++i){
            for(int j=i+1;j<so.size();++j){
                gx[i][j]=0;
            }
        }
        for(int i=0;i<so.size();++i){
            const int x=so[i];
            for(int j=i+1;j<so.size();++j){
                const int y=so[j];
                int idj=f[y].size()-1;
                for(int idi=0;idi<f[x].size();++idi){
                    ll nf=(f[x][idi].second-(idi?f[x][idi-1].second:0)+mod)%mod;
                    while(idj>=0&&f[y][idj].first+f[x][idi].first>lm)--idj;
                    if(idj<0)break;
                    gx[i][j]=(gx[i][j]+nf*f[y][idj].second)%mod;
                }
            }
        }
        ans[2]=get_f((1<<so.size())-1);
        return;
    }
    if(so.size()%2==0)so.push_back(n+1);
    nv=no;
    for(int i=0;i<so.size();++i){
        for(int j=i+1;j<so.size();++j){
            gx[i][j]=0;
        }
    }
    for(int i=0;i<so.size();++i){
        const int x=so[i];
        for(int j=i+1;j<so.size();++j){
            const int y=so[j];
            int idj=f[y].size()-1;
            for(int idi=0;idi<f[x].size();++idi){
                ll nf=(f[x][idi].second-(idi?f[x][idi-1].second:0)+mod)%mod;
                while(idj>=0&&f[y][idj].first+f[x][idi].first>lm)--idj;
                if(idj<0)break;
                gx[i][j]=(gx[i][j]+nf*f[y][idj].second)%mod;
            }
        }
    }
    for(int i=0;i<so.size();++i){
        const int x=so[i];
        ll nf=get_f((1<<so.size())-1-(1<<i));
        if(!nf)continue;
        for(int j=0;j<f[x].size();++j){
            if(f[x][j].first+1>lm)continue;
            ll tf=(f[x][j].second-(j?f[x][j-1].second:0)+mod)%mod;
            f[no].emplace_back(f[x][j].first+1,tf*nf%mod);
        }
    }
    sort(f[no].begin(),f[no].end());
    int m=0;
    for(int i=1;i<f[no].size();++i){
        if(f[no][i].first==f[no][m].first){
            f[no][m].second=(f[no][m].second+f[no][i].second)%mod;
        }
        else{
            f[no][++m]=f[no][i];
        }
    }
    f[no].resize(m+1);
    for(int i=1;i<=m;++i){
        f[no][i].second=(f[no][i].second+f[no][i-1].second)%mod; 
    }
}
void solve2(){
    f[n+1].emplace_back(0,1);
    lm=ans[1];
    dfs(1,0);
}
int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(int i=0;i<17;++i)lg[1<<i]=i;
    cin>>n>>typ;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;++i)ans[0]+=(e[i].size()&1);
    ans[0]/=2;
    if(typ>1){
        solve1();
        if(typ>2)solve2();
    }
    for(int i=0;i<typ;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}