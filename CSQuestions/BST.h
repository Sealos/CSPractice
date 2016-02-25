#pragma once

template<typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
	bool insert(const T &value) {
		if (root == nullptr) {
			root = std::make_unique<TreeNode<T>>(value, nullptr);
		}

		return insert(root, value);
	}

	bool exists(const T &value) const {
		for (auto iter = begin(); iter != end(); iter++) {
			if (*iter == value) {
				return true;
			}
		}

		return false;
	}

	bool remove(const T &value) {
		if (root == nullptr) {
			return false;
		} else {
			if (root->item == value) {
				// TODO
				return false;
			} else {
				return remove(root, nullptr, value);
			}
		}
	}

private:
	inline bool insert(Node const &n, const T &value) {
		if (n->item == value) {
			return false;
		} else if (n->item > value) {
			if (n->left == nullptr) {
				n->left = std::make_unique<TreeNode<T>>(value, n.get());
			} else {
				return insert(n->left, value);
			}
		} else {
			if (n->right == nullptr) {
				n->right = std::make_unique<TreeNode<T>>(value, n.get());
			} else {
				return insert(n->right, value);
			}
		}

		return true;
	}

	inline bool remove(Node const &node, TreeNode<T> *parent, const T &value) {
		if (node->item > value) {
			if (node->left != nullptr) {
				return remove(node->left, node.get(), value);
			} else {
				return false;
			}

		} else if (node->item < value) {
			if (node->right != nullptr) {
				return remove(node->right, node.get(), value);
			} else {
				return false;
			}
		} else {
			if (node->left != nullptr && node->right != nullptr) {
				node->item = min_value(node->right);
				return remove(node->right, node.get(), node->item);
			} else if (parent->left == node) {
				if (node->left != nullptr) {
					parent->set_left(std::move(node->left));
				} else {
					parent->set_left(std::move(node->right));
				}
			} else if (parent->right == node) {
				if (node->left != nullptr) {
					parent->set_right(std::move(node->left));
				} else {
					parent->set_right(std::move(node->right));
				}
			}

			return true;
		}
	}

	inline T min_value(Node const &n) {
		if (n->left == nullptr) {
			return n->item;
		} else {
			return min_value(n->left);
		}
	}
};