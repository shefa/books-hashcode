#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define mp make_pair
#define pii pair<int,int>

struct node{
	int v;
	vector<int> edge;
	int cheat;
	node(int c){v=c; cheat=1<<27;}
};

int t,n;
vector<string> words;
node* graph[28];
bool visited[28];



/* Timing stuff */
double currentTime=0;
double deadline=CLOCKS_PER_SEC*4.5;
inline int getTime() { return currentTime=clock(); }

inline int cv(const char& x) { return (int)(x-'a'+1);}


void createGraph(){
	for(int i=0;i<28;i++) graph[i] = new node(i);
	for(auto& x:words){
		for(int i=0;i<x.size();i++){
			int y=i?cv(x[i-1]):0, z=cv(x[i]);
			if(!(graph[y]->cheat&(1<<z))){
				graph[y]->edge.push_back(z);
				graph[y]->cheat|=(1<<z);
			}
		}
		graph[cv(x[x.size()-1])]->edge.push_back(27);
	}
}

void printGraph(){
	memset(visited,0,sizeof(visited)*sizeof(bool));
	queue<pii> q;
	q.push(mp(0,0));
	int x,y;
	while(!q.empty()){
		x=q.front().first;
		y=q.front().second;
		q.pop();
		if(visited[x]++) continue;
		cout<<graph[x]->v<<"("<<char(graph[x]->v+'a'-1)<<") "<<y<<endl;
		for(auto& i:graph[x]->edge) q.push(mp(i,y+1));
	}
}

void solve(){
	createGraph();
	printGraph();
}

void output(){
	cout<<getTime()<<endl;
}

void init(){
	words.resize(n);
}

void input(){
	freopen("crossword.in","r",stdin);
	//freopen("crossword.out","w",stdout);
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin>>t>>n;
	init();
	for(int i=0;i<n;i++) cin>>words[i];
}

int main()
{
	input();
	solve();
	output();
	return 0;
}