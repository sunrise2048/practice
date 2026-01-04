#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int T;
int n,m;
bitset<N> st[N];
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
struct edge{
    int u,v,w;
    edge()=default;
    edge(int u,int v,int w):u(u),v(v),w(w){}
};
vector<edge> ed;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            st[i].reset();
        }
        int sm=0;
        for(int i=1;i<=m;++i){
            int fl=0;
            for(int j=1;j<=n;++j){
                char c;
                cin>>c;
                sm+=c-'0';
                fl|=c-'0';
                st[j][i]=c-'0';
            }
            sm-=fl;
        }
        ed.clear();
        iota(fa+1,fa+n+1,1);
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                ed.emplace_back(i,j,(st[i]&st[j]).count());
            }
        }
        sort(ed.begin(),ed.end(),[](const edge& x,const edge& y){
            return x.w>y.w;
        });
        int ncn=0;
        vector<pair<int,int>> ve;
        for(auto [u,v,w]:ed){
            if(find(u)==find(v))continue;
            ncn+=w;
            ve.emplace_back(u,v);
            fa[find(u)]=find(v);
        }
        if(ncn==sm){
            cout<<"YES\n";
            for(auto [x,y]:ve){
                cout<<x<<' '<<y<<'\n';
            }
        }
        else cout<<"NO\n";
    }
    return 0;
}