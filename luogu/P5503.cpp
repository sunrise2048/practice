#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
int a[N];
double ans[N];
double calc(int x,int y){
    return a[y]+sqrt(abs(x-y))-a[x];
}
void solve(int l,int r,int L,int R){
    if(L==R){
        for(int i=l;i<=r;++i){
            ans[i]=max(ans[i],calc(i,L));
        }
        return;
    }
    if(l>r)return;
    const int mid=l+r>>1;
    int z=L;
    double p=calc(mid,L);
    for(int i=L+1;i<=min(R,mid);++i){
        double np;
        if((np=calc(mid,i))>p){
            p=np;
            z=i;
        }
    }
    ans[mid]=max(ans[mid],p);
    solve(l,mid-1,L,z);solve(mid+1,r,z,R);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=n;i;--i)cin>>a[i];
    solve(1,n,1,n);
    reverse(a+1,a+n+1);reverse(ans+1,ans+n+1);
    solve(1,n,1,n);
    for(int i=1;i<=n;++i){
        cout<<(int)ceil(ans[i])<<'\n';
    }
    return 0;
}