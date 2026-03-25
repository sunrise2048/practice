#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
int pr[N],ne[N];
int id[N];
class SGT{
public:
    int ma[N<<2],mi[N<<2],lz[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){ma[k]=max(ma[ls],ma[rs]);mi[k]=min(mi[ls],mi[rs]);}
    void build(int l,int r,int k){
        lz[k]=0;
        if(l==r){
            ma[k]=mi[k]=l;
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        pushup(k);
    }
    void upd(int k,int d){
        ma[k]+=d;mi[k]+=d;
        lz[k]+=d;
    }
    void pushdown(int k){
        if(!lz[k])return;
        upd(ls,lz[k]);upd(rs,lz[k]);
        lz[k]=0;
    }
    void update(int l,int r,int k,int x){
        if(x<=l){
            upd(k,-2);
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x);
        update(mid+1,r,rs,x);
        pushup(k);
    }
    int query_mi(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return mi[k];
        pushdown(k);
        if(y<=mid)return query_mi(l,mid,ls,x,y);
        if(x>mid)return query_mi(mid+1,r,rs,x,y);
        return min(query_mi(l,mid,ls,x,y),query_mi(mid+1,r,rs,x,y));
    }
    int query_ma(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return ma[k];
        pushdown(k);
        if(y<=mid)return query_ma(l,mid,ls,x,y);
        if(x>mid)return query_ma(mid+1,r,rs,x,y);
        return max(query_ma(l,mid,ls,x,y),query_ma(mid+1,r,rs,x,y));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        {
            stack<int> st;
            for(int i=1;i<=n;++i){
                while(!st.empty()&&a[st.top()]>=a[i])st.pop();
                pr[i]=(st.empty()?1:st.top()+1);
                st.push(i);
            }
            while(!st.empty())st.pop();
            for(int i=n;i;--i){
                while(!st.empty()&&a[st.top()]>=a[i])st.pop();
                ne[i]=(st.empty()?n:st.top()-1);
                st.push(i);
            }
        }
        iota(id+1,id+n+1,1);
        sort(id+1,id+n+1,[](const int& x,const int& y){
            return a[x]<a[y];
        });
        sgt.build(0,n,1);
        int no=0;
        int ans=0;
        for(int i=1;i<=n;++i){
            int x=id[i];
            while(sgt.query_ma(0,n,1,x,ne[x])>=sgt.query_mi(0,n,1,pr[x]-1,x-1)){
                ++no;
                sgt.update(0,n,1,id[no]);
            }
            ans=max(ans,a[id[no]]-a[x]);
        }
        cout<<ans<<'\n';
    }
    return 0;
}