#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=20;
const int M=25;
int n,k,q;
int cn[M];
int ls[M][N],rs[M][N];
int d[M][N][1<<N];
mt19937 mt(time(0));
int main(){
    cin>>n>>k;
    cn[n]=1;
    for(int i=n-1;i;--i){
        sol(i);
    }
    for(int i=0;i<k;++i){
        get_nd(i,"",0,i);
    }
    ;
    return 0;
}