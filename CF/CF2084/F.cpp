#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int inf=1e7;
int T;
int n;
int a[N],c[N];
int ta[N],tc[N];
int l[N],r[N];
class SGTma{
public:
    int t[N<<2];
    void cl(){
        for(int i=1;i<=(n<<2);++i){
            t[i]=0;
        }
    }
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void upd(int k,int d){t[k]=max(t[k],d);}
    void update(int l,int r,int k,int x,int y,int d){
        if(x<=l&&r<=y){
            t[k]=max(t[k],d);
            return;
        }
        if(x<=mid)update(l,mid,ls,x,y,d);
        if(y>mid)update(mid+1,r,rs,x,y,d);
    }
    int query(int l,int r,int k,int x){
        if(l==r)return t[k];
        if(x<=mid)return max(t[k],query(l,mid,ls,x));
        return max(t[k],query(mid+1,r,rs,x));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt_ma;
class SGTmi{
public:
    int t[N<<2];
    void cl(){
        for(int i=1;i<=(n<<2);++i){
            t[i]=n+1;
        }
    }
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void upd(int k,int d){t[k]=min(t[k],d);}
    void update(int l,int r,int k,int x,int y,int d){
        if(x<=l&&r<=y){
            t[k]=min(t[k],d);
            return;
        }
        if(x<=mid)update(l,mid,ls,x,y,d);
        if(y>mid)update(mid+1,r,rs,x,y,d);
    }
    int query(int l,int r,int k,int x){
        if(l==r)return t[k];
        if(x<=mid)return min(t[k],query(l,mid,ls,x));
        return min(t[k],query(mid+1,r,rs,x));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt_mi;
struct node{
    int r,id;
    node()=default;
    node(int r,int id):r(r),id(id){}
    bool operator<(const node& x)const{
        return r!=x.r?r>x.r:id>x.id;
    }
};
vector<node> ve[N];
void solve(){
    sgt_mi.cl();sgt_ma.cl();
    for(int i=n;i;--i){
        if(tc[i]){
            if(sgt_ma.query(1,n,1,ta[i])>tc[i]){
                cout<<"-1\n";
                return;
            }
            sgt_ma.update(1,n,1,ta[i],n,tc[i]);
            continue;
        }
        l[i]=sgt_ma.query(1,n,1,ta[i]);
    }
    for(int i=1;i<=n;++i){
        if(tc[i]){
            if(sgt_mi.query(1,n,1,ta[i])<tc[i]){
                cout<<"-1\n";
                return;
            }
            sgt_mi.update(1,n,1,1,ta[i],tc[i]);
            continue;
        }
        r[i]=sgt_mi.query(1,n,1,ta[i]);
    }
    vector<int> id;
    priority_queue<node> pq;
    for(int i=1;i<=n;++i){
        if(c[i]==0)id.push_back(i);
        if(tc[i])continue;
        ve[l[i]+1].emplace_back(r[i],ta[i]);
    }
    int nl=0;
    for(int no:id){
        while(nl<no){
            ++nl;
            for(node x:ve[nl])pq.push(x);
        }
        if(pq.empty()){
            cout<<"-1\n";
            return;
        }
        if(pq.top().r<no){
            cout<<"-1\n";
            return;
        }
        c[no]=a[pq.top().id];
        pq.pop();
    }
    for(int i=1;i<=n;++i){
        cout<<n-c[i]+1<<' ';
    }cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            ve[i].clear();
            cin>>a[i];
            a[i]=n-a[i]+1;
            ta[a[i]]=i;
        }
        for(int i=1;i<=n;++i){
            tc[i]=0;
        }
        for(int i=1;i<=n;++i){
            cin>>c[i];
            if(c[i])c[i]=n-c[i]+1;
            tc[c[i]]=i;
        }
        solve();
    }
    return 0;
}