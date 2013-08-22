/*#include <iostream>

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
}*/
/*
int main(){
	int a[10] = {68,65,32,24,26,21,19,13,16,14};
	int b[10] = {1,2,3,4,5,6,7,8,9};
	print(a,10);
	printSideway(0,0,a,10);
}*/