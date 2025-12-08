#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
string s;
string t;
int main(){
    cin>>s;
    int sm=0;
    reverse(s.begin(),s.end());
    for(char c:s){
        sm+=(c-'0')*21;
        t.push_back('0'+(sm&1));
        sm/=2;
    }
    while(sm){
        t.push_back('0'+(sm&1));
        sm/=2;
    }
    reverse(t.begin(),t.end());
    cout<<t;
    return 0;
}