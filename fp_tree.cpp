#include<bits/stdc++.h>
#define per 23
#define it 5
using namespace std;
typedef
struct tree
{
	tree *d[it];
	int count=1;
	// node count
	int key=0;
	// node value
	int child=0;
	// counting the no of children to the present node
	tree *next;
}*fptr;
fptr l[it];
vector<int>v,vect;
void create(fptr &t,vector<int>&x,int m)
{
	if(m<x.size())
	{
		int i=0;
		for(i=0;i<t->child;i++)
		if((t->d[i]->key==x[m]))
		break;
		fptr p;
		p=l[x[m]-1];							// m is index here and the values are x[m]
		if(i==t->child)
		{
			t->d[t->child]=new tree();
			t->d[t->child]->key=x[m];
			while((p->next)&&(p!=t->d[t->child]))
			p=p->next;							//	be careful with the cyclic pointers they are dangerous in future they can be pointed back which are included already
			if(p!=t->d[t->child])
			p->next=t->d[t->child];
			delete(p);
			create(t->d[t->child++],x,m+1);		//	as the child count is 1 when no of child is 1 but in array we have to supply as 0
		}
		else
		{
			t->d[i]->count++;
			while(p->next&&p!=t->d[i])
			p=p->next;
			if(p!=t->d[i])
//			p->next=t->d[i];					// ?
			delete(p);
			create(t->d[i],x,m+1);					// here as i starts from 0 no problem
		}
	}
}
//void check(fptr &t,fptr &p)
//{
//	int i=0;
//	static int j=0;		// As the range of the static is throughout the function j is remaining 1 only we need to change after a while in fpgrowth function
//	for(i=0;i<t->child;i++)
//	{
//		if(t->d[i]!=p)
//		{
//			vect.push_back(t->d[i]->key);
//			check(t->d[i],p);
//			if(j!=1)
//			{
//				cout<<vect[vect.size()-1]<<endl;
//				vect.erase(vect.begin()+vect.size()-1);
//			}
//			else
//			{
//				if(t->key==0)
//				j=0;
//				cout<<" j is "<<j<<endl;
//				return;
//			}
////			cout<<t->d[i]->key<<" ";
//		}
//		else
//		{
//			if(vect.size()!=0&&t->key!=0)
//			vect.push_back(t->d[i]->count);
////			cout<<t->key<<" hii "<<endl;
//			j=1;
//		}
//	}
//}
//void fpgrowth(fptr &t)
//{
//	reverse(v.begin(),v.end());
//	int i=0,j=0;
//	vector<vector<int> >pb[it],cp[it],fp[it];
//	fptr p;
//	for(i=0;i<v.size()-1;i++)						//	As it is not required for the last one 
//	{
//		p=l[v[i]-1]->next;
//		while(p)
//		{
//			check(t,p);
//			pb[v[i]-1].push_back(vect);
//			for(j=0;j<vect.size()-1;j++)
//			cout<<vect[j]<<" ";
//			cout<<endl;
//			vect.clear();
//			p=p->next;
//		}
//	}
//	
//}
bool sor(pair<int,int>&a,pair<int,int>&b)
{
	return(a.second>b.second);						//	descending order so > symbol and second is used for sorting based on second type of elements
}
void print(fptr &t,vector<int>&vect)
{
	int i=0;
	for(i=0;i<t->child;i++)
	{
//		cout<<t->d[i]->key<<" "<<t->d[i]->count<<" ";
		vect.push_back(t->d[i]->key);
		print(t->d[i],vect);
	}
		if(t->d[i]==NULL)
		{
			int j=0;
			for(j=0;j<vect.size();j++)
			cout<<vect[j]<<" ";
			cout<<endl;
			vect.erase(vect.begin()+j-1);
		}
}
int main()
{
	string str;
	cin>>str;
	ifstream fin(str.c_str());
	vector<vector<int> >x;
	int sum=0,i=0,j=0;
	char ch;
	while(fin)
	{
		sum=0;
		fin.get(ch);
		while((ch>=48)&&(ch<=57))
		{
			sum=10*sum+int(ch)-48;
			fin.get(ch);
		}
		v.push_back(sum);
		if(ch=='\n')
		{
			if(sum!=0)
			x.push_back(v);
			v.clear();
		}
	}
	fin.close();
	map<int,int>m;
//	map<int,int>a;
	for(i=0;i<x.size();i++)
	{
		for(j=0;j<x[i].size();j++)
		{
			m[x[i][j]]++;
		}
	}
//	for(i=1;i<=it;i++)
//	{
//		a.insert(m[i],i);							// but problem is we cannot insert duplicates of key in map so we create a pair based on second element
//	}
	vector<pair<int,int> >v_pair;
	for(i=0;i<it;i++)
	v_pair.push_back(make_pair(i+1,m[i+1]));					// Here to access a pair(first or second) "." is used
	sort(v_pair.begin(),v_pair.end(),sor);						// sorting the pairs based on second element in descending order
	for(i=0;i<it;i++)
	v.push_back(v_pair[i].first);							// All the itemsets are inserted in decending order of frequency
	v_pair.clear();
	for(i=0;i<x.size();i++)
	{
		for(j=0;j<x[i].size();j++)
		v_pair.push_back(make_pair(x[i][j],m[x[i][j]]));
		sort(v_pair.begin(),v_pair.end(),sor);
		x[i].clear();								// x[i] is not lost but it became empty because of clear function
		for(j=0;j<v_pair.size();j++)
		x[i].push_back(v_pair[j].first);
		v_pair.clear();
	}
	fptr t;
	t=new tree();
	t->count=0;									// No need to initialise all the pointers as NULL
	for(i=0;i<it;i++)
	{
		l[i]=new tree();							// to initialise the table in which each element points to different items
		l[i]->key=i+1;
	}
	for(i=0;i<x.size();i++)
	create(t,x[i],0);
//	print(t,vect);
//	fptr p;
//	for(i=0;i<it;i++)
//	{
//		p=l[i]->next;
//		while(p)
//		{
//			cout<<p->key<<" ";
//			p=p->next;
//		}
//		cout<<endl;
//	}
//	for(i=0;i<vect.size();i++)
//	cout<<vect[i]<<endl;
//	cout<<t->d[0]->d[0]->d[0]->key<<endl;
//	cout<<t->d[0]->d[0]->d[1]->key<<endl;
//	cout<<t->d[0]->d[0]->d[2]->key<<endl;
//	cout<<t->d[0]->d[0]->d[2]->d[0]->key<<endl;
//	cout<<t->d[0]->d[1]->key<<endl;
//	cout<<t->d[0]->d[2]->key<<endl;
//	cout<<t->d[1]->d[0]->key<<endl;
//	cout<<t->d[1]->key<<endl;
//	fpgrowth(t);
	vect.clear();
}
