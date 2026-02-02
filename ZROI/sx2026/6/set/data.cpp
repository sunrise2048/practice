#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=524288;
mt19937 mt(time(0));
int main(){
    freopen("set.in","w",stdout);
    cout<<"0\n";
    cout<<N<<'\n';
    for(int i=0;i<N;++i){
        cout<<mt()<<' ';
    }
    return 0;
}
