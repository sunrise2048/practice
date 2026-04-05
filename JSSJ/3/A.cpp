#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m;
ll T;
int xl,yl,xr,yr;
ll calc0(ll x,ll y){
    ll s=x+y;
    return s*(s-1)/2+(2*n-s)*(2*n-s+1)/2;
}
ll d11,d12,d21,d22;
ll ch(int x,int y,ll n11,ll n12,ll n21,ll n22){
    if(x<=xl||xr<=x||y<=yl||yr<=y){
        auto calc1=[&](ll a,ll b){
            if(x<a&&y>b){
                return (y-b)*(a-x);
            }
            if(x>a&&y<b){
                return (y-b)*(a-x);
            }
            return 0ll;
        };
        return n11+calc1(xl,yl)<=d11&&n12+calc1(xl,yr)<=d12&&n21+calc1(xr,yl)<=d21&&n22+calc1(xr,yr)<=d22;
    }
    if(n11>d11||n22>d22)return 0;
    ll a=x-xl,b=xr-x;
    ll c=y-yl,d=yr-y;
    ll A=max(0ll,b*d-(d12-n12-a*d));
    ll B=min(b*d,d21-n21-b*c);
    return A<=B;
}
struct zt{
    int x,y,st;
    ll n11,n12,n21,n22;
};
int main(){
    freopen("sense.in","r",stdin);
    freopen("sense.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>T;
    cin>>xl>>yl>>xr>>yr;
    n--;xl--;yl--;xr--;yr--;
    d11=T-calc0(xl,yl);
    d12=T-calc0(xl,yr);
    d21=T-calc0(xr,yl);
    d22=T-calc0(xr,yr);
    d11/=2;d12/=2;d21/=2;d22/=2;
    if(!ch(0,0,0,0,0,0))return 0;
    vector<zt> st;
    st.push_back({0,0,0,0,0,0});
    int cn=0;
    string s;
    while(!st.empty()&&cn<m){
        zt& no=st.back();
        if(no.x==n&&no.y==n){
            cout<<s<<'\n';
            ++cn;
            st.pop_back();
            if(!st.empty())s.pop_back();
            continue;
        }
        auto [x,y,wrwqef,n11,n12,n21,n22]=no;
        if(no.st==0){
            no.st=1;
            if(x<n){
                ll t11=n11+(x<xl&&y>yl?y-yl:0);
                ll t12=n12+(x<xl&&y>yr?y-yr:0);
                ll t21=n21+(x<xr&&y>yl?y-yl:0);
                ll t22=n22+(x<xr&&y>yr?y-yr:0);
                if(ch(x+1,y,t11,t12,t21,t22)){
                    s+='R';
                    st.push_back({x+1,y,0,t11,t12,t21,t22});
                    continue;
                }
            }
        }
        if(no.st==1){
            no.st=2;
            if(y<n){
                ll t11=n11+(x>xl&&y<yl?x-xl:0);
                ll t12=n12+(x>xl&&y<yr?x-xl:0);
                ll t21=n21+(x>xr&&y<yl?x-xr:0);
                ll t22=n22+(x>xr&&y<yr?x-xr:0);
                if(ch(x,y+1,t11,t12,t21,t22)){
                    s+='U';
                    st.push_back({x,y+1,0,t11,t12,t21,t22});
                    continue;
                }
            }
        }
        st.pop_back();
        if(!st.empty())s.pop_back();
    }
    return 0;
}