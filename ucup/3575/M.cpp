#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
struct line{
    ll b,k;
};
ll get_y(const line& a,ll x){
    return a.b-x*a.k;
}
int Lim;
struct info{
    vector<int> st;
    vector<line> le;
};
void add_le(info& f,int s,const line& x){
    if(s>Lim)return;
    if(!f.le.empty()&&f.le.back().b==x.b&&f.le.back().k==x.k)return;
    if(!f.st.empty()&&f.st.back()==s){
        f.le.back()=x;
        return;
    }
    f.st.push_back(s);
    f.le.push_back(x);
}
info upd_f(const info& f,ll db,ll dk){
    info as;as.st=f.st;
    as.le.reserve(f.le.size());
    for(auto t:f.le){
        as.le.push_back({t.b+db,t.k+dk});
    }
    return as;
}
info mer_f(const info& A,const info& B){
    info as;
    as.st.reserve(A.st.size()+B.st.size());
    as.le.reserve(A.le.size()+B.le.size());
    int ida=0,idb=0;
    int no=0;
    while(no<=Lim){
        int na=(ida+1<A.st.size()?A.st[ida+1]:Lim+1);
        int nb=(idb+1<B.st.size()?B.st[idb+1]:Lim+1);
        int r=min(na,nb)-1;
        add_le(as,no,{A.le[ida].b+B.le[idb].b,A.le[ida].k+B.le[idb].k});
        no=r+1;
        if(na==no)++ida;
        if(nb==no)++idb;
    }
    return as;
}
void ins_seg(info& f,ll l,ll r,const line& li){
    if(l>r||r<0||l>Lim)return;
    if(l<0)l=0;
    if(r>Lim)r=Lim;
    if(l<=r)add_le(f,l,li);
}
ll fl_div(ll a,ll b){
    ll q=a/b,r=a%b;
    if(r&&(r>0)!=(b>0))--q;
    return q;
}
ll ce_div(ll a,ll b){
    ll q=a/b,r=a%b;
    if(r&&(r>0)==(b>0))++q;
    return q;
}
info mxf(const info& A,const info& B){
    info as;
    as.st.reserve(A.st.size()+B.st.size());
    as.le.reserve(A.le.size()+B.le.size());
    int ida=0,idb=0;
    int no=0;
    while(no<=Lim){
        int na=(ida+1<A.st.size()?A.st[ida+1]:Lim+1);
        int nb=(idb+1<B.st.size()?B.st[idb+1]:Lim+1);
        int r=min(na,nb)-1;
        const line &a=A.le[ida],&b=B.le[idb];
        ll dl=get_y(a,no)-get_y(b,no);
        ll dr=get_y(a,r)-get_y(b,r);
        if(dl>=0&&dr>=0){
            add_le(as,no,a);
        }
        else if(dl<=0&&dr<=0){
            add_le(as,no,b);
        }
        else{
            ll D=a.b-b.b;
            ll S=a.k-b.k;
            if(dl>0){
                ll t=fl_div(D,S);
                ins_seg(as,no,min((ll)r,t),a);
                ins_seg(as,max((ll)no,t+1),r,b);
            }
            else{
                ll t=ce_div(D,S);
                ins_seg(as,no,min((ll)r,t-1),b);
                ins_seg(as,max((ll)no,t),r,a);
            }
        }
        no=r+1;
        if(na==no)++ida;
        if(nb==no)++idb;
    }
    return as;
}
ll query_f(const info& A,int x){
    int p=upper_bound(A.st.begin(),A.st.end(),x)-A.st.begin()-1;
    return get_y(A.le[p],x);
}
struct node{
    int len;
    ll s;
    info pre,suf,bst;
};
vector<ll> s;
#define mid (l+r>>1)
node build(int l,int r){
    if(l==r){
        info f;
        f.st.push_back(0);
        f.le.push_back({s[l],1});
        return {1,s[l],f,f,f};
    }
    node L=build(l,mid),R=build(mid+1,r);
    node as;
    as.len=L.len+R.len;
    as.s=L.s+R.s;
    info rp=upd_f(R.pre,L.s,L.len);
    as.pre=mxf(L.pre,rp);
    info ls=upd_f(L.suf,R.s,R.len);
    as.suf=mxf(R.suf,ls);
    info cr=mer_f(L.suf,R.pre);
    info tmp=mxf(L.bst,R.bst);
    as.bst=mxf(tmp,cr);
    return as;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    for(int i=0;i<n;++i)cin>>a[i];
    vector<int> c(q);
    Lim=0;
    for(int i=0;i<q;++i){
        cin>>c[i];
        Lim=max(Lim,c[i]);
    }
    ll no=0;
    for(int i=0;i<n;++i){
        if(a[i]==-1){
            s.push_back(no);
            no=0;
        }
        else no+=a[i];
    }
    s.push_back(no);
    node rt=build(0,s.size()-1);
    for(int i=0;i<q;++i){
        ll ans=c[i]+query_f(rt.bst,c[i]);
        cout<<ans<<'\n';
    }
    return 0;
}