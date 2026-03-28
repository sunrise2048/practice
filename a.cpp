#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>
using namespace std;
const int N=50;
const int M=15;
int n,m,k,mod;
string s;
class SOL0{
public:
	void sol(){
		int be=(n-k)/2;
		int ed=be+k-1;
		//cout<<be<<' '<<ed<<'\n';
		int liml=0,limr=0,limz=0;
		for(int i=0;i<be;++i){
			if(s[i]!='0')++liml;
		}
		for(int i=be;i<=ed;++i){
			if(s[i]!='0')++limz;
		}
		for(int i=ed+1;i<n;++i){
			if(s[i]!='0')++limr;
		}
		vector<vector<vector<vector<vector<int>>>>> f(2,vector<vector<vector<vector<int>>>>(m+1,vector<vector<vector<int>>>(liml+1,vector<vector<int>>(limr+1,vector<int>(limz+1,0)))));
		limr=limz=0;
		int lim=0;
		if(s[be]!='1'){
			const int nop=be&1;
			for(int nl=liml;nl>=0;--nl){
				if(nl*(nl-1)/2>m)continue;
				f[nop][nl*(nl-1)/2][nl][0][0]=1;
			}
			lim=min(liml*(liml-1)/2,m);
		}
		if(s[be]!='0'){
			limz=1;
			const int nop=be&1;
			for(int nl=liml;nl>=0;--nl){
				if(nl*(nl+1)/2>m)continue;
				f[nop][nl*(nl+1)/2][nl][0][1]=1;
			}
			lim=min(liml*(liml+1)/2,m);
		}
		for(int i=be+1;i<=ed;++i){
			const int op=i&1;
			for(int ncn=0;ncn<=lim;++ncn){
				for(int nl=0;nl<=liml;++nl){
					for(int nr=0;nr<=limr;++nr){
						for(int nz=0;nz<=limz;++nz){
							f[op][ncn][nl][nr][nz]=0;
						}
					}
				}
			}
			int lop=(i-k<0?0:(s[i-k]=='?'?2:s[i-k]-'0')),rop=(i+k-1<n?(s[i+k-1]=='?'?2:s[i+k-1]-'0'):0);
			for(int lcn=0;lcn<=lim;++lcn){
				for(int ll=0;ll<=liml;++ll){
					for(int lr=0;lr<=limr;++lr){
						for(int lz=0;lz<=limz;++lz){
							if(!f[op^1][lcn][ll][lr][lz])continue;
							for(int opl:{0,1}){
								if(lop!=2&&opl!=lop)continue;
								if(opl&&ll==0)continue;
								for(int opr:{0,1}){
									if(rop!=2&&opr!=rop)continue;
									for(int opz:{0,1}){
										if(s[i]!='?'&&opz!=s[i]-'0')continue;
										int ncn=lcn+opz*(ll-opl+lr+opr+lz)+opr*lr;
										//cout<<lcn<<' '<<ll<<' '<<lr<<' '<<lz<<'\n';
										//cout<<opl<<' '<<opr<<' '<<opz<<' '<<ncn<<'\n';
										if(ncn>m)continue;
										lim=max(lim,ncn);
										f[op][ncn][ll-opl][lr+opr][lz+opz]+=f[op^1][lcn][ll][lr][lz];
										f[op][ncn][ll-opl][lr+opr][lz+opz]>=mod?f[op][ncn][ll-opl][lr+opr][lz+opz]-=mod:0;
									}
								}
							}
						}
					}
				}
			}
			if(lop!=0)--liml;
			if(rop!=0)++limr;
			if(s[i]!='0')++limz;
		}
		for(int i=0;i<=m;++i){
			int s=0;
			for(int cnr=0;cnr<=limr;++cnr){
				for(int cnz=0;cnz<=limz;++cnz){
					s+=f[ed&1][i][0][cnr][cnz];
					s>=mod?s-=mod:0;
				}
			}
			cout<<s<<' ';
		}
	}
}sol_poly;
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
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k>>mod;
	cin>>s;
	if(3*k-2>=n){
		sol_poly.sol();
		return 0;
	}
	if(k<16){
		sol_nopoly.sol();
		return 0;
	}
	sol_wmy.sol();
	return 0;
}
/*
g++ -o network network.cpp -O2 -std=c++14 && time ./network
*/