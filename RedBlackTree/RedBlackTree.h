#pragma once
#include <tuple>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

template <typename T> class RedBlackTree;

template <typename T>
std::ostream& operator<<(std::ostream& out, const RedBlackTree<T>& tree);

enum class RBTreeColor { BLACK = 1, RED = 31 };

template <typename T>
struct Node
{
	T data;
	RBTreeColor color;
	Node* parent;
	std::pair<Node*, Node*> children;
	bool sentinal = false;
};

template <typename T>
class RedBlackTree
{
public:
	RedBlackTree() : _root(nullptr), _height(0) {};
	
	template <typename ...K>
	void emplace(K... args);
	void insert(T data);

	bool find(const T& data) const;

	void remove(const T& data);

	bool empty() const { return _root == nullptr; }

	friend std::ostream& operator<< <T>(std::ostream& out, const RedBlackTree<T>& tree);

private:
	Node<T>* _root;
	int _height;

	void insert(Node<T>* n);
	void rotateLeft(Node<T>* n);
	void rotateRight(Node<T>* n);
	void fixInsert(Node<T>* n);
	void fixDeletion(Node<T>* n);

	void print (std::ostream& out, std::string leftText, Node<T>* n) const;

};

template<typename T>
inline void RedBlackTree<T>::insert(T data)
{
	Node<T>* n = new Node<T>;
	n->data = data;
	n->color = RBTreeColor::RED;
	n->parent = nullptr;
	n->children = std::make_pair(nullptr, nullptr);

	insert(n);
}

template<typename T>
inline bool RedBlackTree<T>::find(const T& data) const
{
	Node<T>* cur = _root;
	while (cur != nullptr)
	{
		if (data == cur->data)
			return true;

		if (data < cur->data)
			cur = cur->children.first;

		cur = cur->children.second;
	}

	return false;
}

template<typename T>
inline void RedBlackTree<T>::remove(const T& data)
{
	
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const RedBlackTree<T>& tree)
{
	tree.print(out, "", tree._root);

	return out;
}

template<typename T>
template<typename ...K>
inline void RedBlackTree<T>::emplace(K ...args)
{
	Node<T>* n =  new Node<T>;
	n->data = T(args...);
	n->children = std::make_pair(nullptr, nullptr);

	insert(n);
}

template<typename T>
inline void RedBlackTree<T>::insert(Node<T>* n)
{
	if (_root == nullptr)
	{
		_root = n;

		Node<T>* left = new Node<T>;
		Node<T>* right = new Node<T>;

		left->color = RBTreeColor::BLACK;
		right->color = RBTreeColor::BLACK;

		left->parent = _root;
		right->parent = _root;

		left->sentinal = true;
		right->sentinal = true;

		_root->children = std::make_pair(left, right);

		fixInsert(n);

		return;
	}

	Node<T>* cur = _root;
	int steps = 1;
	bool rightMost = true;

	while (true)
	{
		if (n->data < cur->data)
		{
			if (cur->children.first->sentinal)
			{
				Node<T>* temp = cur->children.first;
				temp->parent = n;

				n->children.first = temp;

				n->children.second = new Node<T>;
				n->children.second->color = RBTreeColor::BLACK;
				n->children.second->parent = n;
				n->children.second->sentinal = true;


				cur->children.first = n;
				n->parent = cur;

				if (steps > _height)
					_height++;


				fixInsert(n);

				return;
			}

			cur = cur->children.first;
			rightMost = false;
		}
		else
		{
			if (cur->children.second->sentinal)
			{
				Node<T>* temp = cur->children.second;
				temp->parent = n;

				n->children.first = temp;

				n->children.second = new Node<T>;
				n->children.second->color = RBTreeColor::BLACK;
				n->children.second->parent = n;
				n->children.second->sentinal = true;

				cur->children.second = n;
				n->parent = cur;

				if (steps > _height)
					_height++;

				fixInsert(n);

				return;
			}

			cur = cur->children.second;
		}

		steps++;
	}
}

template<typename T>
inline void RedBlackTree<T>::rotateLeft(Node<T>* n)
{
	auto temp = n->children.second;

	if (_root == n)
		_root = temp;
	else
	{
		if (n->parent->children.first == n)
			n->parent->children.first = temp;
		else
			n->parent->children.second = temp;
	}

	temp->parent = n->parent;
	n->parent = temp;

	n->children.second = temp->children.first;
	temp->children.first = n;
}

template<typename T>
inline void RedBlackTree<T>::rotateRight(Node<T>* n)
{
	auto temp = n->children.first;

	if (_root == n)
		_root = temp;
	else
	{
		if (n->parent->children.first == n)
			n->parent->children.first = temp;
		else
			n->parent->children.second = temp;
	}

	temp->parent = n->parent;
	n->parent = temp;

	n->children.first = temp->children.second;
	temp->children.second = n;
}

template<typename T>
inline void RedBlackTree<T>::fixInsert(Node<T>* n)
{
	while (n != _root && n->parent->color == RBTreeColor::RED)
	{
		if (n->parent->parent->children.first == n->parent)
		{
			Node<T>* y = n->parent->parent->children.second;
			if (y->color == RBTreeColor::RED)
			{
				n->parent->color = RBTreeColor::BLACK;
				y->color = RBTreeColor::BLACK;
				n->parent->parent->color = RBTreeColor::RED;
				n = n->parent->parent;
			}
			else
			{
				if (n == n->parent->children.second)
				{
					n = n->parent;
					rotateLeft(n);
				}

				n->parent->color = RBTreeColor::BLACK;
				n->parent->parent->color = RBTreeColor::RED;
				rotateRight(n->parent->parent);
			}
		}
		else
		{
			Node<T>* y = n->parent->parent->children.first;
			if (y->color == RBTreeColor::RED)
			{
				n->parent->color = RBTreeColor::BLACK;
				y->color = RBTreeColor::BLACK;
				n->parent->parent->color = RBTreeColor::RED;
				n = n->parent->parent;
			}
			else
			{
				if (n == n->parent->children.first)
				{
					n = n->parent;
					rotateRight(n);
				}

				n->parent->color = RBTreeColor::BLACK;
				n->parent->parent->color = RBTreeColor::RED;

				rotateLeft(n->parent->parent);
			}
		}
	}
	_root->color = RBTreeColor::BLACK;
}

template<typename T>
inline void RedBlackTree<T>::fixDeletion(Node<T>*n)
{}

template<typename T>
inline void RedBlackTree<T>::print(std::ostream& out, std::string leftText, Node<T>*n) const
{
	
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& n)
{
	out << "\33[" << (int)n.color << "m" << n.data << "\33[m";
	return out;
}
