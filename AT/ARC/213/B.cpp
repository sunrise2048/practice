#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e6+5;
int T;
int cop;
ll L,R;
int len;
bool fl[N];
vector<int> id[2];
bool as[N];
int cn;
void dfs(ll x){
    fl[x-L]=1;
    int op=__builtin_popcountll(x);
    id[op&1].push_back(x-L);
    for(int i=0;i<23;++i){
        ll tx=x^(1<<i);
        if(tx<L||tx>R)continue;
        if(fl[tx-L])continue;
        dfs(tx);
    }
}
const int M=505;
int fa[M];
ll si[M][2];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector<pair<ll,ll>> nd;
void get_nd(ll l,ll r){
    if(L<=l&&r<=R){
        nd.emplace_back(l,r-l+1);
        return;
    }
    ll mid=(l+r)>>1;
    if(L<=mid)get_nd(l,mid);
    if(R>mid)get_nd(mid+1,r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>cop;
        cin>>L>>R;
        if(cop){
            len=R-L+1;
            memset(fl,0,sizeof(bool)*(len+1));
            cn=0;
            memset(as,0,sizeof(bool)*(len+1));
            for(int i=0;i<len;++i){
                if(fl[i])continue;
                id[0].clear();
                id[1].clear();
                dfs(L+i);
                cn+=max(id[0].size(),id[1].size());
                if(id[0].size()>id[1].size()){
                    for(int no:id[0])as[no]=1;
                }
                else{
                    for(int no:id[1])as[no]=1;
                }
            }
            for(int i=0;i<len;++i){
                cout<<as[i];
            }
            cout<<'\n';
        }
        else{
            nd.clear();
            get_nd(0,(1ll<<60)-1);
            for(int i=0;i<nd.size();++i){
                fa[i]=i;
                si[i][0]=si[i][1]=0;
                if(nd[i].second==1){
                    si[i][__builtin_popcountll(nd[i].first)&1]=1;
                }
                else{
                    si[i][0]=si[i][1]=nd[i].second/2;
                }
            }
            for(int i=0;i<nd.size();++i){
                for(int j=i+1;j<nd.size();++j){
                    if(find(i)==find(j))continue;
                    ll hb=max(nd[i].second,nd[j].second);
                    if(__builtin_popcountll((nd[i].first^nd[j].first)&((1ll<<60)-hb))<=1){
                        si[find(j)][0]+=si[find(i)][0];
                        si[find(j)][1]+=si[find(i)][1];
                        fa[find(i)]=find(j);
                    }
                }
            }
            ll ans=0;
            for(int i=0;i<nd.size();++i){
                if(fa[i]==i){
                    ans+=max(si[i][0],si[i][1]);
                }
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}