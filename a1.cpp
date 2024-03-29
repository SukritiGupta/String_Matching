#include<vector>
#include<unordered_map>
#include<climits>
#include <fstream>

static unsigned long x=123456789, y=362436069, z=521288629;

// unsigned long xorshf96(void) {          //period 2^96-1
// unsigned long t;
//     x ^= x << 16;
//     x ^= x >> 5;
//     x ^= x << 1;

//    t = x;
//    x = y;
//    y = z;
//    z = t ^ x ^ y;

//   return z;
// }

using namespace std;

int costs[5][5];
int K;
int V;
int CC;
int totNi=0;
vector<string> vecstr;
vector<vector<int>> base;
unordered_map<char,int> mpchartoint;
unordered_map<int, char> mpintochar;
double timeforeach;

class searchspace
{
	public:
	int N, nodash;
	vector<vector<int>> w;
	vector<pair<int, int>> alldashes;
	searchspace(){};
	searchspace(int n)	
	{
		N=n;
		w=base;
		int temp;
		nodash=0;
		alldashes.clear();
		int del, siz;

		for (int i = 0; i < K ; ++i)
		{
			siz=w[i].size();
			del=N-siz;
			unsigned long t;
			nodash+=del;
			// vector<int>::iterator it=w[i].begin();
			for (int j = 0; j < del; ++j)
			{
				x ^= x << 16;
			    x ^= x >> 5;
			    x ^= x << 1;
				t = x;
				x = y;
				y = z;
				z = t ^ x ^ y;
				w[i].insert(w[i].begin()+(z%siz),V);
				siz++;
			}
		}

		for (int i = 0; i < K; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if(w[i][j]==V)
					alldashes.push_back(make_pair(i,j));
			}
		}
	}
};


// int eval(searchspace curr, int s, int p1, int p2)
// {
// 	int ret=0;
// 	for (int i = 0; i < K; ++i)
// 	{
// 		if(i==s)
// 			continue;
// 		ret+=costs[curr.w[i][p1]][curr.w[s][p2]]-costs[curr.w[i][p1]][curr.w[s][p1]]+costs[curr.w[i][p2]][curr.w[s][p1]]-costs[curr.w[i][p2]][curr.w[s][p2]];
// 	}
// 	return ret;
// }


int Totaleval(searchspace curr)
{
	int ret=0;
	for (int i = 0; i < K; ++i)
	{
		for (int j = i+1; j < K; ++j)
		{
			for (int k = 0; k < curr.N; ++k)
			{
				ret+=costs[curr.w[i][k]][curr.w[j][k]];
			}
		}
	}
	return ret;
}


searchspace findbest_forn(int don, int* val, time_t start)
{
	time_t now;
	int curreval, diff1,diff2;
	int diffglobe=0;
	int opteval=INT_MAX;
	searchspace optassign;
	unsigned long t;

	while(true)
	{
		searchspace a= searchspace(don);
		curreval=Totaleval(a)+ CC*(don*K-totNi);
		diffglobe=0;

		int temp=a.nodash/2;
		int s, j, pdash;
		while(diffglobe<=temp)
		{

			x ^= x << 16;
		    x ^= x >> 5;
		    x ^= x << 1;
			t = x;
			x = y;
			y = z;
			z = t ^ x ^ y;

		  	//return z;
			pdash= z%(a.nodash);
			time(&now);
			if(difftime(now,start)>=timeforeach)
				break;
			diff1=1;
			diff2=1;
			j=a.alldashes[pdash].second;
			s=a.alldashes[pdash].first;

			if(j>0 && a.w[s][j-1]!=V && j<don-1 && a.w[s][j+1]!=V)
			{
				// diff1=eval(a, s, j, j-1);
				diff1=0;
				diff2=0;
				for (int ii = 0; ii < K; ++ii)
				{
					diff1+=costs[a.w[ii][j]][a.w[s][j-1]]-costs[a.w[ii][j]][a.w[s][j]]+costs[a.w[ii][j-1]][a.w[s][j]]-costs[a.w[ii][j-1]][a.w[s][j-1]];
					diff2+=costs[a.w[ii][j]][a.w[s][j+1]]-costs[a.w[ii][j]][a.w[s][j]]+costs[a.w[ii][j+1]][a.w[s][j]]-costs[a.w[ii][j+1]][a.w[s][j+1]];
				
				}
			}
			else if(j<don-1 && a.w[s][j+1]!=V)
			{
					// diff2=eval(a,s,j,j+1);
				diff1=10;
				diff2=0;
				for (int ii = 0; ii < K; ++ii)
				{
					diff2+=costs[a.w[ii][j]][a.w[s][j+1]]-costs[a.w[ii][j]][a.w[s][j]]+costs[a.w[ii][j+1]][a.w[s][j]]-costs[a.w[ii][j+1]][a.w[s][j+1]];
				}
			}

			else if(j>0 && a.w[s][j-1]!=V)
			{
					// diff2=eval(a,s,j,j+1);
				diff1=0;
				diff2=10;
				for (int ii = 0; ii < K; ++ii)
				{
					diff1+=costs[a.w[ii][j]][a.w[s][j-1]]-costs[a.w[ii][j]][a.w[s][j]]+costs[a.w[ii][j-1]][a.w[s][j]]-costs[a.w[ii][j-1]][a.w[s][j-1]];
				}
			}

			if(diff1<diff2 && diff1<0)
			{
				a.w[s][j]=a.w[s][j-1];
				a.w[s][j-1]=V;
				curreval+=diff1;
				a.alldashes[pdash].second=j-1;
				diffglobe=0;
			}
			else if(diff2<diff1 && diff2<0)
			{
				a.w[s][j]=a.w[s][j+1];
				a.w[s][j+1]=V;
				curreval+=diff2;
				diffglobe=0;
				a.alldashes[pdash].second=j+1;
			}
			else
				diffglobe++;
		}
		if (opteval>curreval)
		{
			optassign=a;
			opteval=curreval;				
		}
		time(&now);
		if(difftime(now,start)>=timeforeach)
			break;
	}

	*val=opteval;
	return optassign;
	
}


int main(int argc, char const *argv[])
{
	time_t start, procstart, end;	
	time(&start);
	string second;
	float seconds;

	string in_file = argv[1];		fstream file1;			file1.open(in_file,ios::in);

	getline(file1,second);
	seconds=stof(second);
	seconds*=60;

	file1>>V;

	char c;
	for (int i = 0; i < V; ++i)
	{
		file1>>c;
		mpintochar[i]=c;
		mpchartoint[c]=i;
		if(i!=V-1)
			file1>>c;		
	}

	mpchartoint['-']=V;
	mpintochar[V]='-';

	file1>>K;


	vecstr.clear();			
	string s;
	int l;
	int maxNi=0;			
	for(int i=0;i<K;i++)
	{
		file1 >> s;	
		vecstr.push_back(s);
		l=s.length();
		totNi+=l;
		if (l>maxNi)
		{
			maxNi=l;
		}
	}


	file1>>CC;

	int temp;

	for (int i = 0; i < V+1; ++i)
	{
		for (int j = 0; j < V+1; ++j)
		{
			file1>>temp;
			costs[i][j]=temp;			
		}
	}


	file1>>c;
	int ll, ul;
	vector<int> singstr;

	for (int i = 0; i < K; ++i)
	{
		singstr.clear();
		ll=vecstr[i].length();
		for (int j = 0; j < ll; ++j)
		{
			singstr.push_back(mpchartoint[vecstr[i][j]]);			
		}
		base.push_back(singstr);
	}

	ll=maxNi;
	ul=(maxNi+totNi)/2;
	bool separate=false;
	int jump=1;
	int rounds=(ul-ll)/7; 

	if (rounds==0)
	{
		ul=totNi;
		rounds=(ul-ll)/7;
	}
	if (rounds==0)
	{
		separate=true;
	}
	searchspace finalwrite;

	if(!separate)
	{
		int diffntried=1+rounds*3; //use for time division of each n
		time(&procstart);
		double timeleft=difftime(start, procstart);
		timeleft+=seconds;
		double buffer=2+0.1*K;
		timeleft-=buffer>3?buffer:3;
		// timeleft-=5;

		timeforeach=timeleft/diffntried;
		int val;
		time_t now=procstart;
		// time(&now);
		finalwrite=findbest_forn(maxNi, &val, now);
		int bestofwrite=val;
		int donerounds=1;
		searchspace b;

		int doner=1;
		for (int i = maxNi+1; i <= ul; i+=jump)
		{
			if(donerounds==rounds)
			{
				donerounds=1;
				jump*=2;
			}
			else donerounds++;
	
			now=(double)now+timeforeach;
			b=findbest_forn(i, &val, now);
			if(val<bestofwrite)
			{
				bestofwrite=val;
				finalwrite=b;
			}
	
			doner++;
	
		}
	}
	else
	{
		int diffntried=1+ul-ll; //use for time division of each n
		time(&procstart);
		double timeleft=difftime(start, procstart);
		timeleft+=seconds;
		double buffer=2+0.1*K; 
		timeleft-=buffer>3?buffer:3;

		timeforeach=timeleft/diffntried;
		int val;
		time_t now=procstart;
		// time(&now);
		finalwrite=findbest_forn(maxNi, &val, now);
		int bestofwrite=val;
		searchspace b;

		for (int i = maxNi+1; i <= ul; i++)
		{
			now=(double)now+timeforeach;
			b=findbest_forn(i, &val, now);
			if(val<bestofwrite)
			{
				bestofwrite=val;
				finalwrite=b;
			}
		}
	}





	fstream fl;			fl.open(argv[2],ios::out);

	for (int i = 0; i < K; ++i)
	{
		for (int j = 0; j < finalwrite.w[i].size(); ++j)
		{
			fl<<mpintochar[finalwrite.w[i][j]];
		}
		fl<<endl;
	}
}