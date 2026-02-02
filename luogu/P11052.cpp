#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=2e5+5;
const int lm=2e5;
const int inf=0x3f3f3f3f;
int n,m;
int a[N],b[N];
vector<int> C;
int c[N];
vector<int> ta[M],tb[M];
int cna[M],cnb[M];
bool fla[N],flb[N];
void get_c(){
    for(int i=1;i<=n;++i){
        ta[a[i]].push_back(i);
        cna[a[i]]++;
    }
    for(int i=1;i<=m;++i){
        tb[b[i]].push_back(i);
        cnb[b[i]]++;
    }
    for(int i=0;i<=lm;++i){
        if(cna[i]<cnb[i]){
            for(int no:ta[i])fla[no]=1;
        }
        else{
            for(int no:tb[i])flb[no]=1;
        }
    }
    int ida=1,idb=1;
    int la=0,lb=0;
    while(ida<=n||idb<=m){
        while(ida<=n&&!fla[ida]){
            cna[a[ida]]--;
            ++ida;
        }
        while(idb<=m&&!flb[idb]){
            cnb[b[idb]]--;
            ++idb;
        }
        if(ida>n&&idb>m)break;
        if(ida<la||idb<lb){
            C={-1};
            return;
        }
        bool opa=(ida<=n),opb=(idb<=m);
        int va=a[ida],vb=b[idb];
        int nb=inf,na=inf;
        auto it=upper_bound(ta[vb].begin(),ta[vb].end(),la);
        if(it!=ta[vb].end())nb=*it;
        it=upper_bound(tb[va].begin(),tb[va].end(),lb);
        if(it!=tb[va].end())na=*it;
        if(na>idb)opa=0;
        if(nb>ida)opb=0;
        if(cna[vb]<cnb[vb])opa=0;
        if(cnb[va]<cna[va])opb=0;
        if(opa==opb){
            C={-1};
            return;
        }
        if(opa){
            lb=na;
            cna[a[ida]]--;
            C.push_back(a[ida]);
            ++ida;
        }
        else{
            la=nb;
            cnb[b[idb]]--;
            C.push_back(b[idb]);
            ++idb;
        }
    }
}
class SGT{
public:
    int t[N<<2];
    void init(){
        memset(t,0x3f,sizeof(t));
    }
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void update(int l,int r,int k,int x,int d){
        if(l==r){
            t[k]=d;
            return;
        }
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        t[k]=min(t[ls],t[rs]);
    }
    int query(int l,int r,int k,int x,int y){
        if(x>y)return M;
        if(x<=l&&r<=y)return t[k];
        if(y<=mid)return query(l,mid,ls,x,y);
        if(x>mid)return query(mid+1,r,rs,x,y);
        return min(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int pa[N],pb[N];
int lc;
int las[M];
int f[N];
bool vis[M];
bool chk(){
    sgt.init();
    memset(las,0,sizeof(las));
    for(int i=1;i<=lc;++i){
        f[i]=pb[i];
        const int nc=c[i];
        auto it=lower_bound(ta[nc].begin(),ta[nc].end(),pa[i]);
        int la=0;
        if(it!=ta[nc].begin()){
            la=*prev(it);
        }
        if(!las[nc]){
            int na=ta[nc][0],nb=tb[nc][0];
            if(na<pa[i]&&nb<pb[i])return 0;
            f[i]=min(f[i],nb);
        }
        int l1=max(las[nc],1);
        las[nc]=i;
        int l2=lower_bound(pa+1,pa+lc+1,la)-pa;
        int mi1=sgt.query(1,lc,1,l1,l2-1),mi2=sgt.query(1,lc,1,l2,i-1);
        it=upper_bound(tb[nc].begin(),tb[nc].end(),mi1);
        if(it==tb[nc].end())mi1=inf;
        else mi1=*it;
        it=upper_bound(tb[nc].begin(),tb[nc].end(),mi2);
        if(it==tb[nc].end())mi2=inf;
        else mi2=*it;
        if(mi1<pb[i])return 0;
        f[i]=min(f[i],mi2);
        sgt.update(1,lc,1,i,f[i]);
    }
    memset(vis,0,sizeof(vis));
    for(int i=lc;i;--i){
        if(vis[c[i]])continue;
        vis[c[i]]=1;
        if(pa[i]<ta[c[i]].back()){
            int r=lower_bound(pa+1,pa+lc+1,ta[c[i]].back())-pa-1;
            if(sgt.query(1,lc,1,i,r)<tb[c[i]].back()){
                return 0;
            }
        }
    }
    return 1;
}
bool ch(){
    if(C.empty())return 1;
    if(C[0]==-1)return 0;
    int np=1;
    lc=C.size();
    for(int i=1;i<=lc;++i)c[i]=C[i-1];
    for(int i=1;i<=lc;++i){
        while(np<=n&&a[np]!=c[i])++np;
        if(np>n)return 0;
        pa[i]=np;
        ++np;
    }
    np=1;
    for(int i=1;i<=lc;++i){
        while(np<=m&&b[np]!=c[i])++np;
        if(np>m)return 0;
        pb[i]=np;
        ++np;
    }
    if(!chk())return 0;
    int mx=max(n,m);
    swap(n,m);
    for(int i=0;i<=lm;++i)swap(ta[i],tb[i]);
    for(int i=1;i<=mx;++i){
        swap(a[i],b[i]);
    }
    for(int i=1;i<=lc;++i){
        swap(pa[i],pb[i]);
    }
    return chk();
}
vector<int> ucs(vector<int> A,vector<int> B){
    n=A.size();m=B.size();
    for(int i=1;i<=n;++i)a[i]=A[i-1];
    for(int i=1;i<=m;++i)b[i]=B[i-1];
    get_c();
    if(ch())return C;
    return {-1};
}