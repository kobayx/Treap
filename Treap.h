#ifndef TREAP_H
#define TREAP_H
#include <iostream>
#include <stack>
#include <time.h>

template< typename Key, typename Value >
class Treap {
public:
	Treap() : root_(nullptr) {}

	Value& operator[](const Key& key);

	class Node {
	public:

		// I really like this compact style that you showed us
		Node(Key key) : key_(key), value_(), priority_(rand()), left_(nullptr), right_(nullptr) {}

		const Key& key() { return key_; }
		Value& value() { return value_; }
		Node* left() { return left_; }
		Node* right() { return right_; }


		Node* lookup(const Key key, Node* &root, Node* parent, Node* current, Node* retVal);
		Node* rotate(Node* &root, Node* parent, Node* current, Node* retVal, bool rightOrLeft);
		void dump(Node* dumpTreap);

	private:
		Key key_;
		Value value_;
		Node* left_;
		Node* right_;
		int priority_;
	};
	class Iterator {
	public:
		Iterator(Node* root);

		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);

		Iterator& operator++();
		const ::std::pair<const Key&, Value&> operator*();

	private:
		void leftmost(Node*p);
		Node* current_;
		std::stack<Node*> stack_;
	};
	Iterator end();
	Iterator begin();

private:
	Node * root_;

};

template<typename Key, typename Value>
inline Treap<Key, Value>::Iterator::Iterator(Node * root)
{
	if (!root) {
		current_ = nullptr;
		return;
	}
	leftmost(root);
	current_ = stack_.top();
	stack_.pop();
}

template<typename Key, typename Value>
inline typename Treap<Key, Value>::Iterator Treap<Key, Value>::begin()
{
	return Iterator(root_);
}

template<typename Key, typename Value>
inline typename Treap<Key, Value>::Iterator Treap<Key, Value>::end()
{
	return Iterator(nullptr);
}

template<typename Key, typename Value>
inline bool Treap<Key, Value>::Iterator::operator==(const Iterator & other)
{
	return current_ == other.current_;
}

template<typename Key, typename Value>
inline bool Treap<Key, Value>::Iterator::operator!=(const Iterator & other)
{
	return !(*this == other);
}

template<typename Key, typename Value>
inline typename Treap<Key, Value>::Iterator & Treap<Key, Value>::Iterator::operator++()
{
	leftmost(current_->right());
	if (stack_.empty()) {
		current_ = nullptr;
		return *this;
	}
	current_ = stack_.top();
	stack_.pop();

	return*this;
}

template<typename Key, typename Value>
inline const std::pair<const Key&, Value&> Treap<Key, Value>::Iterator::operator*()
{
	return std::pair<const Key&, Value&>(current_->key(), current_->value());
}

template<typename Key, typename Value>
inline void Treap<Key, Value>::Iterator::leftmost(Node * ptr)
{
	while (ptr) {
		stack_.push(ptr);
		ptr = ptr->left();
	}
}

template<typename Key, typename Value>
inline Value & Treap<Key, Value>::operator[](const Key & key)
{
	if (!root_) {
		root_ = new Node(key);
		return root_->value();
	}
	return root_->lookup(key, root_, root_, root_, root_)->value();// lookup returns a Node*, had to modify this return to compensate
}

template<typename Key, typename Value>
inline typename Treap<Key, Value>::Node * Treap<Key, Value>::Node::lookup(const Key key, Node* &root, Node* parent, Node* current, Node* retVal)
{
	if (key == current->key_) {
		return current;
	}
	// Left side of tree/subtree
	/////////////////////////////////////////////////////////////////////////////
	if (key < current->key_) {
		if (!current->left_) {
			current->left_ = new Node(key);
			retVal = current->left_;
			rotate(root, parent, current, retVal, false);
			return retVal;
		}
		else {
			if(parent->left_ == current || parent->right_ == current)
				retVal = lookup(key, root, current, current->left_, rotate(root, parent, current, retVal, false));
			else
				retVal = lookup(key, root, parent, current->left_, rotate(root, parent, current, retVal, false));
			rotate(root, parent, current, retVal, false);
			return retVal;
		}
	}
	// Right side of tree/subtree 
	/////////////////////////////////////////////////////////////////////////////
	if (key > current->key_) {
		if (!current->right_) {
			current->right_ = new Node(key);
			retVal = current->right_;
			rotate(root, parent, current, retVal, true);
			return retVal;
		}
		else {
			if (parent->right_ == current || parent->left_ == current)
				retVal = lookup(key, root, current, current->right_, rotate(root, parent, current, retVal, true));
			else 
				retVal = lookup(key, root, parent, current->right_, rotate(root, parent, current, retVal, true));
			rotate(root, parent, current, retVal, true);
			return retVal;
		}
	}
}

template<typename Key, typename Value>
inline typename Treap<Key, Value>::Node * Treap<Key, Value>::Node::rotate(Node* &root, Node* parent, Node* current, Node* retVal, bool rightOrLeft)// this = this->right/left_ temp = this
{
	if (rightOrLeft == true) { // right rotation
		if (retVal!= root && retVal->priority_ > current->priority_) {
			if (current == root) {
				root = retVal;
				parent->right_ = retVal->left_;
				retVal->left_ = parent;
				return retVal;
			}
			else {
				current->right_ = retVal->left_;
				retVal->left_ = current;
				if (retVal->key() > parent->key())
					parent->right_ = retVal;
				else
					parent->left_ = retVal;
				return retVal;
			}
		}
		else {
			return retVal;
		}
	} else {// left rotation
		if (retVal != root && retVal->priority_ > current->priority_) {
			if (current == root) {
				root = retVal;
				parent->left_ = retVal->right_;
				retVal->right_ = parent;
				return retVal;
			}
			else {
				current->left_ = retVal->right_;
				retVal->right_ = current;
				if (retVal->key() > parent->key())
					parent->right_ = retVal;
				else
					parent->left_ = retVal;
				return retVal;
			}
		}
		else {
			return retVal;
		}
	}
}

template<typename Key, typename Value>
inline void Treap<Key, Value>::Node::dump(Node* dumpTreap)
{
//	if (dumpTreap != nullptr) {
//		std::cerr << dumpTreap->key() << endl;
//		dumpTreap->dump(dumpTreap->right_);
//		dumpTreap->dump(dumpTreap->left_);
//	//	std:cerr << "end" << endl;
//	}
}

#endif
