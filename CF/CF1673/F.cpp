#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=32;
int n,k;
int a[N][N];
int g[N];
int main(){
    for(int i=0;i<N;++i){
        g[i]=i^(i/2);
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            for(int k=0;k<10;++k){
                if(k&1){
                    a[i][j]|=(((g[i]>>(k/2))&1)<<k);
                }
                else{
                    a[i][j]|=(((g[j]>>(k/2))&1)<<k);
                }
            }
        }
    }
    cin>>n>>k;
    for(int i=0;i<n;++i){
        for(int j=0;j<n-1;++j){
            cout<<(a[i][j]^a[i][j+1])<<' ';
        }
        cout<<endl;
    }
    for(int i=0;i<n-1;++i){
        for(int j=0;j<n;++j){
            cout<<(a[i][j]^a[i+1][j])<<' ';
        }
        cout<<endl;
    }
    int no=0;
    while(k--){
        int x;
        cin>>x;
        no^=x;
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(a[i][j]==no){
                    cout<<i+1<<' '<<j+1<<endl;
                }
            }
        }
    }
    return 0;
}