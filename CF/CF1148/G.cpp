#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=1e7+5;
int n,k;
int a[N];
bool isp[M];
int phi[M];
vector<int> pr;
void init(){
    const int n=1e7;
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!isp[i]){
            phi[i]=-1;
            pr.push_back(i);
        }
        for(int p:pr){
            if(i*p>n)break;
            isp[i*p]=1;
            if(i%p==0){
                break;
            }
            else phi[i*p]=-phi[i];
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    init();
    return 0;
}