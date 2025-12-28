#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=1.5e3+5;
const ull bas=19260817;
const int mod=1e9+7;
int n,m,l;
unordered_set<ull> st;
ull hap(int x,int y){
    return x*bas+y;
}
struct node{
    int h[7],e[7];
    int cn;
};
vector<node> ndz;
node nod;
unordered_map<ull,int> mp;
ull rd(ull x){
    return x*x*x+((x*x)^x)+x;
}
ull get_ha(node& no){
    ull sum=0;
    for(int i=0;i<no.cn;++i){
        sum+=rd(hap(no.h[i],no.e[i]));
    }
    return sum;
}
void dfs(int no){
    if(no==l+1){
        if(nod.cn==0)return;
        for(int i=0;i<nod.cn;++i){
            if(!nod.h[i]||!nod.e[i])return;
        }
        ndz.push_back(nod);
        return;
    }
    dfs(no+1);
    node las=nod;
    nod.h[nod.cn]=nod.e[nod.cn]=no;
    nod.cn++;
    dfs(no+1);
    nod=las;
    nod.h[nod.cn]=no;
    nod.cn++;
    dfs(no+1);
    nod=las;
    nod.e[nod.cn]=no;
    nod.cn++;
    dfs(no+1);
    nod=las;
    for(int i=0;i<nod.cn;++i){
        if(!nod.e[i]){
            nod.e[i]=no;
            dfs(no+1);
            nod=las;
        }
        if(!nod.h[i]){
            nod.h[i]=no;
            dfs(no+1);
            nod=las;
        }
    }
}
int f[N][N];
bool chk(int x,int y){
    return st.find(hap(x,y))==st.end();
}
bool ck(node& no){
    for(int i=0;i<no.cn;++i){
        if(no.e[i]>l||no.h[i]>l)return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>l;
    if(n==1){
        cout<<"1\n";
        return 0;
    }
    if(n==2){
        if(m)cout<<"0\n";
        else cout<<"1\n";
        return 0;
    }
    if(l==0){
        cout<<(n==1);
        return 0;
    }
    for(int i=1;i<=m;++i){
        int a,b;
        cin>>a>>b;
        st.insert(hap(a,b));
    }
    dfs(1);
    int z=0;
    for(int i=0;i<ndz.size();++i){
        mp[get_ha(ndz[i])]=i;
        if(ndz[i].cn==1&&ndz[i].e[0]==1&&ndz[i].h[0]==1)z=i;
    }
    f[n][z]=1;
    for(int i=n-1;i>1;--i){
        for(int lz=0;lz<ndz.size();++lz){
            if(!f[i+1][lz])continue;
            int lf=f[i+1][lz];
            nod=ndz[lz];
            node tz;
            for(int j=0;j<nod.cn;++j){
                nod.e[j]++;nod.h[j]++;
            }
            tz=nod;
            if(ck(tz)){
                tz.e[tz.cn]=tz.h[tz.cn]=1;
                tz.cn++;
                int nz=mp[get_ha(tz)];
                f[i][nz]=(f[i][nz]+lf)%mod;
            }
            for(int j=0;j<nod.cn;++j){
                tz=nod;
                tz.e[j]=1;
                if(chk(nod.e[j]+i-1,i)&&ck(tz)){
                    int nz=mp[get_ha(tz)];
                    f[i][nz]=(f[i][nz]+lf)%mod;
                }
                tz=nod;
                tz.h[j]=1;
                if(chk(i,nod.h[j]+i-1)&&ck(tz)){
                    int nz=mp[get_ha(tz)];
                    f[i][nz]=(f[i][nz]+lf)%mod;
                }
            }
            for(int j=0;j<nod.cn;++j){
                for(int k=0;k<nod.cn;++k){
                    if(j==k)continue;
                    tz.cn=0;
                    for(int tt=0;tt<nod.cn;++tt){
                        if(tt==j||tt==k)continue;
                        tz.e[tz.cn]=nod.e[tt];
                        tz.h[tz.cn]=nod.h[tt];
                        ++tz.cn;
                    }
                    tz.h[tz.cn]=nod.h[j];
                    tz.e[tz.cn]=nod.e[k];
                    ++tz.cn;
                    if(chk(nod.e[j]+i-1,i)&&chk(i,nod.h[k]+i-1)&&ck(tz)){
                        int nz=mp[get_ha(tz)];
                        f[i][nz]=(f[i][nz]+lf)%mod;
                    }
                }
            }
        }
    }
    ll ans=0;
    for(int i=0;i<ndz.size();++i){
        if(ndz[i].cn!=1)continue;
        if(chk(1,ndz[i].h[0]+1)&&chk(ndz[i].e[0]+1,1)){
            ans=(ans+f[2][i])%mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}