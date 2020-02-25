#include<bits/stdc++.h>
using namespace std;

#define ANNEALING_FEED 0
#define DEBUG_PRINT 1
#define endl '\n'
#define mp make_pair
#define pii pair<int,int>


/* Timing stuff */
double currentTime=0;
double deadline=CLOCKS_PER_SEC*4.5;
inline int getTime() { return currentTime=clock(); }


struct lib{
	int id;
	int n; //10^5
	int t; //signup
	int m; //capacity
	unordered_set<int> lookupBooks;
	vector<int> books;
};

bool final=0;
int d;
vector<int> books;
vector<lib> libs, libsOrig, ans;
unordered_set<int> globalThing;

int score(vector<lib> &libs2){
	unordered_set<int>x;
	int sum=0,time=0,cap=0,b=0;
	for(auto &i: libs2){
		if(time+i.t>=d) continue;
		cap=(d-time-i.t)*i.m;
		b=0;
		for(auto &j: i.books) if(x.insert(j).second&&++b==cap) break;
		if(b) time+=i.t;
	}
	for(auto& i:x) if(globalThing.find(i)==globalThing.end()) sum+=books[i];
	return sum;
}

bool greedy1(const lib &x, const lib &y){
	int result=0;
	for(const auto& it: x.lookupBooks) result+=y.lookupBooks.find(it)==y.lookupBooks.end();
    return result/(x.m*x.t) > (y.books.size()-(x.books.size()-result))/(y.m*y.t);
}

bool greedy2(const lib &x, const lib &y){
	int result=0;
	for(const auto& it: x.lookupBooks) result+=y.lookupBooks.find(it)==y.lookupBooks.end();
    return ((result/(x.m))-x.t) > (((y.books.size()-(x.books.size()-result))/(y.m))-y.t);
}

bool greedy3(const lib &x, const lib &y){
	int score1=0, score2=0;
	vector<lib> t(2);
	t[0]=x;
	t[1]=y;
	score1=score(t);
	t[0]=y;
	t[1]=x;
	score2=score(t);
	return score1>score2;
}

void iterative_greedy(){
	int d_orig=d, cap=0,b=0;
	for(int i=0;i<libs.size();i++){
		for(int j=i+1;j<libs.size();j++){
			if(greedy3(libs[i],libs[j])) swap(libs[i],libs[j]);
		}
		d-=libs[i].t;
		b=0; cap=d*libs[i].m;
		for(auto& j: libs[i].books) if(globalThing.insert(j).second&&++b==cap) break;
	}
	globalThing.clear();
	d=d_orig;
}

void greedy(int type){
	if(type==0) return sort(libs.begin(),libs.end(),greedy1);
	if(type==1) return sort(libs.begin(),libs.end(),greedy2);
	if(type==3) return iterative_greedy();
	return sort(libs.begin(),libs.end(),greedy3);
}

void solve(){
	copy(libs.begin(),libs.end(),back_inserter(libsOrig));
	int max_score=0,sc=0;
	for(int i=3;i<=3;i++){
		greedy(i);
		sc=score(libs);
		if(max_score<sc){
			ans.clear();
			copy(libs.begin(),libs.end(),back_inserter(ans));
			max_score=sc;
		}
		libs.clear();
		copy(libsOrig.begin(),libsOrig.end(),back_inserter(libs));
	}
}

void make_ans(){
	unordered_set<int>x;
	vector<int> ids;
	vector<vector<int> > res;
	int time=0,cap=0,b=0;
	for(auto &i: ans){
		if(time+i.t>=d) continue;
		cap=(d-time-i.t)*i.m;
		b=0;
		vector<int> temp;
		for(auto &j: i.books) if(x.insert(j).second){
			temp.push_back(j);
			if(++b==cap) break;
		}
		if(b) {time+=i.t; ids.push_back(i.id); res.push_back(temp);}
	}
	cout<<res.size()<<endl;
	for(int i=0;i<res.size();i++){
		cout<<ids[i]<<" "<<res[i].size()<<endl;
		for(int j=0;j<res[i].size();j++)
			cout<<(j?" ":"")<<res[i][j];
		cout<<endl;
	}
}

void printState(){ for(int i=0;i<ans.size();i++) cout<<ans[i].id<<" "; cout<<endl;}
void printScore(){ cout<<"score:"<<score(ans)<<endl<<getTime()<<endl; }

void output(){
	if(ANNEALING_FEED) return printState();
	if(DEBUG_PRINT) return printScore();
	make_ans();
}

bool sortByScore(const int  &x, const int &y){ return books[x]>books[y]; }

void input(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin.sync_with_stdio(0);
	cin.tie(0);
	int b,l;
	cin>>b>>l>>d;
	books.resize(b);
	libs.resize(l);
	for(int i=0;i<b;i++) cin>>books[i];
	for(int i=0;i<l;i++){
		libs[i].id=i;
		cin>>libs[i].n>>libs[i].t>>libs[i].m;
		for(int j=0,x;j<libs[i].n;j++) {
			cin>>x; 
			if(libs[i].lookupBooks.insert(x).second) libs[i].books.push_back(x);
		}
		sort(libs[i].books.begin(),libs[i].books.end(),sortByScore);
	}
}

int main()
{
	input();
	solve();
	output();
	return 0;
}