//problem https://atcoder.jp/contests/abc222/tasks/abc222_g
#include<bits/stdc++.h>
using namespace std;

int pow(long long a,int n,int m){
	long long ans=1;
	a%=m;
	while(n){
		if(n%2)ans=ans*a%m;
		a=a*a%m;
		n/=2;
	}
	return (int)ans;
}

int phi(int n){
	int ans=n;
	for(int p=2;p*p<=n;p++)if(n%p==0){
		while(n%p==0)n/=p;
		ans-=ans/p;
	}
	if(n!=1)ans-=ans/n;
	return ans;
}

vector<int> divisor(int n){
	vector<int>div;
	for(int d=1;d*d<=n;d++)if(n%d==0){
		div.push_back(d);
		if(d!=n/d)div.push_back(n/d);
	}
	sort(div.begin(),div.end());
	return div;
}

int solve(int m){
	if(m%2==0)m/=2;
	m*=9;
	for(int d:divisor(phi(m)))if(pow(10,d,m)==1)return d;
	return -1;
}

int main(){
	int n;
	cin >> n;
	while(n--){
		int a;
		cin >> a;
		cout << solve(a) << endl;
	}
}
