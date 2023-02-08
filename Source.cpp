#include<stdio.h> 
#include<iostream> 
#include<stdlib.h> 
#include<time.h> 
#include<memory.h> 

using namespace std;

class MyTree {
	struct NodeTree {
		NodeTree* nLeft, * nRight;
		int value;
		bool red;
	};
	NodeTree* tree_root;
private:
	void Balance(NodeTree**);
	bool BalanceLeft(NodeTree**);
	bool BalanceRight(NodeTree**);
	NodeTree* NewNode(int value);
	void DeletRoot(NodeTree*);
	void Delete(NodeTree*);
	bool AddNode(int, NodeTree**);
	bool MaxObject(NodeTree**, NodeTree**);
	NodeTree* MoveLeft(NodeTree*);
	NodeTree* MoveRight(NodeTree*);
	bool Remove(NodeTree**, int);
	void Show(NodeTree*, int, char);
public:
	void Show();
	~MyTree();
	void AddNode(int);
	void RemoveMain(int);
	void DeleteMain();
	void FindObject(int);
};
MyTree::~MyTree()
{
	Delete(tree_root);
}
void MyTree::Show(NodeTree* node, int depth, char dir) {
	for (int i = 0; i < depth; i++) putchar(' ');
	if (!node) {
		cout << dir << " -------" << endl;
		return;
	}
	if (node->red)
		cout << dir << " " << node->value << " (red)" << endl;  else
		cout << dir << " " << node->value << " (black)" << endl;
	if (!node->nLeft && !node->nRight) {
		return;
	}
	Show(node->nLeft, depth + 3, '-');
	Show(node->nRight, depth + 3, '+');
}
MyTree::NodeTree* MyTree::MoveRight(NodeTree* node) {
	NodeTree* nLeft = node->nLeft;
	NodeTree* nLeft_temp = nLeft->nRight;
	nLeft->nRight = node;
	node->nLeft = nLeft_temp;
	return nLeft;
}
MyTree::NodeTree* MyTree::MoveLeft(NodeTree* node) {
	NodeTree* nRight = node->nRight;
	NodeTree* nRight_temp = nRight->nLeft;
	nRight->nLeft = node;
	node->nRight = nRight_temp;
	return nRight;
}
MyTree::NodeTree* MyTree::NewNode(int value)
{
	NodeTree* node = new NodeTree;
	node->value = value;
	node->nLeft = node->nRight = 0;
	node->red = true;
	return node;
}
void MyTree::DeletRoot(NodeTree* node)
{
	delete node;
}
void MyTree::Delete(NodeTree* node)
{
	if (!node) return;
	Delete(node->nLeft);
	Delete(node->nRight);
	DeletRoot(node);
}
void MyTree::Balance(NodeTree** root)
{
	NodeTree* nLeft, * nRight, * nLeft_temp, * nRight_temp;  NodeTree* node = *root;
	if (node->red) return;
	nLeft = node->nLeft;
	nRight = node->nRight;
	if (nLeft && nLeft->red) {
		nRight_temp = nLeft->nRight;
		if (nRight_temp && nRight_temp->red)   nLeft = node->nLeft = MoveLeft(nLeft);   nLeft_temp = nLeft->nLeft;
		if (nLeft_temp && nLeft_temp->red) {
			node->red = true;
			nLeft->red = false;
			if (nRight && nRight->red) {
				nLeft_temp->red = true;   nRight->red = false;   return;
			}
			*root = MoveRight(node);
			return;
		}
	}
	if (nRight && nRight->red) {
		nLeft_temp = nRight->nLeft;
		if (nLeft_temp && nLeft_temp->red)
			nRight = node->nRight = MoveRight(nRight);   nRight_temp = nRight->nRight;
		if (nRight_temp && nRight_temp->red) {
			node->red = true;
			nRight->red = false;
			if (nLeft && nLeft->red) {
				nRight_temp->red = true;
				nLeft->red = false;
				return;
			}
			*root = MoveLeft(node);
			return;
		}
	}
}
bool MyTree::BalanceLeft(NodeTree** root)
{
	NodeTree* node = *root;
	NodeTree* nLeft = node->nLeft;
	NodeTree* nRight = node->nRight;
	if (nLeft && nLeft->red) {
		nLeft->red = false;
		return false;
	}
	if (nRight && nRight->red) {
		node->red = true;
		nRight->red = false;
		node = *root = MoveLeft(node);
		if (BalanceLeft(&node->nLeft)) node->nLeft->red = false;   return false;
	}
	NodeTree* nRight_1 = nRight->nLeft;
	NodeTree* nRight_2 = nRight->nRight;
	if ((!nRight_1 || !nRight_1->red) && (!nRight_2 || !nRight_2->red)) {
		nRight->red = true;
		return true;
	}
	else if (nRight_1 && nRight_1->red) {
		nRight->red = true;
		nRight_1->red = false;
		nRight = node->nRight = MoveRight(nRight);
		nRight_2 = nRight->nRight;
	}
	else if (nRight_2 && nRight_2->red) {
		nRight->red = node->red;
		nRight_2->red = node->red = false;
		*root = MoveLeft(node);
	}
	return false;
}
bool MyTree::BalanceRight(NodeTree** root)
{
	NodeTree* node = *root;
	NodeTree* nLeft = node->nLeft;
	NodeTree* nRight = node->nRight;
	if (nRight && nRight->red) {
		nRight->red = false;
		return false;
	}
	if (nLeft && nLeft->red) {
		node->red = true;
		nLeft->red = false;
		node = *root = MoveRight(node);
		if (BalanceRight(&node->nRight)) node->nRight->red = false;   return false;
	}
	NodeTree* nLeft_1 = nLeft->nLeft;
	NodeTree* nLeft_2 = nLeft->nRight;
	if ((!nLeft_2 || !nLeft_2->red) && (!nLeft_1 || !nLeft_1->red)) {
		nLeft->red = true;
		return true;
	}
	else if (nLeft_2 && nLeft_2->red) {
		nLeft->red = true;
		nLeft_2->red = false;
		nLeft = node->nLeft = MoveLeft(nLeft);
		nLeft_1 = nLeft->nLeft;
	}
	else if (nLeft_1 && nLeft_1->red) {
		nLeft->red = node->red;
		nLeft_1->red = node->red = false;
		*root = MoveRight(node);
	}
	return false;
}
void MyTree::FindObject(int value)
{
	NodeTree* node = tree_root;
	while (node) {
		if (node->value == value)
		{
			cout << "Узел со значением " << node->value << " найден и имеет ";   if (node->red) cout << "Красный цвет" << endl;   else cout << "Черный цвет" << endl;
			return;
			break;
		}
		else
			node = node->value > value ? node->nLeft : node->nRight;
	}
	cout << "Элемент не найден" << endl;
}
bool MyTree::MaxObject(NodeTree** root, NodeTree** res)
{
	NodeTree* node = *root;
	if (node->nLeft) {
		if (MaxObject(&node->nLeft, res)) return BalanceLeft(root);
	}
	else {
		*root = node->nRight;
		*res = node;
		return !node->red;
	}
	return false;
}
bool MyTree::Remove(NodeTree** root, int value)
{
	NodeTree* temp, * node = *root;
	if (!node) return false;
	if (node->value < value) {
		if (Remove(&node->nRight, value))
			return BalanceRight(root);
	}
	else if (node->value > value) {
		if (Remove(&node->nLeft, value))
			return BalanceLeft(root);
	}
	else {
		bool res;
		if (!node->nRight) {
			*root = node->nLeft;
			res = !node->red;
		}
		else {
			res = MaxObject(&node->nRight, root);
			temp = *root;
			temp->red = node->red;
			temp->nLeft = node->nLeft;
			temp->nRight = node->nRight;
			if (res) res = BalanceRight(root);
		}
		DeletRoot(node);
		return res;
	}
	return 0;
}
bool MyTree::AddNode(int value, NodeTree** root)
{
	NodeTree* node = *root;
	if (!node)*root = NewNode(value);
	else {
		if (value == node->value)
			return true;
		if (AddNode(value, value < node->value ? &node->nLeft : &node->nRight))   return true;
		Balance(root);
	}
	return false;
}
void MyTree::Show()
{
	Show(tree_root, 0, ' ');
}
void MyTree::AddNode(int value)
{
	AddNode(value, &tree_root);
	if (tree_root) tree_root->red = false;
}
void MyTree::RemoveMain(int value)
{
	Remove(&tree_root, value);
}
void MyTree::DeleteMain()
{
	Delete(tree_root);
	tree_root = 0;
}
int main()
{
	int n;
	setlocale(LC_ALL, "Russian");
	MyTree tree;
	printf("Введите количество узлов в дереве: ");
	cin >> n;
	int a;
	for (int i = 0; i < n; i++)
	{
		cout << "Введите элемент #" << i + 1 << " : ";
		cin >> a;
		tree.AddNode(a);
	}
	cout << "Дерево успешно создано и готово к работе" << endl;  while (true)
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "Выберите действие:" << endl;
		cout << "[1] - Добавить узел" << endl;
		cout << "[2] - Удалить узел" << endl;
		cout << "[3] - Вывести дерево" << endl;
		cout << "[4] - Найти элемент" << endl;
		cout << "[0] - Выйти из программы" << endl;
		cin >> a;
		cout << "---------------------------------------------------------------" << endl;
		switch (a)
		{
		case 1: {
			cout << "Введите элемент, который необходимо добавить в дерево: ";   cin >> a;
			tree.AddNode(a);
			cout << "Элемент '" << a << "' успешно добавлен в дерево" << endl;   break;
		}
		case 2:
		{
			cout << "Введите значение узла, который необходимо удалить: ";   cin >> a;
			cout << "Элемент '" << a << "' успешно удален" << endl;   tree.RemoveMain(a);
			break;
		}
		case 3:
		{
			cout << "Дерево: " << endl;
			tree.Show();
			cout << endl;
			break;
		}
		case 4:
		{
			cout << "Введите значние для поиска: ";
			cin >> a;
			tree.FindObject(a);
			break;
		}
		case 0:
		{
			tree.DeleteMain();
			return 0;
			break;
		}
		default:
			cout << "Ошибка!!! Введите команду от 1 до 4. Для выхода нажмите 0" << endl;
		}
	}
	return 0;
}
