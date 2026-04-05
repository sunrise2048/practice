#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n;
const int v[5][5]={{2,3,1,1,1},{1,2,3,1,1},{1,1,2,1,3},{1,1,1,3,2},{3,1,1,2,1}};
int gt(int x,int y){
    const int md=(n+1)/2;
    int a=x-md,b=y-md;
    if(abs(a)>2||abs(b)>2){
        if(x==y)return 2;
        if(x==n-y+1)return 3;
        return 1;
    }
    return v[a+2][b+2];
}
int main(){
    cin>>n;
    if(n&1){
        if(n<=3){
            cout<<"-1\n";
            return 0;
        }
        cout<<n*n+3*n<<'\n';
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cout<<gt(i,j)<<' ';
            }cout<<'\n';
        }
        return 0;
    }
    cout<<n*n<<'\n';
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cout<<"1 ";
        }
        cout<<'\n';
    }
    return 0;
}