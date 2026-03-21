#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using I128=__int128;
const int N=2e5+5;
int n,op;
int lm;
int a[N],b[N];
vector<int> lis;
vector<int> e[N];
struct node{
    I128 sum;
    ll cn;
    int lson,rson;
}t[N*250];
int cnt;
#define mid (l+r>>1)
#define rs(k) t[k].rson
#define ls(k) t[k].lson
void pushup(int k){
    t[k].sum=t[ls(k)].sum+t[rs(k)].sum;
    t[k].cn=t[ls(k)].cn+t[rs(k)].cn;
}
void update_val(int l,int r,int& k,int x,ll d){
    if(t[k].cn+d==0){
        k=0;
        return;
    }
    int no=++cnt;
    t[no]=t[k];k=no;
    if(l==r){
        t[k].cn+=d;
        t[k].sum+=(I128)lis[l-1]*d;
        return;
    }
    if(x<=mid)update_val(l,mid,ls(k),x,d);
    else update_val(mid+1,r,rs(k),x,d);
    pushup(k);
}
void update_cl(int l,int r,int& k,int k0,int x){
    if(x>r)return;
    if(x<=l){
        k=k0;
        return;
    }
    int no=++cnt;
    t[no]=t[k];k=no;
    if(x<=mid)update_cl(l,mid,ls(k),ls(k0),x);
    update_cl(mid+1,r,rs(k),rs(k0),x);
    pushup(k);
}
int cr,rcn;
int ncn;
I128 query(int l,int r,int k,int k0,int x,int& d){
    if(t[k].cn-t[k0].cn==0||!d)return 0;
    if(x<=l){
        if(t[k].cn-t[k0].cn<=d){
            ncn+=(t[k].cn-t[k0].cn);
            d-=(t[k].cn-t[k0].cn);
            cr=l;
            return (t[k].sum-t[k0].sum)-(t[k].cn-t[k0].cn)*lis[x-1];
        }
        if(l==r){
            cr=l+1;
            rcn=d;
            ncn+=d;
            d=0;
            return (I128)rcn*(lis[l-1]-lis[x-1]);
        }
        I128 sm=query(mid+1,r,rs(k),rs(k0),x,d);
        return sm+query(l,mid,ls(k),ls(k0),x,d);
    }
    I128 sm=query(mid+1,r,rs(k),rs(k0),x,d);
    if(x<=mid)sm+=query(l,mid,ls(k),ls(k0),x,d);
    return sm;
}
pair<int,ll> qu(int l,int r,int k){
    if(!k)return {-1,-1};
    if(l==r)return {l,t[k].cn};
    if(t[rs(k)].cn)return qu(mid+1,r,rs(k));
    return qu(l,mid,ls(k));
}
int merge(int l,int r,int k,int k0){
    if(!k||!k0)return k|k0;
    int no=++cnt;
    t[no]=t[k];
    if(l==r){
        t[no].cn+=t[k0].cn;
        t[no].sum+=t[k0].sum;
        return no;
    }
    ls(no)=merge(l,mid,ls(k),ls(k0));
    rs(no)=merge(mid+1,r,rs(k),rs(k0));
    pushup(no);
    return no;
}
#undef mid
#undef rs
#undef ls
vector<pair<int,int>> er[N];
int rtf[N],rtg[N];
I128 sum[N],sg[N];
ll sf[N];
void dfs_si(int no,int fa){
    for(int to:e[no]){
        if(to==fa)continue;
        dfs_si(to,no);
        sum[no]+=sum[to];
        rtf[no]=merge(1,lm,rtf[no],rtf[to]);
    }
    update_val(1,lm,rtf[no],a[no],2*b[no]);
    ll nc=b[no];
    auto pr=qu(1,lm,rtf[no]);
    sf[no]-=(I128)lis[a[no]-1]*b[no];
    while(nc){
        auto [id,ncn]=pr;
        if(ncn<=0){
            cout<<"?";
        }
        ll d=min(ncn,nc);
        sf[no]+=(I128)d*lis[id-1];
        nc-=d;
        er[no].emplace_back(id,d);
        update_val(1,lm,rtf[no],id,-d);
        pr=qu(1,lm,rtf[no]);
    }
    sum[no]+=sf[no];
}
I128 ans[N];
void dfs_ans(int no,int fa){
    for(auto [id,d]:er[no]){
        update_val(1,lm,rtg[no],id,d);
    }
    int ld=b[no];
    ans[no]=sum[no]-sf[no]+sg[no]+query(1,lm,rtg[no],0,a[no],ld);
    for(int to:e[no]){
        if(to==fa)continue;
        ld=b[no];
        int nrt=rtg[no];
        cr=lm+1;rcn=ncn=0;
        sg[to]=sg[no]+sum[no]-sf[no]-sum[to]+query(1,lm,nrt,rtf[to],a[no],ld);
        update_cl(1,lm,nrt,rtf[to],cr);
        if(rcn)update_val(1,lm,nrt,cr-1,-rcn);
        rtg[to]=nrt;
        dfs_ans(to,no);
    }
}
int st[50],str;
void print(I128 no){
    str=0;
    do{
        st[++str]=no%10;
        no/=10;
    }while(no);
    for(int i=str;i;--i)cout<<st[i];
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>op;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        lis.push_back(a[i]);
    }
    sort(lis.begin(),lis.end());
    lis.erase(unique(lis.begin(),lis.end()),lis.end());
    for(int i=1;i<=n;++i)a[i]=lower_bound(lis.begin(),lis.end(),a[i])-lis.begin()+1;
    lm=lis.size();
    for(int i=1;i<=n;++i){
        cin>>b[i];
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs_si(1,0);
    if(op==1){
        print(sum[1]);
        return 0;
    }
    rtg[1]=rtf[1];
    dfs_ans(1,0);
    for(int i=1;i<=n;++i){
        print(ans[i]);
    }
    return 0;
}