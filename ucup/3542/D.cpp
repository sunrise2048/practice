#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n,x;
int a[N];
set<int> st;
int cn;
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(st.count(a[i])||st.size()!=x-1){
			st.insert(a[i]);
		}
		else{
			st.clear();++cn;
			st.insert(a[i]);
		}
	}
	cout<<n-cn-1<<'\n';
	return 0;
}