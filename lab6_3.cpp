#include <iostream>

using namespace std;

template<typename T>
class BST;

template<typename T>
class BSTnode{
	T data;
	BSTnode *left, *right;
public:
	friend class BST<T>; // ����� class BST ���¡ member variable �ͧ BSTNode ��
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
		if(r != nullptr){ //��Ǩ�ͺ��ҷ�� r �բ�����������������������ѧ���������� recursive��������
			if(item < r->data){
				addNode(item,r->left);
			}else{
				addNode(item,r->right);
			}
		}else{
			r = new BSTnode<T>(item); // ����բ����ŷ�� node ����������������ŧ������
		}
	}

	void print(BSTnode<T> *r,int level){
		if(r != nullptr){
			print(r->right,level+1);
			for(int i =0;i < level;i++)cout << " "; // print ��ͧ��ҧ
			cout << r->data << endl;
			print(r->left,level+1);
		}
	}

	//find 
	BSTnode<T>*& find(BSTnode<T> *r,T item){
		while(r != nullptr || r->left != nullptr && r->right != nullptr){ // ��Ǩ�ͺ�������ش�ͧ���ǹ��
			if(item == r->data)return r;
			if(item < r->data){
				if(item == r->left->data)return r->left;
				r = r->left;
			}else{
				if(item == r->right->data)return r->right;
				r = r->right;
			}
		}
		BSTnode<T> *n = nullptr; //���ҧ nullptr ������ pointer ��� null ��Ѻ�
		return n;
	}

	//remove 
	void removeNode(BSTnode<T>*& r){
		if(r->left != nullptr && r->right != nullptr){
			BSTnode<T> *p = r; //pointer ��зӡ��
			BSTnode<T> *bp; //pointer �纤�ҡ�͹��зӡ��
			p = p->right; //����͹价ҧ��ҷչ֧ >> �Ң�ҧ����ҡ ���е�ͧ��ä�ҷ���ҡ���Ң�ҧ���·���ⴹź ����·���ش㹽�觢�Ңͧ����ⴹź
			while(p->left != nullptr){ // 价ҧ������������ ������յ������� >> �ҵ�Ƿ����·���ش㹢�ҧ��Ңͧ��Ƿ��١ź
				bp = p; 
				p = p->left;
			}
			bp->left = p->right; // �Ѵ��Ƿ����·���ش㹽�觢�Ңͧ��Ƿ��ⴹź�͡
			r->data = p->data; // ��Ҥ�ҷ����·���ش㹽�觢�Ңͧ��Ƿ��١ź�᷹������ǳ���ź
		}else if(r->left != nullptr || r->right != nullptr){
			BSTnode<T> *p = root;
			while(true){ // ����������á���ҵ�ǡ�͹����ź
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
			r = nullptr; //�������� node �١��ź�͡����������
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