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
int searchMin(vector <int> &segTree,int qlow, int qhigh,int low,int high,int pos)
{
	if(qlow>high || qhigh<low)
		return INT_MAX;
	if(qlow<=low && qhigh>=high)
		return segTree[pos];
	int m=(low+high)/2;
	return min(searchMin(segTree,qlow,qhigh,low,m,pos*2+1),searchMin(segTree,qlow,qhigh,m+1,high,pos*2+2));


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
	
	
	return 0;
}

