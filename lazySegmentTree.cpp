#include<iostream>
#include<vector>
#include<cmath>
#include<limits.h>
using namespace std;
void makeTree(vector <int> &arr,vector <int> & segTree,int l,int r,int pos)
{
	if(l==r)
	{	
		segTree[pos]=arr[l];
		return;
	}
	int m=(l+r)/2;
	makeTree(arr,segTree,l,m,pos*2+1);
	makeTree(arr,segTree,m+1,r,pos*2+2);
	segTree[pos]=min(segTree[pos*2+1],segTree[pos*2+2]);
}
int searchMin(vector <int> &segTree,vector <int> &LazyUpdate,int qlow, int qhigh,int low,int high,int pos)
{
	if(low>high){
	return INT_MAX;
	}
	
	if(LazyUpdate[pos]!=0)
	{
		segTree[pos]+=LazyUpdate[pos];
		if(low!=high)
		{
			LazyUpdate[pos*2+1]+=LazyUpdate[pos];
			LazyUpdate[pos*2+2]+=LazyUpdate[pos];
		}
		LazyUpdate[pos]=0;
	}
	if(qlow>high || qhigh<low)
		return INT_MAX;
		
		
	if(qlow<=low && qhigh>=high)
		return segTree[pos];
		
		
	int m=(low+high)/2;
	return min(searchMin(segTree,LazyUpdate,qlow,qhigh,low,m,pos*2+1),searchMin(segTree,LazyUpdate,qlow,qhigh,m+1,high,pos*2+2));


}

void updateTreeLazy(vector <int> & segTree,vector <int> & LazyUpdate,int value,int low,int high,int qlow,int qhigh,int pos)
{
	if(low>high){
	return;
	}
	if(LazyUpdate[pos]!=0)
	{
		segTree[pos]+=LazyUpdate[pos];
		if(low!=high)
		{
			LazyUpdate[pos*2+1]+=LazyUpdate[pos];
			LazyUpdate[pos*2+2]+=LazyUpdate[pos];
		}
		LazyUpdate[pos]=0;
	}
	if(qhigh<low || qlow>high)
		return;
		
	
	if(qhigh>=high && qlow<=low)
	{
		segTree[pos]+=value;
		if(low!=high)
		{
			LazyUpdate[pos*2+1]+=value;
			LazyUpdate[pos*2+2]+=value;
		}
		return;
	}
	
	int m=(low+high)/2;
	
	updateTreeLazy(segTree,LazyUpdate,value,low,m,qlow,qhigh,pos*2+1);
	updateTreeLazy(segTree,LazyUpdate,value,m+1,high,qlow,qhigh,pos*2+2);
	
	segTree[pos]=min(segTree[2*pos+1],segTree[2*pos+2]);
}


int main(){

	int n,temp;
	cout<< "enter value of n: "<<endl;
	cin>>n;
	vector <int> arr;
	for(int i=0;i<n;i++){
		cin>>temp;
		arr.push_back(temp);
	}
	temp=1;
	while(temp<n)
		temp*=2;
	
	vector <int> segTree((2*temp)-1);
	vector <int> LazyUpdate((2*temp)-1);
	fill(segTree.begin(),segTree.end(),INT_MAX);
	makeTree(arr,segTree,0,n-1,0);
	//search query processing...
	int min=searchMin(segTree,3,3,0,n-1,0);
	cout<<min<<endl;
	cout<<"Before update query\n";
	for(int i=0;i<segTree.size();i++)
		cout<<" "<<segTree[i];
	cout<<endl;
	for(int i=0;i<LazyUpdate.size();i++)
		cout<<" "<<LazyUpdate[i];
	cout<<endl;
	updateTreeLazy(segTree,LazyUpdate,4,0,n-1,2,5,0);
	cout<<"After update\n";
	for(int i=0;i<segTree.size();i++)
		cout<<" "<<segTree[i];
	cout<<endl;
	for(int i=0;i<LazyUpdate.size();i++)
		cout<<" "<<LazyUpdate[i];
	cout<<endl;
	return 0;
}

