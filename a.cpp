/*in
3
6
U, I, S, O, Q, M
8
UQ
UUSMMQSI
SIUI
IIOOUIQMI
UIMUMOU
OMMOMQ
UOUMQUSQ
OQQIIM
0
0 5 11 13 16 19 2 
5 0 16 4 14 5 14 
11 16 0 17 19 11 0 
13 4 17 0 8 19 3 
16 14 19 8 0 19 1 
19 5 11 19 19 0 19 
2 14 0 3 1 19 0 
#

*/

//tranpose array for strings
#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
using namespace std;

class st{
public:
	int N;
	vector<vector<int>> w;

	st(){

	}

	st(vector<string> v,int n){
		N=n;
		for(int i=0;i<v.size();i++){
			vector<int> a;		string s1 = v.at(i);
			for(int j=0;j<N;j++){
				if(j<s1.size()){a.push_back(j);}
				else {a.insert(a.begin()+(rand()%a.size()),-1);}
			}
			w.push_back(a);
		}
	}
};

struct transtn{
	int sid,p1,p2; 
};

unordered_map<string,int> mp;
vector<string> k;	int cc;

void print(st a){
	vector<vector<int>> v=a.w;

	for(int i=0;i<v.size();i++){
		vector<int> v1 = v.at(i);
		for(int j=0;j<v1.size();j++){
			if(v1.at(j)==-1)cout << "-";
			else cout << k.at(i)[v1.at(j)] << "";
		}
		cout <<"\n";
	}
}

int cost(int i,int j, int a,int b){
	string key="";
	string s1 = k.at(i);		string s2 = k.at(j);
	if(a==-1)key+="-";		else key+=s1[a];
	if(b==-1)key+="-";		else key+=s2[b];
	return mp[key];
}

int eval(st a){
	int cst=0;
	int n = a.N;
	vector<std::vector<int>> v = a.w;
	for(int i=0;i<v.size()-1;i++){
		for(int j=i+1;j<v.size();j++){
			for(int k=0;k<n;k++)cst+=(	cost(i,j,v.at(i).at(k),v.at(j).at(k))	);
		}
		cst+=((n - k.at(i).size())*cc);
	}
	cst+=((n - k.at(v.size()-1).size())*cc);
	return cst;
}

st rnd_restart(st a){
	st b = st(k,a.N);
	return b;
}

st newstat(st a, struct transtn b){
	st nw = st();	nw.w = a.w;		nw.N = a.N; 
	
	int temp = nw.w.at(b.sid).at(b.p1);		nw.w.at(b.sid).at(b.p1) = nw.w.at(b.sid).at(b.p2);		nw.w.at(b.sid).at(b.p2) = temp;
	return nw;
}

st nextstate(st a){
	vector<vector<int>> v = a.w;		st nxt = st();			nxt=a;		int min = eval(a);
	
	for(int i=0;i<v.size();i++){
		vector<int> v1 = v.at(i);
		
		for(int j=0;j<v1.size();j++){
			if(v1.at(j)==-1){
				if(j!=v1.size()-1){
					transtn t = {i, j, j+1};	st temp = st();		temp = newstat(a,t);	 
					int u = eval(temp);			if(u<min){	min = u;	nxt=temp;	}
				}
				if(j!=0){
					transtn t = {i, j, j-1};	st temp = st();		temp = newstat(a,t);	 
					int u = eval(temp);			if(u<min){	min = u;	nxt=temp;	}
				}
			}
		}
	}

	return nxt;
}

void printv(vector<string> v){
	for(int i=0;i<v.size();i++)cout << v.at(i) << " ";
	cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);	cin.tie(NULL);
	time_t start, end;		
	mp.clear();
	float minutes;		cin >> minutes;		int sec = (int)(60* minutes);
	int V;				cin >> V;			int v=V;							string grbg;				getline(cin,grbg);
	string vcb;			getline(cin,vcb);	vector<char> voc;					for(int i=0;v>0;i+=3,v--)voc.push_back(vcb[i]);
	int K;				cin >> K;
	k.clear();			string s;			for(int i=0;i<K;i++){cin >> s;	k.push_back(s);}   
	cc=0;				cin >> cc;			int e=0;	
	for(int i=0;i<=V;i++){
		for(int j=0;j<=V;j++){
			cin >> e;	string s1="";
			if(i<V)s1+=voc.at(i);		else s1+="-";
			if(j<V)s1+=voc.at(j);		else s1+="-";	
			mp[s1]=e;	
		}
	}	char c;				cin >> c;
	
	time(&start); 

	int minN = INT_MIN;		int maxN = 0;
	for(int i=0;i<K;i++){int l = k.at(i).size(); minN = max(minN,l);	maxN+=l;}	
	maxN = maxN;
	
	time(&end);		double te = double(end-start);		st a = st(k,minN);

	int prev = eval(a);		int min = prev;		st o = st();		int tc = sec/(maxN-minN+1);

	for(int d=0;d<=(maxN-minN);d++){
		a = st(k,d+minN);
		int ccc=0;
		
		st o1 = st();	int min1=eval(a);
		while(te<(d+1)*tc){
			a = nextstate(a);
			int nxt = eval(a);
			if(nxt<min1){
				min1 = nxt;	o1=a;
			}
			if(nxt<min){
				min = nxt;	o=a;
			}
			if(nxt==prev){
				a = rnd_restart(a);
				nxt = eval(a);ccc++;
			}
			prev = nxt;
			time(&end);
			te = double(end-start);
		}	
		cout << d+minN << " "<<eval(o1)<<" "<< ccc << "\n";
		print(o1);
	}

	print(o);
	cout << eval(o) << "\n";
}