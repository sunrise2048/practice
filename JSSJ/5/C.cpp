#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,a,b,c,op;
bool ch(int n,ll a,ll b,ll c){
    if(a*b*c<n)return 0;
    if(max({a+b-c,a+c-b,b+c-a})<=n)return 1;
    return 0;
}
int p[N],q[N],r[N];
int *P,*Q,*R;
set<ll> vl;
set<pair<ll,ll>> stq,str;
void solve(int n,ll a,ll b,ll c){
    if(n>=a+b+c-2){
        vl.clear();
        stq.clear();str.clear();
        auto gid_q=[&](ll vl)->ll {
            return (b*c-(vl-1)/a-1)*a+(vl-1)%a+1;
        };
        auto gid_r=[&](ll vl)->ll {
            return (vl-1)/(a*c)*(a*c)+a*c-(vl-1)%(a*c);
        };
        vector<ll> ve;
        auto ins=[&](ll x)->void {
            if(vl.count(x))return;
            ve.push_back(x);
            vl.insert(x);
            stq.emplace(gid_q(x),x);
            str.emplace(gid_r(x),x);
        };
        for(int i=1;i<=a;++i){
            ins(i);
        }
        for(int i=0;i<b;++i){
            ins(i*a*c+1);
        }
        for(int i=0;i<c;++i){
            ins(i*a+1);
        }
        int i=1;
        while(ve.size()<n){
            ins(i);++i;
        }
        sort(ve.begin(),ve.end());
        for(int i=1;i<=n;++i){
            p[i]=i;
        }
        for(int i=1;i<=n;++i){
            ll x=stq.begin()->second;stq.erase(stq.begin());
            q[i]=lower_bound(ve.begin(),ve.end(),x)-ve.begin()+1;
        }
        for(int i=1;i<=n;++i){
            ll x=str.begin()->second;str.erase(str.begin());
            r[i]=lower_bound(ve.begin(),ve.end(),x)-ve.begin()+1;
        }
        return;
    }
    if(ch(n-1,a-1,b-1,c-1)){
        p[n]=q[n]=r[n]=n;
        solve(n-1,a-1,b-1,c-1);
        return;
    }
    if(a!=2){
        P=r;Q=p;R=q;
    }
    else if(b!=2){
        P=q;Q=p;R=r;
    }
    else{
        P=p;Q=q;R=r;
    }
    for(int i=1;i<=n;++i){
        P[i]=i;
        Q[i]=R[i]=n-i+1;
    }
    swap(Q[1],Q[2]);swap(R[2],R[3]);
}
int main(){
    freopen("memory.in","r",stdin);
    freopen("memory.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>a>>b>>c>>op;
        if(!ch(n,a,b,c)){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        if(!op)continue;
        solve(n,a,b,c);
        for(int i=1;i<=n;++i){
            cout<<p[i]<<' ';
        }cout<<'\n';
        for(int i=1;i<=n;++i){
            cout<<q[i]<<' ';
        }cout<<'\n';
        for(int i=1;i<=n;++i){
            cout<<r[i]<<' ';
        }cout<<'\n';
    }
    return 0;
}