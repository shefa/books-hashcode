#include<bits/stdc++.h>
using namespace std;

#define ANNEALING_FEED 1
#define DEBUG_PRINT 1
#define out if(DEBUG_PRINT)cout
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
	vector<int> booksOrdered;
};


int b,l,d;
vector<int> books;
vector<lib> libs, libsOrig, ans;

bool sortByScore(const int  &x, const int &y){ return books[x]>books[y]; }

int score(vector<lib> &libs2){
	unordered_set<int>xx;
	int sum=0,time=0,maxBooks;
	for(int i=0;i<libs2.size();i++){
		libs2[i].booksOrdered.clear();
		if(time+libs2[i].t>=d) continue;
		for(int j=0;j<libs2[i].books.size();j++) if(xx.insert(libs2[i].books[j]).second) libs2[i].booksOrdered.push_back(libs2[i].books[j]);
		if(libs2[i].booksOrdered.size()){
			//sort(libs2[i].booksOrdered.begin(),libs2[i].booksOrdered.end(),sortByScore);
			time+=libs2[i].t;
			maxBooks=(d-time)*libs2[i].m;
			if(maxBooks<libs2[i].booksOrdered.size()){
				for(int j=maxBooks;j<libs2[i].booksOrdered.size();j++){
					xx.erase(libs2[i].booksOrdered[j]);
				}
				libs2[i].booksOrdered.resize(maxBooks);
			}
			//for(int j=0;j<libs2[i].booksOrdered.size();j++) x.insert(libs2[i].booksOrdered[j]);
		}
		//we can reinsert the books that current library cannot process (after D days) so next libraries can attempt to process them
		//actually gives less score? try me
	}
	for(unordered_set<int>::iterator it=xx.begin();it!=xx.end();it++) sum+=(books[*it]);
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

void greedy(int type){
	if(type==0) return sort(libs.begin(),libs.end(),greedy1);
	if(type==1) return sort(libs.begin(),libs.end(),greedy2);
	return sort(libs.begin(),libs.end(),greedy3);
}

void solve(){
	copy(libs.begin(),libs.end(),back_inserter(libsOrig));
	int max_score=0,sc=0;
	for(int i=0;i<3;i++){
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

void printState(){ for(int i=0;i<ans.size();i++) cout<<ans[i].id<<" "; cout<<endl; }

void output(){
	if(ANNEALING_FEED) return printState();
	out<<"score:"<<score(ans)<<endl<<getTime()<<endl;
	if(DEBUG_PRINT) return;
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		if(ans[i].booksOrdered.size()==0) continue;
		cout<<ans[i].id<<" "<<ans[i].booksOrdered.size()<<endl;
		for(int j=0;j<ans[i].booksOrdered.size();j++)
			cout<<(j?" ":"")<<ans[i].booksOrdered[j];
		cout<<endl;
	}
}


void input(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin>>b>>l>>d;
	books.resize(b);
	libs.resize(l);
	for(int i=0;i<b;i++) cin>>books[i];
	for(int i=0;i<l;i++){
		libs[i].id=i;
		cin>>libs[i].n>>libs[i].t>>libs[i].m;
		for(int j=0,xxx;j<libs[i].n;j++) {
			cin>>xxx; if(libs[i].lookupBooks.insert(xxx).second) libs[i].books.push_back(xxx);
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