#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int M=5e5+5;
const double eps=1e-12;
int n,m,k;
ll a[N];
ll s[N];
struct sgt{
public:
    struct node{
        double k,b;
        node():k(0),b(1e9){}
    }t[M<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    double get(double k,double b,int x){
        return k*x+b;
    }
    void update(int l,int r,int k,int x,int y,double tk,double tb){
        if(x<=l&&r<=y){
            if(get(tk,tb,l)<get(t[k].k,t[k].b,l)){
                if(get(tk,tb,r)<get(t[k].k,t[k].b,r)){
                    t[k].k=tk,t[k].b=tb;
                    return;
                }
                if(get(tk,tb,mid)<get(t[k].k,t[k].b,mid)){
                    swap(t[k].k,tk);swap(t[k].b,tb);
                    update(mid+1,r,rs,x,y,tk,tb);
                }
                else update(l,mid,ls,x,y,tk,tb);
            }
            else if(get(tk,tb,r)<get(t[k].k,t[k].b,r)){
                if(get(tk,tb,mid+1)<get(t[k].k,t[k].b,mid+1)){
                    swap(t[k].k,tk);swap(t[k].b,tb);
                    update(l,mid,ls,x,y,tk,tb);
                }
                else update(mid+1,r,rs,x,y,tk,tb);
            }
            return;
        }
        if(x<=mid)update(l,mid,ls,x,y,tk,tb);
        if(y>mid)update(mid+1,r,rs,x,y,tk,tb);
    }
    double query(int l,int r,int k,int x){
        if(l==r)return get(t[k].k,t[k].b,x);
        if(x<=mid)return min(query(l,mid,ls,x),get(t[k].k,t[k].b,x));
        return min(query(mid+1,r,rs,x),get(t[k].k,t[k].b,x));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
vector<double> ad[N],er[N];
multiset<double> st;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    if(k==1){
        for(int i=1;i<=n;++i)sgt.update(1,m,1,a[i],a[i],0,0);
        for(int i=1;i<=m;++i){
            double as=sgt.query(1,m,1,i);
            if(as>1)printf("-1\n");
            else printf("%.20f\n",as);
        }
        return 0;
    }
    for(int i=1;i<=n-k+1;++i){
        double av=1.0*(s[i+k-1]-s[i-1])/k;
        ad[i].push_back(av);
        er[i+k].push_back(av);
    }
    for(int i=1;i<=n;++i){
        for(double nv:ad[i])st.insert(nv);
        for(double nv:er[i])st.erase(st.find(nv));
        double mi=*st.begin(),ma=*st.rbegin();
        int z=ceil(mi);
        if(fabs(a[i]-mi)>eps)sgt.update(1,m,1,z,a[i],-1.0/(a[i]-mi),a[i]/(a[i]-mi));
        else sgt.update(1,m,1,a[i],a[i],0,0);
        z=ma;
        if(fabs(a[i]-ma)>eps)sgt.update(1,m,1,a[i],z,1.0/(ma-a[i]),-a[i]/(ma-a[i]));
        else sgt.update(1,m,1,a[i],a[i],0,0);
    }
    for(int i=1;i<=m;++i){
        double as=sgt.query(1,m,1,i);
        if(as>1)printf("-1\n");
        else printf("%.20f\n",as);
    }
    return 0;
}