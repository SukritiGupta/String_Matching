#include <bits/stdc++.h>

static unsigned long x=123456789, y=362436069, z=521288629;

unsigned long xorshf96(void) {          //period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}

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
	int N;
	vector<vector<int>> w;
	searchspace(){};
	searchspace(int n)	
	{
		N=n;
		w=base;

		int del, siz;
		for (int i = 0; i < K ; ++i)
		{
			siz=w[i].size();
			del=N-siz;
			vector<int>::iterator it=w[i].begin();
			for (int j = 0; j < del; ++j)
			{
				w[i].insert(w[i].begin()+(xorshf96()%siz),V);
				siz++;
			}
		}
	}
};


int eval(searchspace curr, int s, int p1, int p2)
{
	int ret=0;
	for (int i = 0; i < K; ++i)
	{
		if(i==s)
			continue;
		ret+=costs[curr.w[i][p1]][curr.w[s][p2]]-costs[curr.w[i][p1]][curr.w[s][p1]];
		ret+=costs[curr.w[i][p2]][curr.w[s][p1]]-costs[curr.w[i][p2]][curr.w[s][p2]];
	}
	return ret;
}


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
	int diffglobe=3;

	// bool timeover=true;

	int opteval=INT_MAX;
	searchspace optassign;

	while(true)
	{
		searchspace a= searchspace(don);
		curreval=Totaleval(a)+ CC*(don*K-totNi);
		diffglobe=3;
		while(diffglobe!=0)
		{
			diffglobe=0;
			for (int i = 0; i < K; ++i)
			{
				for (int j = 0; j < don; ++j)
				{
					time(&now);
					if(difftime(now,start)>=timeforeach)
						break;
					diff1=100;
					diff2=100;
					if(a.w[i][j]==V+1)
					{

						if(j>0)
						{
							if(a.w[i][j-1]!=V)
								diff1=eval(a, i, j, j-1);
						}
						if(j<don-1)
						{
							if(a.w[i][j+1]!=V)
								diff2=eval(a,i,j,j+1);
						}
						if(diff1<diff2 && diff1<0)
						{
							a.w[i][j]=a.w[i][j-1];
							a.w[i][j-1]=V;
							curreval+=diff1;
							diffglobe++;
						}
						else if(diff2<diff1 && diff2<0)
						{
							a.w[i][j]=a.w[i][j+1];
							a.w[i][j+1]=V;
							curreval+=diff2;
							diffglobe++;
						}
					}
				}
			}
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

	cout<<endl<<don<<"  "<<opteval<<endl;

	*val=opteval;
	return optassign;
	
}


int main()
{
	time_t start, procstart, end;	
	time(&start);
	string second;
	float seconds;
	getline(cin,second);
	seconds=stof(second);
	seconds*=60;

	cin>>V;

	char c;
	for (int i = 0; i < V; ++i)
	{
		cin>>c;
		mpintochar[i]=c;
		mpchartoint[c]=i;
		cin>>c;		
	}

	mpchartoint['-']=V;
	mpintochar[V]='-';

	K=c-'0';

	vecstr.clear();			
	string s;
	int l;
	int maxNi=0;			
	for(int i=0;i<K;i++)
	{
		cin >> s;	
		vecstr.push_back(s);
		l=s.length();
		totNi+=l;
		if (l>maxNi)
		{
			maxNi=l;
		}
	}


	cin>>CC;

	int temp;

	for (int i = 0; i < V+1; ++i)
	{
		for (int j = 0; j < V+1; ++j)
		{
			cin>>temp;
			costs[i][j]=temp;			
		}
	}


	cin>>c;
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

	int jump=1;
	int rounds=(ul-ll)/7; //****************what if this is 0????????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int diffntried=1+rounds*3; //use for time division of each n
	time(&procstart);
	double timeleft=difftime(start, procstart);
	timeleft+=seconds;
	timeleft-=5;

	timeforeach=timeleft/diffntried;


	int val;
	time_t now;
	time(&now);
	searchspace finalwrite=findbest_forn(maxNi, &val, now);
	int bestofwrite=val;
	int donerounds=1;
	searchspace b;

	int doner=1;

	for (int i = maxNi+1; i <= ul; i+=jump)
	{
		// if(doner>=diffntried)
		// {
		// 	cout<<"check!!!!";
		// 	break;
		// }
		if(donerounds==rounds)
		{
			donerounds=1;
			jump*=2;
		}
		else donerounds++;

		time(&now); //****************************************88change to start + something
		b=findbest_forn(i, &val, now);
		if(val<bestofwrite)
		{
			bestofwrite=val;
			finalwrite=b;
		}

		doner++;

		// cout<<i<<"   "<<val<<endl;
	}
















	cout<<bestofwrite<<endl;
	for (int i = 0; i < K; ++i)
	{
		for (int j = 0; j < finalwrite.w[i].size(); ++j)
		{
			cout<<mpintochar[finalwrite.w[i][j]];
		}
		cout<<endl;
	}
}