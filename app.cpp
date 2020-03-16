#include<bits/stdc++.h>
#define per 5
#define it 5
using namespace std;
void appr(vector<vector<int> >vin[],vector<vector<int> >&vout,int n)
{
	int i=0,count=0,j=0,k=0,l=0,q=0,r=0,c=0,sum=0,t=0,b=0,d=0;
	map<int,int>m;
	for(i=0;i<vin[n].size();i++)
		for(j=0;j<vin[n][i].size();j++)
			m[vin[n][i][j]]++;
	for(j=0;j<it;j++)
		if(((m[j+1]*100)/vin[n].size())<per)
			m[j+1]=0;
	vector<int>v,p;
	vector<vector<int> >x,y;
	fstream fout;
	fout.open("appriori.txt",ios::app|ios::out);
	fout<<"L1"<<endl;
	for(i=1;i<=it;i++)
		if(m[i]!=0)
		{
			p.push_back(i);
			fout<<i<<endl;
			x.push_back(p);
			p.clear();
		}
	m.clear();
	fout.close();
	do
	{
		count=0;
		for(i=0;i<x.size();i++)
		{
			for(j=i+1;j<x.size();j++)
			{
				for(k=0;k<x[i].size()-1;k++)
				{
					if(x[i][k]!=x[j][k])
					break;
				}
				if(k==x[j].size()-1)
				{
					for(l=0;l<x[i].size();l++)
					{
						v.push_back(x[i][l]);
						m[x[i][l]]=1;
					}
					v.push_back(x[j][x[j].size()-1]);
					m[x[j][x[j].size()-1]]=1;
					for(q=0;q<vin[n].size();q++)
					{
						c=0;
						for(r=0;r<vin[n][q].size();r++)
							if(m[vin[n][q][r]]==1)
							c++;
						if(c==v.size())
						sum++;
					}
					m.clear();
					if(sum>=((vin[n].size())*per)/100)
					{
						count++;
								//		cout<<"pruning"<<endl;
						vector<int>a;
						for(k=0;k<v.size();k++)
						{
							for(t=0;t<v.size();t++)
							{
								if(t!=k)
								a.push_back(v[t]);
							}
											//	if vout.size()==0 case has to be considered
							for(d=0;d<vout.size();d++)
							{
								if(a==vout[d])
								{
									b++;
									break;
								}
							}
							a.clear();
						}
						if(b==v.size()||b==0)
						{
							y.push_back(v);
							vout.push_back(v);
							count++;
						}
						b=0;
						v.clear();
					}
				}
			}
		}
		x.clear();
		x=y;
		y.clear();
		sum=0;
		fout.open("appriori.txt",ios::out|ios::app);
		if(count>0)
		fout<<"L"<<x[0].size()<<endl;
		for(i=0;i<x.size();i++)
		{
			for(j=0;j<x[i].size();j++)
			{
				if(j==x[i].size()-1)
				fout<<x[i][j];
				else
				fout<<x[i][j]<<" ";
			}
			fout<<endl;
		}
		fout.close();
	}while(count>1);
}
int main()
{
	vector<vector<int> >vin[1],vout;
	string str;
	cin>>str;
	fstream fin(str.c_str());
	int i=0,sum=0,j=0;
	char ch;
	vector<int>v;
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
			vin[i].push_back(v);
			v.clear();
		}
	}
	appr(vin,vout,0);
}
