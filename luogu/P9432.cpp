#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,q;
ll a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        ll no=x;
        int l,r=lower_bound(a+1,a+n+1,x)-a;
        l=r-1;
        ll sum=0;
        while(l!=0||r!=n+1){
            if(l==0){
                sum+=a[n]-no;
                break;
            }
            if(r==n+1){
                sum+=no-a[1];
                break;
            }
            if(no-a[l]<=a[r]-no){
                sum+=no-a[l];
                no=a[l];
                int it=lower_bound(a+1,a+l,no-(a[r]-no))-a;
                sum+=no-a[it];
                no=a[it];
                l=it-1;
            }
            else{
                sum+=a[r]-no;
                no=a[r];
                int it=lower_bound(a+r+1,a+n+1,no+(no-a[l]))-a-1;
                sum+=a[it]-no;
                no=a[it];
                r=it+1;
            }
        }
        cout<<sum<<'\n';
    }
    return 0;
}