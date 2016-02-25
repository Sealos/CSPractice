#pragma once

template<typename T>
struct BinaryTreeIterator;

template<typename T>
struct TreeNode;

template<typename T>
struct TreeNode {

	using Node = std::unique_ptr<TreeNode>;

	T item;
	Node left;
	Node right;
	TreeNode *parent;
	TreeNode(const T &value, TreeNode *parent) : item(value), left(nullptr), right(nullptr), parent(parent) {}
	void print() const {
		std::cout << "Item " << item << std::endl;
	}

	void set_left(std::unique_ptr<TreeNode> &&n) {
		left = std::move(n);
	}

	void set_right(std::unique_ptr<TreeNode> &&n) {
		right = std::move(n);
	}
};

template<typename T>
class BinaryTree {
public:
	using Node = std::unique_ptr<TreeNode<T>>;

	void print() const {
		for (auto iter = begin(); iter != end(); ++iter) {
			std::cout << *iter << std::endl;
		}
	}

	void print_in_order() {
		print_in_order(root);
	}

	void print_in_order(Node const &node) {
		if (node == nullptr) {
			return;
		}

		print_in_order(node->left);
		node->print();
		print_in_order(node->right);
	}

	BinaryTreeIterator<T> begin() const {
		if (root == nullptr) {
			return BinaryTreeIterator<T>(nullptr);
		} else {
			TreeNode<T> *node = get_leftmost_node(root);
			return BinaryTreeIterator<T>(node);
		}
	}

	BinaryTreeIterator<T> end() const {
		return BinaryTreeIterator<T>(nullptr);
	}

protected:
	Node root;

private:
	inline TreeNode<T> *get_leftmost_node(Node const &node) const {
		if (node->left == nullptr) {
			return node.get();
		} else {
			return get_leftmost_node(node->left);
		}
	}

	inline TreeNode<T> *get_rightmost_node(Node const &node) const {
		if (node->right == nullptr) {
			return node.get();
		} else {
			return get_rightmost_node(node->right);
		}
	}
};

template<typename T>
struct BinaryTreeIterator {
public:
	BinaryTreeIterator(TreeNode<T> *node) : node_ptr(node) {}

	const BinaryTreeIterator& operator++() {
		if (node_ptr == nullptr) {
			return *this;
		}

		if (node_ptr->right != nullptr) {
			node_ptr = node_ptr->right.get();
			while (node_ptr->left != nullptr) {
				node_ptr = node_ptr->left.get();
			}
		} else {
			auto temp = node_ptr->parent;
			while ((temp) && (node_ptr == temp->right.get())) {
				node_ptr = temp;
				temp = temp->parent;
			}

			if (node_ptr->right.get() != temp) {
				node_ptr = temp;
			}
		}
		return *this;
	};

	BinaryTreeIterator operator++(int) {
		auto result = *this;
		++(*this);
		return result;
	};

	bool operator==(const BinaryTreeIterator &iter) const {
		return node_ptr == iter.node_ptr;
	};

	bool operator!=(const BinaryTreeIterator &iter) const {
		return !(*this == iter);
	};

	T operator*() const {
		return node_ptr->item;
	};

	void print() {
		if (node_ptr) node_ptr->print();
	}

private:
	TreeNode<T> *node_ptr;
};