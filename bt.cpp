# include<iostream>
# include<vector>
# include<algorithm>

using namespace std;

class Node{
	public:
		int data;
	    Node* left;
	    Node* right;
	
	    Node(int val){
	    	data = val;
		    left = right = nullptr;
		}
		
	
};

static int idx = -1;

Node* buildtree(vector<int> preorder){
	idx++;
	if(preorder[idx] == -1){
		return nullptr;
		}
	Node* root = new Node(preorder[idx]);
	root->left = buildtree(preorder);
	root->right = buildtree(preorder);
	
	return root;
}

void preordertraversal(Node* root){
	if(root==nullptr){
		return;
	}
	
	cout<<root->data<<" ";
	preordertraversal(root->left);
	preordertraversal(root->right);
}

void inordertrav(Node* root){
	if(root == nullptr){
		return;
	}
	
	inordertrav(root->left);
	cout<<root->data<<" ";
	inordertrav(root->right);
}

void postordertrav(Node* root){
	if(root == nullptr){
		return;
	}
	
	inordertrav(root->left);
	inordertrav(root->right);
    cout<<root->data<<" ";

}

int main(){
	vector<int> preorder = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};
	
	Node* root = buildtree(preorder);
	
	preordertraversal(root);
	cout<<endl;
	inordertrav(root);
	cout<<endl;
	postordertrav(root);
	return 0;
}