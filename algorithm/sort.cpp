#include<iostream>
using namespace std;
int n;
int num[100];
//선택정렬
void selectionsort(){
	for(int i=0; i<n ;i++){
		int idx = i;
		for(int j=i; j<n ;j++){
			if(num[idx] > num[j]){
				idx = j;
			}
		}
		
		int tmp;
		tmp = num[i];
		num[i] = num[idx];
		num[idx] = tmp;
	}
}
//삽입정렬
void insertsort(){
	for(int i=0;i<n;i++){
		int idx = i;
		for(int j=i;j>=1;j--){
			if(num[j-1] > num[j]){
				int tmp;
				tmp = num[j-1];
				num[j-1] = num[j];
				num[j] = tmp;
			}
			else 
				break;
		}
	}
}

//버블정렬
void bubblesort(){
	for(int i=0;i<n;i++){
		for(int j=0 ; j<n-i-1 ; j++){
			if(num[j] > num[j+1]){
				int tmp;
				tmp = num[j];
				num[j] = num[j+1];
				num[j+1] = tmp;
			}
		}
	}
}
//퀵정렬
int getLeft(int s,int e, int pivot, int result[]){
  //pivot보다 작거나 같은 값을 result에 저장하는 함수
  //result의 갯수를 반환
  
  int idx=0;
  for(int i=s;i<=e;i++)
    if(num[i]<=pivot)
      result[idx++] = num[i];
  
  return idx;
}
int getRight(int s, int e, int pivot, int result[]){
  //pivot보다 큰 값을 result에 저장하는 함수
  //result갯수를 반환
  
  int idx=0;
  for(int i=s;i<=e;i++)
    if(num[i]>pivot)
      result[idx++] = num[i];
  
  return idx;
}

void quicksort(int start, int end){
	if(start>=end) return ;
	
	int left[100], right[100];
	int pivot = num[start];
	
	int left_cnt = getLeft(start+1,end,pivot,left);
	int right_cnt = getRight(start+1,end,pivot,right);
	
	for(int i =0; i<left_cnt; i++)
		num[start+i] = left[i];
	
	num[start+left_cnt] = pivot; // swap
	
	for(int i = 0; i <right_cnt; i++)
		num[start + left_cnt + 1 + i] = right[i];
	
	quicksort(start,start+left_cnt-1);
	quicksort(start+left_cnt+1, end);
}
//합병정렬
void merge(int s1,int e1, int s2, int e2){
	int start =s1, end = e2;
	int res[100];
	int idx = 0;
	while(s1 <= e1 && s2<=e2){
		if(num[s1] <= num[s2]) res[idx++] = num[s1++];
		else res[idx++] = num[s2++];
	}
	if(s1>e1){
		while(s2<=e2)
			res[idx++] = num[s2++];
	}
	if(s2>e2){
		while(s1<=e1)
			res[idx++]  = num[s1++];
	}
	
	for(int i = start; i<= end; i++)
		num[i] = res[i-start];
}
void mergesort(int start, int end){
	if (start>=end) return;
	int mid = (start+end)/2;
	mergesort(start,mid);
	mergesort(mid+1, end);
	merge(start, mid, mid+1, end);
}

int main(){
	cin >>n;
	for(int i=0;i<n;i++)
		cin>> num[i];
	//selectionsort();
	//insertsort();
	//bubblesort();
	//quicksort(0,n-1);
	//mergesort(0,n-1);
	for(int i=0;i<n;i++)
		cout << num[i] <<" ";
	cout<<endl;
	return 0;
}