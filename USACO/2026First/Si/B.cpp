#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
int fa[N];
ll l[N],r[N];
vector<pair<int,ll>> e[N];
ll op[N],c[N];
map<ll,int> mp[N];
bool fl[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool fld;
ll dc;
bool flc;
void dfs(int no){
    fl[no]=1;
    for(auto [to,tc]:e[no]){
        if(!fl[to]){
            op[to]=-op[no];
            c[to]=tc-c[no];
            dfs(to);
            continue;
        }
        if(op[no]+op[to]==0){
            if(c[no]+c[to]!=tc){
                flc=0;
                return;
            }
            continue;
        }
        if((tc-c[no]-c[to])%(op[no]+op[to])!=0){
            flc=0;
            return;
        }
        ll td=(tc-c[no]-c[to])/(op[no]+op[to]);
        if(fld){
            if(dc!=td){
                flc=0;
                return;
            }
        }
        else{
            fld=1;
            dc=td;
        }
    }
}
bool ch(){
    for(int i=1;i<=n;++i){
        if(fa[i]!=i)continue;
        op[i]=1,c[i]=0;
        flc=1;
        dc=fld=0;
        dfs(i);
        if(!flc)return 0;
        if(fld){
            op[i]=0;
            c[i]=dc;
        }
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            fl[i]=0;
            e[i].clear();
            op[i]=c[i]=0;
            mp[i].clear();
            fa[i]=i;
        }
        for(int i=1;i<=n;++i){
            cin>>l[i];
        }
        for(int i=1;i<=n;++i){
            cin>>r[i];
        }
        for(int i=1;i<=m;++i){
            int u,v,c;
            cin>>u>>v>>c;
            fa[find(u)]=find(v);
            e[u].emplace_back(v,c);
            e[v].emplace_back(u,c);
        }
        if(!ch()){
            cout<<"-1\n";
            continue;
        }
        for(int i=1;i<=n;++i){
            int nf=find(i);
            if(op[nf]==0){
                c[i]+=op[i]*c[nf];
                op[nf]=0;
                if(l[i]<=c[i]&&c[i]<=r[i]){
                    mp[nf][c[i]]++;
                }
                continue;
            }
            if(op[i]==1){
                mp[nf][l[i]-c[i]]++;
                mp[nf][r[i]-c[i]+1]--;
            }
            else{
                mp[nf][c[i]-r[i]]++;
                mp[nf][c[i]-l[i]+1]--;
            }
        }
        int cn=0;
        for(int i=1;i<=n;++i){
            if(fa[i]!=i)continue;
            int ns=0,mx=0;
            for(auto [val,tc]:mp[i]){
                ns+=tc;
                mx=max(mx,ns);
            }
            cn+=mx;
        }
        cout<<cn<<'\n';
    }
    return 0;
}