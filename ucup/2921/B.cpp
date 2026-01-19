#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
int n;
int a[N];
int p[N];
struct node{
    int pr,ne;
}lb[N];
int id[N];
int vl[N];
void era(int no){
    lb[lb[no].pr].ne=lb[no].ne;
    lb[lb[no].ne].pr=lb[no].pr;
}
int solve(int l,int r){
    if(l>=r)return 0;
    const int len=r-l+1;
    for(int i=l;i<=r;++i){
        vl[i-l]=a[i];
        id[a[i]]=i-l;
        if(i!=r)lb[a[i]].ne=a[i+1];
        else lb[a[i]].ne=a[l];
        if(i!=l)lb[a[i]].pr=a[i-1];
        else lb[a[i]].pr=a[r];
    }
    int cn=len+1;
    int ct=0;
    for(int i=l;i<r;++i){
        int idl=id[lb[p[i]].pr];
        int idr=id[lb[p[i]].ne];
        idl=(idl+1)%len;idr=(idr-1+len)%len;
        era(p[i]);
        if(idl>idr)idr=idr+len;
        if(idr-idl+1==i-l+1&&(len-idl)%len<cn){
            cn=(len-idl)%len;
            ct=i;
        }
    }
    for(int i=l;i<=r;++i){
        int nid=i-l;
        a[i]=vl[(nid-cn+len)%len];
    }
    return max(solve(l,ct),solve(ct+1,r))+cn;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>p[i];
        a[i]=i;
    }
    cout<<solve(1,n)<<'\n';
    return 0;
}