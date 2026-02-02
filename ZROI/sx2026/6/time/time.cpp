#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int K=405;
const int kc=750;
int q;
int n;
int p[N];
int kid[N];
int L[K],R[K];
void init(){
    const int ks=(q+kc-1)/kc;
    for(int i=1;i<=ks;++i){
        L[i]=R[i-1]+1;
        R[i]=i*kc;
    }
    R[ks]=q;
    for(int i=1;i<=ks;++i){
        for(int j=L[i];j<=R[i];++j){
            kid[j]=i;
        }
    }
}
class SGT{
public:
    vector<int> t[kc<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void update(int l,int r,int k,int x,int d){
        if(l==r){
            t[k].clear();
            t[k].push_back(d);
            return;
        }
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        int id0=0,id1=0;
        t[k].clear();
        while(id0!=t[ls].size()||id1!=t[rs].size()){
            if(id1==t[rs].size()||(id0!=t[ls].size()&&t[ls][id0]<t[rs][id1]-id0)){
                t[k].push_back(t[ls][id0]);
                ++id0;
            }
            else{
                t[k].push_back(t[rs][id1]-id0);
                ++id1;
            }
        }
    }
    int query(int d){
        return upper_bound(t[1].begin(),t[1].end(),d)-t[1].begin();
    }
    #undef mid
    #undef rs
    #undef ls
}sgt[K];
void upd(int id){
    const int nk=kid[id];
    sgt[nk].update(1,R[nk]-L[nk]+1,1,id-L[nk]+1,p[id]);
}
int qu(int x){
    int np=p[x];
    for(int i=x+1;i<=min(n,R[kid[x]]);++i)np+=(np>=p[i]);
    int nk=kid[x]+1;
    for(int i=nk;i<=kid[n];++i){
        np+=sgt[i].query(np);
    }
    return np;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>q;
    cin>>q;
    init();
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            p[++n]=x;
            upd(n);
        }
        else if(op==2){
            int y;
            cin>>y;
            p[x]=y;
            upd(x);
        }
        else{
            cout<<qu(x)<<'\n';
        }
    }
    return 0;
}