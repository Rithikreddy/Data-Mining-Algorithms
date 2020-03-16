#include<bits/stdc++.h>
#define min_sup 20
#define it 5
using namespace std;
int main()
{
	vector<vector<int> >sc,sb,dc,db,vin;
	string str;
	cin>>str;
	fstream fin(str.c_str());
	int i=0,sum=0,j=0,l,count=0,k=0;
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
			vin.push_back(v);
			v.clear();
		}
	}
	for(i=1;i<=it;i++)
	{
		v.push_back(i);
		v.push_back(0);		//	one for counting the no of times this itemset occured in transactions
		v.push_back(0);		// one for counting the no of transactions in which the itemset is checked
		dc.push_back(v);
		v.clear();
	}
	i=0;
	map<int,int>m;
	while((dc.size())||(db.size()))
	{
		l=i;
		while((l<(vin.size()/it)+i)&&(l<vin.size()))	// one for checking the count l should be less than m(vin.size()/it)+i(initial stage of reading of transactions)
		{
			cout<<"CEO"<<endl;
			for(k=0;k<vin[l].size();k++)
				m[vin[l][k]]=1;
			for(j=0;j<dc.size();j++)
			{
				if(((dc[j].size()-2)<=((l/(vin.size()/it))+1))||(dc[j].size()-1>0))
				{
					for(k=0;k<dc[j].size()-2;k++)
					{
						if(m[dc[j][k]]!=1)
						break;
					}
					if(k==dc[j].size()-2)
					{
						dc[j][dc[j].size()-2]++;
					}
				}
				dc[j][dc[j].size()-1]++;
			}
			for(j=0;j<db[j].size();j++)
			{
				if(((db[j].size()-2)<=((l/(vin.size()/it))+1))||(db[j].size()-1>0))
				{
					for(k=0;k<db[j].size()-1;k++)
					{
						if(m[db[j][k]]!=1)
						break;
					}
					if(k==db[j].size()-2)
					{
						db[j][db[j].size()-2]++;
					}
				}
				db[j][db[j].size()-1]++;
			}
			l++;
			m.clear();
		}
		for(j=0;j<dc.size();j++)
		{
			cout<<"Software Developer"<<endl;
			if(dc[j].size()==(i%vin.size())/(vin.size()/it))
			{
				cout<<"Hello"<<endl;
				if((dc[j][dc[j].size()-1]==vin.size())&&(dc[j][dc[j].size()-2]>=min_sup)) //	case of dc->sb 
				{
					sb.push_back(dc[j]);
					dc.erase(dc.begin()+j);
					cout<<"Bye"<<endl;
				}
				if((dc[j][dc[j].size()-1]==vin.size())&&(dc[j][dc[j].size()-2]<min_sup)) //	case of dc->sc
				{
					sc.push_back(dc[j]);
					cout<<"Hi"<<endl;
					dc.erase(dc.begin()+j);
				}
//				else
//				if((dc[j][dc[j].size()-1]<vin.size())&&(dc[j][dc[j].size()-2]>=min_sup))	// case of dc->db (if checking for the first time and within m 
//	//			transcations and min_sup is statisfied.Then the checking the superset's subsets are required
//				{
//					for(k=0;k<dc[j].size()-2;k++)
//					m[dc[j][k]]=1;
//					vector<int>temp[dc[j].size()+1];
//					int p=0;
//				}
//				else
//				continue;
			}
		}
		for(j=0;j<db.size();j++)
		{
			if(db[j][db[j].size()-1]==vin.size())
			{
				sb.push_back(db[j]);
				db.erase(db.begin()+j);
			}
		}
		if(l==vin.size())
		count++;
		i=l%(vin.size());
	}
	for(i=0;i<sb.size();i++)
	{
		for(j=0;j<sb[i].size();j++)
			cout<<sb[i][j]<<" ";
		cout<<endl;
	}
	for(i=0;i<sc.size();i++)
	{
		for(j=0;j<sc[i].size();j++)
			cout<<sc[i][j]<<" ";
		cout<<endl;
	}
	cout<<"SDE"<<endl;
	cout<<count;
}




