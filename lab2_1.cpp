#include <iostream>

using namespace std;
template <typename T>
void print(T *a,int index){
	for(int i = 0;i < index;i++){
		cout << a[i]  << " ";
	}
	cout << endl;
}

template <typename T>
void printSideway(int root,int indent,T *arr,int size){
	if(root < size){
		printSideway(2*root+2,indent + 1,arr,size);
		printSpaceIndentTimes(indent);
		cout << arr[root] <<endl;
		printSideway(2*root+1,indent + 1,arr,size);
	}
}

void printSpaceIndentTimes(int indent){
	for(int i = 0;i < indent;i++){
		cout << " ";
	}
}

template<typename T>
class minHeap{
	int size;		//array size
	int last_index;	//last index of heap
	T *h;
public:
	minHeap(int size){
		h = new T[size];
		last_index = -1;
	}
	~minHeap(){
		delete[] h;
	}

	void print(){
		for(int i = 0;i <= last_index;i++){
			cout << h[i]  << " ";
		}
		cout << endl;
	}

	void insert(int index,T value){ //index value คือ เลขที่ใช้วนเช็คการสลับดึงพ่อลงมา เรื่อยๆ
		if(index == 0){
			h[index] = value;
			last_index++;
		}else{
			if(value < h[(index-1)/2] ){ //เช็คที่ root
				h[index] = h[(index-1)/2];
				insert((index-1)/2,value);
			}else{
				h[index] = value;
				last_index++;
			}
		}
	}

	void inorder(int root){ 

		if(root <= last_index){
			inorder(2*root+1);
			cout << h[root] << " ";
			inorder(2*root+2);
		}
	}

	void preorder(int root){

		if(root < last_index){
			cout << h[root] << " ";
			inorder(2*root+1);
			inorder(2*root+2);
		}
	}

	void postorder(int root){

		if(root < last_index){
			inorder(2*root+1);
			inorder(2*root+2);
			cout << h[root] << " ";
		}
	}

	void deletemin(T& min){
		int root = 0;
		int temp = h[root];
		while(root*2+2 <= last_index){ //เช็คว่าจะลงไปลึกเท่าไร
           if(h[root*2+1] < h[root*2+2]){ // เช็คว่าฝั่งซ้ายหรือขวาฝั่งไหนน้อยกว่ากัน  
			   if(h[last_index] > h[root*2+1]){
				   h[root] = h[root*2+1];
			   }else{
				   h[root] = h[last_index]; //Bug นิดหน่อย
			   }
			   root = root*2+1;
		   }else{
			   if(h[last_index] > h[root*2+2]){
				   h[root] = h[root*2+2];
			   }else{
				   h[root] = h[last_index];
			   }
			   root = root*2+2;
		   }
		}
		h[root] = h[last_index];
		h[last_index] = temp;
		min = temp;
		last_index--;
	}
};

template<typename T>
void insert(T *arr,int size,T value){
	if(size == 0){
		arr[size] = value;
	}
	if(value < arr[(size-1)/2] ){ //เช็คที่ root
		arr[size] = arr[(size-1)/2];
		insert(arr,(size-1)/2,value);
	}else{
		arr[size] = value;
	}
	size++;
}

int main(){
	const int size = 10;
	//int a[10] = {68,65,32,24,26,21,19,13,16,14};
	int a[10] = {13,14,21,19,16,65,24,68,26,32};
	int arr[10];
	minHeap<int> h(size);
	for(int i = 0;i < 10;i++){
		h.insert(i,a[i]);
		h.print();
	}
	cout << "--------------------------------------------" << endl;
	h.inorder(0);
	cout << endl;
	h.preorder(0);
	cout << endl;
	h.postorder(0);
	cout << endl;
	cout << "---------------------------------------------" << endl;
	int b[10]; 
	for(int i =0;i < 10;i++){
      h.deletemin(b[i]);
	  h.print();
	}
	for(int i = 0;i < 10;i++){
		cout << b[i] << " " ;
	}

	/*for(int i = 0;i < 10;i++){
	insert(arr,i,a[i]);
	print(arr,i);
	printSideway(0,0,arr,i);
	cout << "---------------------------" << endl;
	}*/
}