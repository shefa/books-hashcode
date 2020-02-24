#include<bits/stdc++.h>
using namespace std;

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
	set<int> books;
	vector<int> booksOrdered;
};


int b, l, d;
vector<int> books;
vector<lib> libs;
vector<lib> ans;

bool greedy1(const lib &x, const lib &y){
	std::set<int> result;
	std::set_difference(x.books.begin(), x.books.end(), y.books.begin(), y.books.end(),
    std::inserter(result, result.end()));
    return result.size()/(x.m*x.t) > (y.books.size()-(x.books.size()-result.size()))/(y.m*y.t);
}

bool greedy2(const lib &x, const lib &y){
	int score1=0, score2=0;
	ans.resize(2);
}

void solve(){
	out<<"solving, "<<libs.size()<<endl;
	sort(libs.begin(),libs.end(),greedy1);
	out<<"test, "<<libs.size()<<endl;
	ans.resize(libs.size());
	for(int i=0;i<libs.size();i++){
		ans[i]=libs[i];
		for(set<int>::iterator it=ans[i].books.begin(); it!=ans[i].books.end(); it++) ans[i].booksOrdered.push_back(*it);
	}
}

int score(){
	unordered_set<int>x;
	int sum=0;
	int time=0;
	for(int i=0;i<ans.size();i++){
		time+=ans[i].t;
		for(int j=0;j<ans[i].booksOrdered.size();j++){
			if(time+(j/ans[i].m)==d) break;
			if(x.find(ans[i].booksOrdered[j])==x.end()){
				x.insert(ans[i].booksOrdered[j]);
				sum+=books[ans[i].booksOrdered[j]];
			}
		}
	}
	return sum;
}

void output(){
	out<<"score:"<<score()<<endl<<getTime()<<endl;
	if(DEBUG_PRINT) return;
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		cout<<ans[i].id<<" "<<ans[i].booksOrdered.size()<<endl;
		for(int j=0;j<ans[i].booksOrdered.size();j++)
		{
			cout<<(j?" ":"")<<ans[i].booksOrdered[j];
		}
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
		for(int j=0;j<libs[i].n;j++) {
			int tmp;
			cin>>tmp;
			libs[i].books.insert(tmp);
		}
	}
}

int main()
{
	input();
	solve();
	output();
	return 0;
}