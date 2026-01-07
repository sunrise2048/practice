#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=25;
int n;
int a[N];
bool fl[N*N*N];
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=0;j<=1000;++j){
            if(fl[j])continue;
            a[i]=j;
            break;
        }
        fl[a[i]]=1;
        for(int j=1;j<i;++j){
            for(int k=1;k<i;++k){
                if(a[i]+a[j]>=a[k]){
                    fl[a[i]+a[j]-a[k]]=1;
                }
                if(j!=k&&a[j]+a[k]>=a[i]){
                    fl[a[j]+a[k]-a[i]]=1;
                }
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j)cout<<"0 ";
            else cout<<a[i]+a[j]<<' ';
        }cout<<'\n';
    }
    return 0;
}