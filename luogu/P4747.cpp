#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
int a[N];
pair<int,int> nd[N<<1];
int nl[N<<1];
bool fl[N<<1];
vector<int> e[N<<1];
vector<int> ql[N<<1];
stack<int> st;
int cn;
class SGT{
public:
    int t[N<<2],lz[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void upd(int k,int d){
        t[k]+=d;
        lz[k]+=d;
    }
    void pushdown(int k){
        if(!lz[k])return;
        upd(ls,lz[k]);upd(rs,lz[k]);
        lz[k]=0;
    }
    void pushup(int k){t[k]=min(t[ls],t[rs]);}
    void update(int l,int r,int k,int x,int y,int d){
        if(x<=l&&r<=y){
            upd(k,d);
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x,y,d);
        if(y>mid)update(mid+1,r,rs,x,y,d);
        pushup(k);
    }
    int query(int l,int r,int k,int x){
        if(t[k]>0)return n+1;
        if(r<=x){
            if(l==r)return l;
            pushdown(k);
            if(t[rs]==0)return query(mid+1,r,rs,x);
            return query(l,mid,ls,x);
        }
        pushdown(k);
        if(x<=mid)return query(l,mid,ls,x);
        int vl=query(mid+1,r,rs,x);
        if(vl<=n)return vl;
        return query(l,mid,ls,x);
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
stack<int> st_mi,st_ma;
bool ch(int x,int y){
    if(min(nd[x].second,nd[y].second)==max(nd[x].first,nd[y].first)-1)return 1;
    return 0;
}
void ins(int no){
    if(st.empty()){
        st.push(no);
        return;
    }
    int qu=sgt.query(1,n,1,nl[no]-1);
    if(qu>n){
        st.push(no);
        return;
    }
    if(qu==nl[st.top()]){
        int tq=st.top();
        if(fl[tq]&&ch(e[tq].back(),no)){
            nd[tq].first=min(nd[tq].first,nd[no].first);
            nd[tq].second=max(nd[tq].second,nd[no].second);
            e[tq].push_back(no);
            sgt.update(1,n,1,nl[no],nl[no],n+1);
            st.pop();
            ins(tq);
            return;
        }
        int td=++cn;
        fl[td]=1;
        nd[td].first=min(nd[no].first,nd[tq].first);
        nd[td].second=max(nd[no].second,nd[tq].second);
        e[td].push_back(tq);e[td].push_back(no);
        sgt.update(1,n,1,nl[no],nl[no],n+1);
        nl[td]=qu;
        st.pop();
        ins(td);
        return;
    }
    int td=++cn;
    vector<int> so;
    nd[td]=nd[no];
    so.push_back(no);
    while(!st.empty()&&nl[st.top()]>=qu){
        so.push_back(st.top());
        nd[td].first=min(nd[td].first,nd[st.top()].first);
        nd[td].second=max(nd[td].second,nd[st.top()].second);
        st.pop();
    }
    reverse(so.begin(),so.end());
    for(int i=1;i<so.size();++i)sgt.update(1,n,1,nl[so[i]],nl[so[i]],n+1);
    swap(so,e[td]);
    nl[td]=nl[e[td][0]];
    ins(td);
}
int si[N<<1],zs[N<<1];
int top[N<<1],fa[N<<1];
int d[N<<1];
void dfs1(int no){
    si[no]=1;
    for(int to:e[no]){
        d[to]=d[no]+1;
        dfs1(to);
        fa[to]=no;
        si[no]+=si[to];
        if(si[zs[no]]<si[to])zs[no]=to;
    }
}
void dfs2(int no,int tp){
    top[no]=tp;
    if(!zs[no])return;
    dfs2(zs[no],tp);
    for(int to:e[no]){
        if(to==zs[no])continue;
        dfs2(to,to);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    cn=n;
    for(int i=1;i<=n;++i){
        nl[i]=i;
        sgt.update(1,n,1,1,i,-1);
        nd[i]={a[i],a[i]};
        while(!st_mi.empty()&&a[st_mi.top()]>a[i]){
            int no=st_mi.top();st_mi.pop();
            int la=(st_mi.empty()?1:st_mi.top()+1);
            sgt.update(1,n,1,la,no,a[no]);
        }
        sgt.update(1,n,1,(st_mi.empty()?1:st_mi.top()+1),i,-a[i]);
        st_mi.push(i);
        while(!st_ma.empty()&&a[st_ma.top()]<a[i]){
            int no=st_ma.top();st_ma.pop();
            int la=(st_ma.empty()?1:st_ma.top()+1);
            sgt.update(1,n,1,la,no,-(a[no]+1));
        }
        sgt.update(1,n,1,(st_ma.empty()?1:st_ma.top()+1),i,a[i]+1);
        st_ma.push(i);
        ins(i);
    }
    int rt=st.top();
    dfs1(rt);
    dfs2(rt,rt);
    for(int i=1;i<=cn;++i){
        if(!fl[i])continue;
        for(int to:e[i]){
            ql[i].push_back(nl[to]);
        }
        ql[i].push_back(nl[i]+nd[i].second-nd[i].first+1);
    }
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int lc=lca(x,y);
        if(!fl[lc]){
            cout<<nl[lc]<<' '<<nl[lc]+nd[lc].second-nd[lc].first<<'\n';
        }
        else{
            int nl=*prev(upper_bound(ql[lc].begin(),ql[lc].end(),x));
            int nr=(*upper_bound(ql[lc].begin(),ql[lc].end(),y))-1;
            cout<<nl<<' '<<nr<<'\n';
        }
    }
    return 0;
}