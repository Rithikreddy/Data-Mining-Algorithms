#include<bits/stdc++.h>
#define k 2
#define infi 1000
using namespace std;
int main()
{
	int i=0,j=0,count=0,l=0,q=0,c;
	double sum=0;
	char ch;
	vector<double>v,x;
	vector<vector<double> >vin[k],vout,vl[k],ls,mn;
	fstream fin("cluster.txt");
	while(fin)
	{
		fin.get(ch);
		sum=0;
		while(ch>=48&&ch<=57)
		{
			sum=10*sum+ch-48;
			fin.get(ch);
		}
		if(sum!=0)
		v.push_back(sum);
		if(ch=='\n')
		{
			vout.push_back(v);
			v.clear();
		}
	}
	while(1)
	{
		srand(time(0));
		j=rand()%vout.size();
		for(i=0;i<mn.size();i++)
		{
			if(mn[i]==vout[j])
			break;
		}
		if(i==mn.size())
		{
			mn.push_back(vout[j]);
			count++;
		}
		if(count==k)
		break;
	}
//	for(i=0;i<vout.size();i++)
//	{
//		for(j=0;j<vout[i].size();j++)
//		cout<<vout[i][j]<<" ";
//		cout<<endl;
//	}
	for(i=0;i<mn.size();i++)
	{
		for(j=0;j<mn[i].size();j++)
		cout<<mn[i][j];
		cout<<endl;
	}
	while(1)
	{
		cout<<"Hi"<<endl;
		for(i=0;i<vout.size();i++)
		{
			q=0;
			c=infi;
			for(j=0;j<mn.size();j++)
			{
				sum=0;
				for(l=0;l<mn[j].size();l++)
				{
					sum+=(vout[i][l]-mn[j][l])*(vout[i][l]-mn[j][l]);
				}
				if(sum<c)
				{
					c=sum;
					q=j;
				}
			}
//			cout<<c<<endl;
			cout<<q<<endl;
			vl[q].push_back(vout[i]);
			for(l=0;l<vout[i].size();l++)
			cout<<vout[i][l]<<" ";
//			cout<<"bye"<<endl;
		}
		cout<<"1234"<<endl;
//		for(i=0;i<k;i++)
//		{
//			for(j=0;j<vout[i].size();j++)
//			cout<<vout[i][j]<<" ";
//			cout<<endl;
//		}
		for(i=0;i<k;i++)
		{
			for(j=0;j<vl[i].size();j++)
			{
				x=vl[i][0];
				for(l=1;l<vl[i][j].size();l++)
				{
					x[l]+=vl[i][j][l];
				}
				for(l=0;l<x.size();l++)
				x[l]/=vl[i][j].size();			// computing average
				ls.push_back(x);
				x.clear();
			}
		}
		for(i=0;i<mn.size();i++)
		{
			if(mn[i]!=ls[i])
			break;
		}
		if(i==mn.size())
		{
			cout<<"Final cluster is obtained "<<endl;
			for(i=0;i<k;i++)
			{
				for(j=0;j<vl[i].size();j++)
				{
					for(l=0;l<vl[i][j].size();l++)
					cout<<vl[i][j][l]<<" ";
					cout<<endl;
				}
			}
			break;
		}
		else
		{
			for(i=0;i<k;i++)
			{
				vl[i].clear();
			}
			mn=ls;
			ls.clear();
		}
	}
}























