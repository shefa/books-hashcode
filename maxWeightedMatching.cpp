#include<bits/stdc++.h>
using namespace std;

struct lib{
	int id;
	int n; //10^5
	int t; //signup
	int m; //capacity
	int totalBooks;
	unordered_set<int> lookupBooks;
	vector<int> books;
};
vector<int> books;
vector<lib> libs;

struct edge{
	int flow;
	int to;
	bool residual;
	edge(int f, int t, bool r){
		flow=f;
		to=t;
		residual=r;
	}
};

struct node{
	int val;
	unordered_map<int,edge> edges;
	node(int v){
		val=v;
	}
};

vector<node> graph;
vector<int> parent;
vector<bool> used;

void add_edge(int x, int y, int cap){
	graph[x].edges.insert(edge(cap,y,0));
	graph[y].edges.insert(edge(0,x,1));

}

bool bfs(){
	queue<pair<int,int> > q;
	q.push(make_pair(0,-1));
	fill(used.begin(),used.end(),0);
	fill(parent.begin(),parent.end(),-1);
	while(!q.empty()){
		int x=q.front().first;
		int p=q.front().second;
		q.pop();
		if(used[x]++) continue;
		parent[x]=p;
		if(x==graph.size()-1) return true;
		for(auto& e: graph[x].edges){
			if(!used[e.second.to]) q.push(make_pair(e.second.to,x));
		}
	}
	return false;
}

void maxflow(){
	int max_flow=0;
	used.resize(graph.size());
	parent.resize(graph.size());
	while(bfs()){
		int min_flow=graph[parent[graph.size()-1]].edges[graph.size()-1].second.flow;
		for(int v=parent[graph.size()-1];v!=0;v=parent[v]) min_flow=min(min_flow,graph[parent[v]].edges[v].second.flow);
		for(int v=graph.size()-1;v!=0;v=parent[v]){
			graph[parent[v]].edges[v].flow-=min_flow;
			graph[v].edges[parent[v]].flow+=min_flow;
		}
		max_flow+=min_flow;
	}
	return max_flow;
}

void build_graph(){
	graph.resize(2+books.size()+libs.size());
	graph.push_back(node(-1)); //source
	for(auto& i: books){ graph.push_back(node(i)); add_edge(0,graph.size()-1,1); }
	for(auto& i: libs){
		graph.push_back(node(0));
		for(auto& j: i.books) add_edge(j+1,graph.size()-1, 1);
	}
	graph.push_back(node(-1)); //sink
	for(int i=0;i<libs.size();i++) add_edge(i+1+books.size(),graph.size()-1,libs[i].);
}

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
	int time=0,cap=0;
	for(auto &i: libs){
		if(time+i.t>=d) {i.totalBooks=-1; continue;}
		i.totalBooks=(d-time-i.t)*i.m;
		time+=i.t;
	}
	vector<libs>
	for()
}

int main(){

}