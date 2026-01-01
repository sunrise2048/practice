#include<bits/stdc++.h>
using namespace std;
using ll=long long;
vector<int> ans;
int cn;
void solve(ll k){
    if(k<=4){
        while(--k){
            ans.insert(ans.begin(),cn);
            ++cn;
        }
        return;
    }
    if(k%2==0){
        solve(k/2);
        ans.push_back(cn);
        ++cn;
    }
    else if(k%4==1){
        solve(k-1);
        ans.insert(ans.begin(),cn);
        ++cn;
    }
    else{
        solve(k-3);
        ans.insert(ans.begin()+2,cn);
        ++cn;
    }
}
vector<int> construct_permutation(ll k){
    ans.clear();
    cn=0;
    solve(k);
    return ans;
}