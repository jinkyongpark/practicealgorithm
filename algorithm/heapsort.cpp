#include<iostream>
using namespace std;
int n;
int num[100];

struct priorityQueue{
	int data[100];
	int len = 1; //idx는 1부터 시작, len은 마지막데이터 다음을 가리킨다.
	
	void push(int x){
		data[len++] = x;
		int idx = len - 1;
		
		while(idx > 1){//root가 아닐 때
			if(data[idx] < data[idx/2]){ //부모와 비교
				int tmp = data[idx];
				data[idx] = data[idx/2];
				data[idx/2] = tmp;
			}
			else
				break;
			idx = idx/2;
		}
	}
	
	void pop(){
		data[1] = data[len-1]; // front에 가장 작은 값 저장이니 없앰
		data[len-1] = 0;
		len--;
		int idx = 1;
		int pidx;
		//front부터 다시 정렬을 시작한다.
		while(1){
			//자식들 중에서 우선순위가 높은거 (자신보다 큰거) 찾고 비교해서 swap결정
			//자식이 없는 경우
			if(idx*2>=len) break;
			//왼쪽자식만 있는 경우
			else if(1 <= idx*2 && idx*2 < len && idx*2+1>=len){
				pidx = idx*2;
			}
			//자식이 모두 있는 경우
			else{
				if(data[idx*2] < data[idx*2 + 1]) pidx = idx*2; //왼쪽이 더 작다.
				else pidx = idx*2 + 1;
			}
			
			//여기까지 왔다는건 자식이 있다는 것, 자식과 내값을 비교해서 swap할지 결정
			if(data[idx] > data[pidx]){
				int tmp = data[idx];
				data[idx] = data[pidx];
				data[pidx] = tmp;
				idx = pidx;
			}
			else
				break;
		}
	}
	int top(){
		return data[1];
	}
};

int main() {
  cin>>n;
  for(int i=0;i<n;i++)
		cin>> num[i];
	
  priorityQueue mypq;
  for(int i =0;i<n;i++)
	  mypq.push(num[i]);
  
  
  for(int i=0;i<n;i++){
	  cout << mypq.top() <<" ";
	  mypq.pop();
  }
  cout<<endl;
  
  return 0;
}