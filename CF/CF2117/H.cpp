#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n,q;
int a[N];
class SGT{
public:
    struct node{
        int s,mx,ml,mr;
    }t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    node pushup(const node& x,const node& y){
        return {x.s+y.s,max({x.mx,y.mx,x.mr+y.ml}),max(x.ml,x.s+y.ml),max(y.mr,y.s+x.mr)};
    }
    void build(int l,int r,int k){
        if(l==r){
            t[k]={-1,0,0,0};
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        t[k]=pushup(t[ls],t[rs]);
    }
    void update(int l,int r,int k,int x,int d){
        if(l==r){
            t[k]={d,max(0,d),max(0,d),max(0,d)};
            return;
        }
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        t[k]=pushup(t[ls],t[rs]);
    }
    int qu(){return t[1].mx;}
    #undef mid
    #undef rs
    #undef ls
}sgt;
vector<pair<int,int>> ve[N];
vector<int> ad[N],er[N];
multiset<int> st;
int ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        st.clear();
        for(int i=1;i<=n;++i){
            ve[i].clear();
        }
        for(int i=1;i<=q;++i){
            ad[i].clear();er[i].clear();
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
            ve[a[i]].emplace_back(1,i);
        }
        for(int i=1;i<=q;++i){
            int x,y;
            cin>>x>>y;
            if(a[x]==y)continue;
            ve[a[x]].emplace_back(i,-x);
            a[x]=y;
            ve[y].emplace_back(i,x);
        }
        for(int i=1;i<=n;++i)ve[a[i]].emplace_back(q+1,-i);
        sgt.build(1,n,1);
        for(int i=1;i<=n;++i){
            for(int j=0;j<ve[i].size();++j){
                auto [tm,id]=ve[i][j];
                if(id<0)sgt.update(1,n,1,-id,-1);
                else sgt.update(1,n,1,id,1);
                if(j+1==ve[i].size())break;
                int nt=ve[i][j+1].first;
                if(tm!=nt){
                    int as=sgt.qu();
                    ad[tm].push_back(as/2);er[nt].push_back(as/2);
                }
            }
        }
        for(int i=1;i<=q;++i){
            for(int vl:ad[i])st.insert(vl);
            for(int vl:er[i])st.erase(st.find(vl));
            cout<<*st.rbegin()<<' ';
        }cout<<'\n';
    }
    return 0;
}