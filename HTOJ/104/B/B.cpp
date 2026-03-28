#include<bits/stdc++.h>
using namespace std;
const int N=50;
const int M=15;
int n,m,k,mod;
string s;
class SOL1{
public:
	int f[2][N*N/2][1<<M];
	int t[N*N/2];
	void sol(){
		if(k==1){
			int ans=1;
			for(int i=0;i<n;++i){
				if(s[i]=='?'){
					ans=ans*2%mod;
				}
			}
			for(int i=0;i<=m;++i){
				if(i==0)cout<<ans<<' ';
				else cout<<"0 ";
			}
			return;
		}
		int z1=0,z0=0;
		for(int i=0;i<k-1;++i){
			if(s[i]=='0')z0|=(1<<i);
			if(s[i]=='1')z1|=(1<<i);
		}
		for(int z=0;z<(1<<k-1);++z){
			if((z0&z)!=0||(z1&z)!=z1)continue;
			int cn=__builtin_popcount(z);
			if(cn*(cn-1)/2>m)continue;
			f[k&1][cn*(cn-1)/2][z]=1;
		}
		int lim=min((k-1)*(k-2)/2,m);
		for(int id=k-1;id<n;++id){
			const int op=id&1;
			for(int cn=0;cn<=lim;++cn){
				memset(f[op][cn],0,sizeof(int)*(1<<k-1));
			}
			for(int lcn=0;lcn<=lim;++lcn){
				for(int lz=0;lz<(1<<k-1);++lz){
					if(f[op^1][lcn][lz]==0)continue;
					if(s[id]!='1'){
						f[op][lcn][lz>>1]+=f[op^1][lcn][lz];
						f[op][lcn][lz>>1]>=mod?f[op][lcn][lz>>1]-=mod:0;
					}
					if(s[id]!='0'){
						int ncn=lcn+__builtin_popcount(lz);
						if(ncn>m)continue;
						f[op][ncn][(lz>>1)|(1<<k-2)]+=f[op^1][lcn][lz];
						f[op][ncn][(lz>>1)|(1<<k-2)]>=mod?f[op][ncn][(lz>>1)|(1<<k-2)]-=mod:0;
					}
				}
			}
			lim=min(lim+k,m);
		}
		const int nop=(n-1)&1;
		for(int i=0;i<=m;++i){
			int s=0;
			for(int nz=0;nz<(1<<k-1);++nz){
				s+=f[nop][i][nz];
				s>=mod?s-=mod:0;
			}
			cout<<s<<' ';
		}
	}
}sol_nopoly;
class SOL2{
public:
	int bs[N];
	int f[2][12290][1226];
	void sol(){
		bs[0]=1;
		const int kc=(n-1+k)/k;
		for(int i=1;i<kc;++i)bs[i]=bs[i-1]*k;
		for(int i=0;i<n;++i){
			if(i%k!=k-1)bs[kc]+=bs[i/k];
		}
		bs[kc]+=2;
		int op=1;
		f[1][0][0]=1;
		for(int ls=0;ls<k;++ls){
			for(int kid=0;kid<kc;++kid){
				int nid=kid*k+ls;
				if(nid>n-1)continue;
				bool nop=(nid%k!=k-1);
				int np=(s[nid]=='?'?2:s[nid]-'0');
				op^=1;
				for(int lz=bs[kc]-1;lz>=0;--lz){
					int tcn=(lz/bs[kid])%k;
					if(kid!=kc-1)tcn+=(lz/bs[kid+1])%k;
					for(int ls=m;ls>=0;--ls){
						f[op][lz][ls]=0;
						if(f[op^1][lz][ls]==0)continue;
						if(np!=1){
							f[op][lz][ls]+=f[op^1][lz][ls];
							f[op][lz][ls]>=mod?f[op][lz][ls]-=mod:0;
						}
						if(np==0||ls+tcn>m)continue;
						int ts=ls+tcn;
						int tz=lz+(nop?bs[kid]:0);
						f[op][tz][ts]+=f[op^1][lz][ls];
						f[op][tz][ts]>=mod?f[op][tz][ts]-=mod:0;
					}
				}
			}
		}
		for(int i=0;i<=m;++i){
			int s=0;
			for(int z=0;z<bs[kc];++z){
				s+=f[op][z][i];
				s>=mod?s-=mod:0;
			}
			cout<<s<<' ';
		}
	}
}sol_wmy;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k>>mod;
	cin>>s;
	if(k<16){
		sol_nopoly.sol();
		return 0;
	}
	sol_wmy.sol();
	return 0;
}