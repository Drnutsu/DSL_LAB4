#include <iostream>

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
	void removeTree(BSTnode<T> *r){
		if(r != nullptr){
			removeTree(r->left);
			removeTree(r->right);
			removeNode(r->data);
			print();
			cout << "------------------------" <<endl;
		}
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
	cout << "----------------------------------------" << endl;
	t.removeNode(9);
	t.print();
	cout << "----------------------------------------" << endl;
	t.removeTree(t.find(17));
	t.print();
}