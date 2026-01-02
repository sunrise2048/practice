#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int lim=10000000;
ll x;
ll xj[50];
struct ope{
    char op;
    ll x,y;
    ope(char op,ll x,ll y):op(op),x(x),y(y){}
};
vector<ope> op;
ll mi;
ll nv;
mt19937 mt(time(0));
set<ll> st;
void ins(ll val){
    if(mt()%20==0)nv=val;
    st.insert(val);
    for(int i=49;i>=0;--i){
        if(val&(1ll<<i)){
            if(xj[i]==0){
                xj[i]=val;
                return;
            }
            if(st.count(xj[i]^val))return;
            op.emplace_back('^',xj[i],val);
            val^=xj[i];
            st.insert(val);
            if(val&1)mi=min(mi,val);
            if(mt()%20==0)nv=val;
        }
    }
}
void get_val(ll bs){
    ll s=x;
    int hb=0;
    for(int i=25;i>=0;--i){
        if(bs&(1<<i)){
            hb=i;
            break;
        }
    }
    for(int i=hb-1;i>=0;--i){
        if(!st.count(s*2)){
            op.emplace_back('+',s,s);
            ins(s*2);
        }
        s*=2;
        if(i&1){
            if(!st.count(s+x)){
                op.emplace_back('+',s,x);
                ins(s+x);
            }
            s+=x;
        }
        if(!st.count(s+nv)){
            op.emplace_back('+',s,nv);
            ins(s+nv);
        }
    }
}
int main(){
    cin>>x;
    mi=x;
    nv=x;
    ins(x);
    while(!st.count(1)){
        get_val(mt()%lim+1);
    }
    cout<<op.size()<<'\n';
    for(auto [c,x,y]:op)cout<<x<<' '<<c<<' '<<y<<'\n';
    return 0;
}