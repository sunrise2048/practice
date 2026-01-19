#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int mod=998244353;
int n,q;
int a[N];
int t[N];
vector<pair<int,int>> qu[N];
set<int> st[N];
int nxt[N];
int pre[N];
ll vl[19][N];
int vt[19][N];
ll mi[N];
void init_v(){
    stack<int> s;
    a[0]=n+1;
    s.push(0);
    for(int i=1;i<=n;++i){
        while(a[s.top()]<a[i])s.pop();
        pre[i]=s.top();
        s.push(i);
    }
    for(int i=1;i<=n;++i){
        vl[0][i]=a[i];
        vt[0][i]=i;
    }
    for(int j=1;j<19;++j){
        if((1<<j)>n)break;
        for(int i=1;i<=n;++i){
            vt[j][i]=vt[j-1][pre[vt[j-1][i]]];
            vl[j][i]=(vl[j-1][pre[vt[j-1][i]]]+mi[(1<<j-1)]*vl[j-1][i])%mod;
        }
    }
}
pair<ll,int> get_v(int x,int l){
    ll val=0;
    int len=0;
    for(int i=18;i>=0;--i){
        if(vt[i][x]<l)continue;
        val=(mi[1<<i]*val+vl[i][x])%mod;
        len+=(1<<i);
        x=pre[vt[i][x]];
    }
    return {val,len};
}
int mxz;
vector<int> st_mx;
set<int> st_x;
int las[N];
set<int> st_nl,st_fl;
bool fl[N];
void upd(int no){
    if(mxz>=no){
        if(st_fl.count(no)==0){
            return;
        }
        auto it=upper_bound(st_mx.begin(),st_mx.end(),nxt[no]);
        if(it==st_mx.end()||a[*it]<=a[las[no]]){
            st_nl.insert(no);
            return;
        }
        st_x.insert(no);
        return;
    }
    mxz=no;
    vector<int> id;
    int to=no;
    while(!st_fl.count(to)&&to){
        id.push_back(to);
        to=pre[to];
    }
    while(!st_x.empty()&&*st_x.rbegin()>=to){
        st_x.erase(*st_x.rbegin());
    }
    while(!st_nl.empty()&&*st_nl.rbegin()>=to){
        st_nl.erase(*st_nl.rbegin());
    }
    while(!st_fl.empty()&&*st_fl.rbegin()>=to){
        st_fl.erase(*st_fl.rbegin());
    }
    id.push_back(to);
    for(int i=0;i+1<id.size();++i){
        las[id[i+1]]=id[i];
    }
    for(int x:id){
        st_fl.insert(x);
    }
    for(int x:id){
        if(x==no)continue;
        if(nxt[x])upd(x);
    }
}
void add_val(int val){
    while(!st_nl.empty()&&a[las[*st_nl.rbegin()]]<val){
        int no=*st_nl.rbegin();
        st_nl.erase(no);
        st_x.insert(no);
    }
}
ll ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=q;++i){
        int l,r;
        cin>>l>>r;
        qu[r].emplace_back(l,i);
    }
    mi[0]=1;
    for(int i=1;i<=n;++i)mi[i]=mi[i-1]*3%mod;
    init_v();
    for(int r=1;r<=n;++r){
        add_val(a[r]);
        while(!st_mx.empty()&&a[st_mx.back()]<=a[r])st_mx.pop_back();
        st_mx.push_back(r);
        if(t[a[r]]){
            nxt[t[a[r]]]=r;
            upd(t[a[r]]);
        }
        t[a[r]]=r;
        for(auto [l,id]:qu[r]){
            if(mxz<l){
                ans[id]=-1;
                continue;
            }
            auto it=st_x.lower_bound(l);
            int pn=mxz;
            if(it!=st_x.end())pn=*it;
            ll nv=get_v(r,nxt[pn]+1).first;
            auto [tv,tlen]=get_v(pn,l);
            nv=(nv*mi[tlen]+tv)%mod;
            ans[id]=nv;
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}