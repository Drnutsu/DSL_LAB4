﻿#include <iostream>

using namespace std;

template<typename T>
class BST;

template<typename T>
class BSTnode{
	T data;
	BSTnode *left, *right;
public:
	friend class BST<T>; // ทำให้ class BST เรียก member variable ของ BSTNode ได้
	BSTnode(const T& d,BSTnode *l = nullptr,BSTnode *r = nullptr ){ 
		// constructor
		data = d;
		left = l;
		right = r;
	}
	T getData(){return data;}
};

template<typename T>
class BST{

	BSTnode<T> *root;
	//addNode internal system
	void addNode(const T& item,BSTnode<T>*& r){
		if(r != nullptr){ //ตรวจสอบว่าที่ r มีข้อมูลอยู่แล้วหรือไม่ถ้ายังมีอยู่ก็เข้า recursiveไปเรื่อยๆ
			if(item < r->data){
				addNode(item,r->left);
			}else{
				addNode(item,r->right);
			}
		}else{
			r = new BSTnode<T>(item); // ไม่มีข้อมูลที่ node นั้นๆแล้วใส่ข้อมูลลงไปได้เลย
		}
	}

	void print(BSTnode<T> *r,int level){
		if(r != nullptr){
			print(r->right,level+1);
			for(int i =0;i < level;i++)cout << " "; // print ช่องว่าง
			cout << r->data << endl;
			print(r->left,level+1);
		}
	}

	//find 
	BSTnode<T>*& find(BSTnode<T> *r,T item){
		while(r != nullptr || r->left != nullptr && r->right != nullptr){ // ตรวจสอบการสิ้นสุดของการวนหา
			if(item == r->data)return r;
			if(item < r->data){
				if(item == r->left->data)return r->left;
				r = r->left;
			}else{
				if(item == r->right->data)return r->right;
				r = r->right;
			}
		}
		BSTnode<T> *n = nullptr; //สร้าง nullptr เพื่อส่ง pointer ที่ null กลับไป
		return n;
	}

	//remove 
	void removeNode(BSTnode<T>*& r){
		if(r->left != nullptr && r->right != nullptr){
			BSTnode<T> *p = r; //pointer กระทำการ
			BSTnode<T> *bp; //pointer เก็บค่าก่อนกระทำการ
			p = p->right; //เลื่อนไปทางขวาทีนึง >> หาข้างที่มาก เพราะต้องการค่าที่มากกว่าข้างซ้ายที่จะโดนลบ แต่น้อยที่สุดในฝั่งขวาของที่จะโดนลบ
			while(p->left != nullptr){ // ไปทางซ้ายไปเรื่อยๆ จนไม่มีตัวใดแล้ว >> หาตัวที่น้อยที่สุดในข้างขวาของตัวที่ถูกลบ
				bp = p; 
				p = p->left;
			}
			bp->left = p->right; // ตัดตัวที่น้อยที่สุดในฝั่งขวาของตัวที่โดนลบออก
			r->data = p->data; // เอาค่าที่น้อยที่สุดในฝั่งขวาของตัวที่ถูกลบไปแทนที่บริเวณที่ลบ
		}else if(r->left != nullptr || r->right != nullptr){
			BSTnode<T> *p = root;
			while(true){ // ไล่ตั้งแต่ตัวแรกมาหาตัวก่อนที่จะลบ
				if(r->data > p->data){
					if(p->right == r)break;
					p = p->right;
				}else{
					if(p->left == r)break;
					p = p->left;
				}
			}
			if(r->data > p->data){
				if(r->left != nullptr){
					p->right = r->left;  
				}else p->right = r->right;
			}else{
				if(r->left != nullptr){
					p->left = r->left;  
				}else p->left = r->right;
			}
		}else{
			r = nullptr; //ถ้าไม่มี node ลูกก็ลบออกดื้อๆได้เลย
		}

	}

	//Count more
	int countMore(const T& item,BSTnode<T>*& r){
		//iterative solution
		/*int count = 0;
		BSTnode<T> *p = r;
		if(p->right != nullptr){ //ถ้าไม่มีโหนดข้างขวาแสดงว่าไม่มี ตัวที่มากกว่ามันแน่ๆ
		p = p->right; // โหนดข้างขวาของ r ต้องมากกว่า r อยู่แล้ว
		count++;
		while(p->left != nullptr){
		if( p->left->data > r->data){
		count++;
		if(p->right != nullptr)count++; // ถ้ามีฝั่งขวาของตัวที่ตรวจด้วยก็เอามานับด้วย เพราะฝั่งขวาจะมากกว่าฝั่งซ้ายเสมอ หากซ้ายมากกว่าแล้ว ขวาก็ต้องมากว่าเสมอ
		p = p->left;
		if(p->right->data > r->data){
		count++;
		p = p->right;
		}
		}
		}
		}
		return count;*/
		if(r != nullptr){
			if(r->data > item)return 1 + countMore(item,r->left) + countMore(item,r->right); //นับโดยเข้าไปทั้งซ้าย และ ขวา ของ node
			else return 0;
		}else{
			return 0;
		}
	}

	//height

	int height(BSTnode<T>* r){
		if(r != nullptr){
			int ans = (height(r->left) < height(r->right) )?height(r->right):height(r->left);
			return 1 + ans;
		}else return 0;
	}

	//path
	void path(BSTnode<T>* r,T item,BST<T>& temp){
		if(r != nullptr){
			temp.addNode(r->data); //ใส่โหนดไปใน temp
			if(item >= r->data)path(r->right,item,temp); //วิ่งค้นหาเส้นทางไปตามหลักการ binary น้อยซ้ายมากขวา
			else path(r->left,item,temp);
		}

	}

	//smallest
	T smallest(BSTnode<T> *r){
		if(r->left != nullptr){
			return smallest(r->left);
		}else return r->data;
	}

	//largest
	T largest(BSTnode<T> *r){
		if(r->right != nullptr){
			return largest(r->right);
		}else return r->data;
	}

	// balanced
	bool balanced(BSTnode<T> *r){
			int left = height(r->left);
			int right = height(r->right);
			if(left == right)return true;
			else return false;
	}
public:
	//constructor
	BST(){
		root = nullptr;
	}
	//addNode form user
	void addNode(const T& d){
		addNode(d,root);
	}
	//print
	void print(){
		print(root,0);
	}

	BSTnode<T>*& find(T item){
		return find(root,item);
	}

	//remove
	void removeNode(T item){
		removeNode(find(item));
	}

	//removeTree
	void removeTree(BSTnode<T>* r){ //ยังมีบัค คือลบ root ไม่ได้ ลบทั้ง tree ทั้งหมดเลยไม่ได้
		if(r != nullptr){
			removeTree(r->left);
			removeTree(r->right);
			removeNode(r->data);
			print();
			cout << "------------------------" <<endl;
		}
	}

	//count More
	int countMore(const T& item){
		return countMore(item,find(item)->right); //เลื่อไปทางขวด 1 node เพราะต้องเริ่มนับที่ node ต่อมาทางขวาซึ่งจะมากกว่า node ที่ item แน่ๆ
	}

	//height
	int height(const T& item){
		return height(find(item))-1; //ลบออกหนึง่เพราะ height = จำนวนnode - 1
	} 

	//path
	void path(const T& item){
		BST<T> temp; //สร้าง BST ใหม่ไว้เก็บข้อมูลเพื่อรอปริ้น
		path(root,item,temp);
		temp.print();
	}

	//smallest
	T smallest(){
		return smallest(root);
	}

	//largest
	T largest(){
		return largest(root);
	}

	//balanced
	bool balanced(){
		return balanced(root);
	}
};

int main() {
	BST<int> t;
	int a[11]  = {5,3,2,9,4,7,17,16,15,13,14};
	for(int i =0;i < 11;i++){
		t.addNode(a[i]);
		t.print();
		cout << "----------------------------------------" << endl;
	}
	cout << "----------------------------------------" << endl;
	cout << " test find" << endl;
	BSTnode<int> *ans = t.find(5);
	if(ans == nullptr){
		cout << "null";
	}
	/*cout << "----------------------------------------" << endl;
	t.removeNode(9);
	t.print();
	cout << "----------------------------------------" << endl;
	*/
	t.removeTree(t.find(16));
	t.print();
	cout << "----------------------------------------" << endl;
	t.print();
	cout << "count = " << t.countMore(3) << endl;
	cout << "----------------------------------------" << endl;
	t.print();
	cout << "height = " << t.height(3) << endl;
	cout << "----------------------------------------" << endl;
	cout << "path is " << endl;
	t.path(16);
	cout << "----------------------------------------" << endl;
	cout << "smallest" << endl;
	cout << "smallest value = " << t.smallest() <<endl;
	cout << "----------------------------------------" << endl;
	cout << "largest" << endl;
	cout << "largest value = " << t.largest() <<endl;
	cout << "----------------------------------------" << endl;
	cout << "Balanced" << endl;
	t.print();
    cout << "this tree is :  ";
	if(t.balanced())cout << "balanced"<<endl;
	else cout << "not balanced" <<endl;

}