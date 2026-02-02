#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2805;
const int Q=3e6+5;
int n,q;
struct line{
    ll t,a,b,c;
}le[N];
vector<ll> lis_x,lis_y;
ll f[N*2][N*2],mx_x[N*2][N*2],mx_y[N*2][N*2];
int get_id(vector<ll>& ls,ll no){
    return lower_bound(ls.begin(),ls.end(),no)-ls.begin();
}
struct ques{
    ll x,y;
    int id;
    ques()=default;
    ques(ll x,ll y,int id):x(x),y(y),id(id){}
};
vector<ques> qs[N*2][N*2];
class LCT{
public:
    struct node{
        ll k,b;
        int lson,rson;
    }t[N*60];
    int cn_t;
    void clear(){
        for(int i=1;i<=cn_t;++i){
            t[i].k=t[i].b=t[i].lson=t[i].rson=0;
        }
        cn_t=0;
    }
    #define mid (l+(r-l)/2)
    #define ls t[k].lson
    #define rs t[k].rson
    ll get(ll k,ll b,ll x){return k*x+b;}
    void update(ll l,ll r,int& k,ll tk,ll tb){
        if(!k){
            t[k=++cn_t].k=tk;
            t[k].b=tb;
            return;
        }
        if(get(t[k].k,t[k].b,l)<get(tk,tb,l)){
            if(get(t[k].k,t[k].b,r)<get(tk,tb,r)){
                t[k].k=tk;
                t[k].b=tb;
                return;
            }
            if(get(t[k].k,t[k].b,mid)<get(tk,tb,mid)){
                swap(tk,t[k].k);swap(tb,t[k].b);
                update(mid+1,r,rs,tk,tb);
            }
            else update(l,mid,ls,tk,tb);
        }
        else if(get(t[k].k,t[k].b,r)<get(tk,tb,r)){
            if(get(t[k].k,t[k].b,mid+1)<get(tk,tb,mid+1)){
                swap(tk,t[k].k);swap(tb,t[k].b);
                update(l,mid,ls,tk,tb);
            }
            else update(mid+1,r,rs,tk,tb);
        }
    }
    ll query(ll l,ll r,int k,ll x){
        if(!k)return 0;
        if(x<=mid)return max(get(t[k].k,t[k].b,x),query(l,mid,ls,x));
        return max(get(t[k].k,t[k].b,x),query(mid+1,r,rs,x));
    }
    #undef mid
    #undef ls
    #undef rs
}sgt;
ll ans[Q];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>le[i].t>>le[i].a>>le[i].b>>le[i].c;
        le[i].c/=2;
        auto [t,a,b,c]=le[i];
        lis_x.push_back(t+a);
        lis_x.push_back(t+abs(a-b)+b);
        lis_y.push_back(t-a);
        lis_y.push_back(t+abs(a-b)-b);
    }
    sort(lis_x.begin(),lis_x.end());
    lis_x.erase(unique(lis_x.begin(),lis_x.end()),lis_x.end());
    sort(lis_y.begin(),lis_y.end());
    lis_y.erase(unique(lis_y.begin(),lis_y.end()),lis_y.end());
    for(int i=1;i<=n;++i){
        auto [t,a,b,c]=le[i];
        if(a<b){
            int xl=get_id(lis_x,t+a),xr=get_id(lis_x,t+b+(b-a));
            int y=get_id(lis_y,t-a);
            for(int x=xl;x<xr;++x){
                mx_x[x][y]=max(mx_x[x][y],c);
            }
        }
        else{
            int x=get_id(lis_x,t+a);
            int yl=get_id(lis_y,t-a),yr=get_id(lis_y,t+(a-b)-b);
            for(int y=yl;y<yr;++y){
                mx_y[x][y]=max(mx_y[x][y],c);
            }
        }
    }
    const int X=lis_x.size(),Y=lis_y.size();
    for(int i=X-1;i>=0;--i){
        for(int j=Y-1;j>=0;--j){
            if(i)f[i-1][j]=max(f[i-1][j],f[i][j]+mx_x[i-1][j]*(lis_x[i]-lis_x[i-1]));
            if(j)f[i][j-1]=max(f[i][j-1],f[i][j]+mx_y[i][j-1]*(lis_y[j]-lis_y[j-1]));
        }
    }
    for(int i=1;i<=q;++i){
        int x,y;
        cin>>x>>y;
        int tx=get_id(lis_x,x+y),ty=get_id(lis_y,x-y);
        if(tx<X&&ty<Y){
            ans[i]=f[tx][ty];
            qs[tx][ty].emplace_back(x+y,x-y,i);
        }
    }
    for(int i=1;i<X;++i){
        sgt.clear();
        int rt=0;
        const int xl=1,xr=lis_x[i]-lis_x[i-1];
        for(int j=Y-1;j>=0;--j){
            sgt.update(xl,xr,rt,mx_x[i-1][j],f[i][j]);
            for(auto [x,y,id]:qs[i][j]){
                ans[id]=max(ans[id],sgt.query(xl,xr,rt,lis_x[i]-x));
            }
        }
    }
    for(int j=1;j<Y;++j){
        sgt.clear();
        int rt=0;
        const int yl=1,yr=lis_y[j]-lis_y[j-1];
        for(int i=X-1;i>=0;--i){
            sgt.update(yl,yr,rt,mx_y[i][j-1],f[i][j]);
            for(auto [x,y,id]:qs[i][j]){
                ans[id]=max(ans[id],sgt.query(yl,yr,rt,lis_y[j]-y));
            }
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}