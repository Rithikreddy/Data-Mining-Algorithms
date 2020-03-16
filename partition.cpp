#include<bits/stdc++.h>
#define per 56
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
	for(i=0;i<it;i++)
		if(m[i+1]!=0)
		{
			p.push_back(i+1);
			x.push_back(p);
			p.clear();
		}
	m.clear();
	if(x.size()==1)
	{
		cout<<x[0][0]<<endl;
		return;
	}
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
//						cout<<"pruning"<<endl;
						vector<int>a;
						for(k=0;k<v.size();k++)
						{
							for(t=0;t<v.size();t++)
								if(t!=k)
									a.push_back(v[t]);
							for(d=0;d<vout.size();d++)
								if(a==vout[d])
								{
									b++;
									break;
								}
							a.clear();
						}
						//	if vout.size()==0 case has to be considered
						if(b==v.size()||b==0)
						{
							y.push_back(v);
							vout.push_back(v);
							for(k=0;k<v.size();k++)
							cout<<" "<<v[k];
							cout<<endl;
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
	}while(count>1);
}
int main()
{
	ofstream fout;
	int l,i=0,j=0,r,s,sum=0,size=0,k=0;
	float c=0;
	cin>>l;
	string str[l];
	vector<vector<int> >vin[l];
	vector<vector<int> >vout;
	char ch;
	while(i<l)
	{
		cin>>str[i];
		fstream fin(str[i].c_str());
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
				size++;
				v.clear();
			}
		}
		appr(vin,vout,i);
		fin.close();
		i++;
	}
//	as size++ is there for the last iterattion as size is incremented so subtract 1 from that
	size--;
//	generally used for removing in single vector not for vector within a vector
//	vout.erase(unique(vout.begin(),vout.end()),vout.end());
	map<int,int>m;
//	for removing duplicates
	for(i=0;i<vout.size();i++)
	{
		for(j=i+1;j<vout.size();j++)
		if(vout[i]==vout[j])
		vout.erase(vout.begin()+j);
	}
	sum=0;
	for(i=0;i<vout.size();i++)
	{
		for(j=0;j<vout[i].size();j++)
		{
			m[vout[i][j]]=1;
		}
		for(j=0;j<l;j++)
		{
			for(r=0;r<vin[j].size();r++)
			{
				for(s=0;s<vin[j][r].size();s++)
				{
					if(m[vin[j][r][s]]==1)
					sum++;
				}
				if(sum==vout[i].size())
				{
					c++;
				}
				sum=0;
			}
		}
		m.clear();
		fout.open("partition.txt",ios::out|ios::app);
		if(c>=(size*per)/100.0)
		{
			for(j=0;j<vout[i].size();j++)
			if(j!=vout[i].size()-1)
			{
				fout<<vout[i][j]<<" ";
			}
			else
			{
				fout<<vout[i][j];
			}
			fout<<endl;
		}
		c=0;
		fout.close();
	}
}

