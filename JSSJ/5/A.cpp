#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
string c;
int s[N];
int lg[N];
int st[20][N];
ll ans;
int gmx(int l,int r){
    int k=lg[r-l+1];
    if(s[st[k][l]]>s[st[k][r-(1<<k)+1]])return st[k][l];
    return st[k][r-(1<<k)+1];
}
vector<int> t[N];
int get_t(int no,int x){
    if(s[no]+1-(int)t[no].size()>x)return 0;
    return t[no][t[no].size()-1-(s[no]-x)];
}
int sol(int l,int r){
    if(l>r)return n+1;
    int no=gmx(l,r);
    int ls=sol(l,no-1),rs=sol(no+1,r);
    vector<int> tls,trs;
    swap(tls,t[ls]);swap(trs,t[rs]);
    if(s[ls]==s[no])tls.back()++;
    else{
        if(tls.empty())tls.push_back(1);
        else tls.push_back(tls.back()+1);
    }
    if(s[rs]==s[no])trs.back()++; 
    else{
        if(trs.empty())trs.push_back(1);
        else trs.push_back(trs.back()+1);
    }
    if(tls.size()>trs.size())swap(tls,trs);
    swap(t[no],trs);
    for(int i=0;i<tls.size();++i){
        ans+=(ll)(t[no].back()-get_t(no,i-1))*(tls[tls.size()-1-i]-(i+1==tls.size()?0:tls[tls.size()-i-2]));
    }
    ans--;
    for(int i=0;i<tls.size();++i){
        t[no][t[no].size()-1-i]+=tls[tls.size()-1-i];
    }
    t[no].back()--;
    return no;
}
int main(){
    freopen("bracket.in","r",stdin);
    freopen("bracket.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>c;n=c.size();
    c="0"+c;
    for(int i=1;i<=n;++i){
        s[i]=s[i-1]+1-2*(c[i]==')');
    }
    s[n+1]=-1;
    for(int i=0;i<=n;++i)st[0][i]=i;
    for(int i=2;i<=n+1;++i)lg[i]=lg[i>>1]+1;
    for(int j=1;j<20;++j){
        for(int i=0;i+(1<<j)-1<=n;++i){
            if(s[st[j-1][i]]>s[st[j-1][i+(1<<j-1)]])st[j][i]=st[j-1][i];
            else st[j][i]=st[j-1][i+(1<<j-1)];
        }
    }
    sol(0,n);
    cout<<ans<<'\n';
    return 0;
}