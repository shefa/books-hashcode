#include<bits/stdc++.h>
using namespace std;

#define DEBUG_PRINT 0
#define out if(DEBUG_PRINT)cout
#define endl '\n'
#define mp make_pair
#define pii pair<int,int>

/* Timing stuff */
double currentTime=0;
double deadline=CLOCKS_PER_SEC*60;
inline int getTime() { return currentTime=clock(); }

// Start here
int n,m;
vector<pii> p;
vector<pii> ans;

bool cmp(pii &x, pii &y){
	return x.first<y.first;
}

void greedy(){
	int l=0,r=0,s=0;
	int global_max=0;
	pii max_location=mp(0,0);

	while(r<=n){
		s+=p[r++].first;
		while(s>m) s-=p[l++].first;
		if(s<=m&&s>global_max){
			global_max=s;
			max_location=mp(l,r);
		}
	}

	for(int i=max_location.first;i<max_location.second;i++) ans.push_back(p[i]);
}

int dp(int x, int y, vector<int> &path){
	vector<int> pp,py;
	path=pp;
	if(y<0) return 0;
	if(x<0||y==0) return m-y;
	int v1=dp(x-1,y,pp);
	int v2=dp(x-1,y-p[x].first,py);
	path=pp;
	if(v1>=v2) return v1;
	py.push_back(x);
	path=py;
	return v2;
}

void dp(){
	out<<"start"<<endl;
	int ma3x[2][m+1];
	//int take[2][m+1];
	int tmp=0;
	for(int i=0;i<=m;i++){
		ma3x[0][i]=0;
		if(p[0].first<=i){
			ma3x[0][i]=p[0].first;
			//take[0][i]=1;
		}
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<=m;j++){
			int idx=i&1;
			int idy=idx^1;
			ma3x[idx][j] = ma3x[idy][j];
			tmp=0;
			if(p[i].first<=j) tmp=ma3x[idy][j-p[i].first]+p[i].first;
			if(ma3x[idx][j]<tmp) {
				ma3x[idx][j]=tmp;
				//take[j].set(i);
			}
		}
	}
	out<<ma3x[(n-1)&1][m]<<endl;
	/*
	int j=m;
	for(int i=n-1;i>=0;i--){
		if(take[i][j]){
			ans.push_back(p[i]);
			j-=p[i].first;
		}
	}*/
}

void optimize(){
	set<pii> x,y;
	pii t;
	int sumx=0,sumy=0, global=0;
	for(int i=0;i<p.size();i++){ x.insert(p[i]); sumx+=p[i].first;}
	for(int i=0;i<ans.size();i++){ x.erase(ans[i]); sumx-=p[i].first; y.insert(ans[i]); sumy+=ans[i].first;}
	global=sumy;
	while(getTime()<deadline){
		vector<pii> tmp;
		for(set<pii>::iterator i=x.begin();i!=x.end();i++){
			t=(*i);
			if( t.first+sumy <= m ){
				tmp.push_back(t);
				sumy+=t.first;
				sumx-=t.first;
				y.insert(t);
			}
			else break;
		}
		for(int i=0;i<tmp.size();i++) {
			x.erase(tmp[i]);
		}
		if(global<sumy){
			out<<"found better solution! "<<sumy<<" "<<global<<endl;
			global=sumy;
			ans.clear();
			for(set<pii>::iterator i=y.begin();i!=y.end();i++) ans.push_back(*i);
		}
		int which_one=(rand()%y.size())/2;
		int xi=0;
		for(set<pii>::reverse_iterator i=y.rbegin();i!=y.rend();i++,xi++){
			if(xi==which_one){
				x.insert(*i);
				sumx+=(*i).first;
				sumy-=(*i).first;
				y.erase(*i);
				break;
			}
		}
	}
}


void solve(){
	sort(p.begin(),p.end(),cmp);
	greedy();
	//vector<int> ans_p;
	//dp(n-1,m,ans_p);
	//for(int i=0;i<ans_p.size();i++) ans.push_back(p[ans_p[i]]);
	//greedy2();
	optimize();
}

int score(){
	int sum=0;
	for(int i=0;i<ans.size();i++) sum+=ans[i].first;
	return sum;
}

void output(){
	out<<score()<<"/"<<m<<endl;
	out<<getTime()<<endl;
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++) cout<<(i?" ":"")<<ans[i].second;
	cout<<endl;
}


void input(){
	cin>>m>>n;
	p.resize(n);
	for(int i=0;i<n;i++){ cin>>p[i].first; p[i].second=i;}
}

int main()
{
	input();
	solve();
	output();
	return 0;
}