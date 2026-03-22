#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
int n;
void print(int x,int y){
    if(x>y)swap(x,y);
    cout<<x+1<<' '<<y+1<<'\n';
}
int main(){
    cin>>n;
    if(n&1){
        for(int i=0;i<=n/2;++i){
            for(int j=1;j<=n/2;++j){
                print((i+j-1)%n,(i+n-j)%n);
            }
            if(i!=n/2){
                for(int j=n/2;j;--j){
                    print((i+j)%n,(i+n-j)%n);
                }
            }
        }
    }
    else{
        for(int i=0;i<n-1;++i){
            print(i,n-1);
            for(int j=n/2-1;j;--j){
                print((i+j)%(n-1),(i+n-1-j)%(n-1));
            }
        }
    }
    return 0;
}