#include <iostream>

using namespace std;

template<class T>
struct Node {
    T value_;
    int height_;
    int diff_;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;

    Node<T>() {
        height_ = 1;
        diff_ = 0;
    }
    Node<T>(T value) : value_(value) { Node<T>(); }
    Node<T>(const Node<T> &other) {
        value_ = other.value_;
        height_ = other.height_;
        diff_ = other.diff_;
    }
};

template<class T, class Compare = std::less<T>>
class BST {
public:
    template<class U>
    class Iterator {
    private:
        Node<U> *pointer_;
    public:
        Iterator() { pointer_ = nullptr; }
        Iterator(Node<U> *pointer) : pointer_(pointer) {}
        Iterator(const Iterator *other) : pointer_(other -> pointer_) {}
        Iterator(const Iterator &other) : pointer_(other.pointer_) {}

        Iterator &operator=(const Iterator &other) { this -> ~Iterator(); new (this) Iterator(other); return *this; }
        Iterator &operator=(const std::nullptr_t &other) { pointer_ = nullptr; return *this;}

        bool operator!=(Iterator const& other) const { return pointer_ != other.pointer_; }
        bool operator==(Iterator const& other) const { return pointer_ == other.pointer_; }
        U operator*() const { return pointer_ -> value_; }

        Iterator& operator++() { pointer_ = next_(pointer_, pointer_-> value_); return *this; }
        Iterator operator++(int) const { Iterator temp(this); ++(*this); return temp; }
        Iterator& operator--() { pointer_ = prev_(pointer_, pointer_-> value_); return *this; }
        Iterator operator--(int) const { Iterator temp(this); --(*this); return temp; }

        Node<U> *getPointer() { return pointer_; }
    };

    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;

    BST();
    BST(const BST &other);
    BST &operator=(const BST &other);
    ~BST();

    template<class InputIt>
    void assign(InputIt first, InputIt second) {
        BST<T, Compare>::iterator it = begin_;
        for (InputIt i = first; i != second; ++i, ++it) {
            *it = *i;
        }
        while (root_ -> diff > 2 || root_ -> diff < 2) {
            refresh_(root_);
        }
    }

    iterator begin() { return begin_; }
    iterator end() { return end_; }
    const_iterator begin() const { return begin_; }
    const_iterator end() const { return end_; }

    void insert(const T &value);
    void remove(const T &value);

    void print() const;

    bool exists(const T &x);
    size_t size() const;
private:
    Node<T> *root_;
    size_t size_;
    Iterator<T> begin_;
    Iterator<T> end_;
    Compare comp;

    void correctHeight(Node<T> *node);
    void smallLeft(Node<T> *node);
    void smallRight(Node<T> *node);
    void bigLeft(Node<T> *node);
    void bigRight(Node<T> *node);
    void refresh_(Node<T> *node);
    Node<T> *find_(Node<T> *node, const T &value);
    static Node<T> *next_(Node<T> *node, const T &value);
    static Node<T> *prev_(Node<T> *node, const T &value);
    void insert_(Node<T> *node, const T &value, Node<T> *parent);
    void remove_(Node<T> *node, const T &value);
    void print_(Node<T> *node) const;
    Node<T> *copy_(Node<T> *dest, Node<T> *parent, Node<T> *src);
};

template<class T, class Compare>
BST<T, Compare>::BST() {
    root_ = nullptr;
    size_ = 0;
    begin_ = nullptr;
    end_ = nullptr;
}

template<class T, class Compare>
BST<T, Compare>::BST(const BST &other) {
    root_ = copy_(root_, nullptr, other.root_);
    size_ = other.size_;
    begin_ = other.begin_;
    end_ = other.end_;
}

template<class T, class Compare>
BST<T, Compare> &BST<T, Compare>::operator=(const BST &other) {
    this -> ~BST();
    new (this) BST(other);
    return *this;
}

template<class T, class Compare>
BST<T, Compare>::~BST() {
    delete [] root_;
}

template<class T, class Compare>
void BST<T, Compare>::insert(const T &value) {
    insert_(root_, value, nullptr);
}

template<class T, class Compare>
void BST<T, Compare>::remove(const T &value) {
    Node<T> *node = find_(root_, value);
    remove_(node, value);
}

template<class T, class Compare>
bool BST<T, Compare>::exists(const T &value) {
    Node<T> *node = find_(root_, value);
    return node != nullptr;

}

template<class T, class Compare>
size_t BST<T, Compare>::size() const {
    return size_;
}

template<class T, class Compare>
void BST<T, Compare>::print() const {
    print_(root_);
}

template<class T, class Compare>
void BST<T, Compare>::correctHeight(Node<T> *node) {
    node -> height_ = max(
            node -> left == nullptr ? 0 : node -> left -> height_,
            node -> right == nullptr ? 0 : node -> right -> height_
    ) + 1;

    node -> diff_ = (node -> left == nullptr ? 0 : node -> left -> height_) -
            (node -> right == nullptr ? 0 : node -> right -> height_);
}

template<class T, class Compare>
void BST<T, Compare>::smallLeft(Node<T> *node) {
    Node<T> *temp = node -> right;

    node -> right = temp -> left;
    if (temp -> left != nullptr) {
        temp -> left -> parent = node;
    }

    temp -> left = node;
    if (node -> parent == nullptr) {
        root_ = temp;
        temp -> parent = nullptr;
    } else {
        if (node == node -> parent -> left)
            node -> parent -> left = temp;
        else node -> parent -> right = temp;
        temp -> parent = node -> parent;
    }
    node -> parent = temp;

    correctHeight(node);
    correctHeight(temp);
}

template<class T, class Compare>
void BST<T, Compare>::smallRight(Node<T> *node) {
    Node<T> *temp = node -> left;

    node -> left = temp -> right;
    if (temp -> right != nullptr) {
        temp -> right -> parent = node;
    }

    temp -> right = node;
    if (node -> parent == nullptr) {
        root_ = temp;
        temp -> parent = nullptr;
    } else {
        if (node == node -> parent -> left)
            node -> parent -> left = temp;
        else node -> parent -> right = temp;
        temp -> parent = node -> parent;
    }
    node -> parent = temp;

    correctHeight(node);
    correctHeight(temp);
}

template<class T, class Compare>
void BST<T, Compare>::bigLeft(Node<T> *node) {
    smallRight(node -> right);
    smallLeft(node);
}

template<class T, class Compare>
void BST<T, Compare>::bigRight(Node<T> *node) {
    smallLeft(node -> left);
    smallRight(node);
}

template<class T, class Compare>
void BST<T, Compare>::refresh_(Node<T> *node) {
    if (node == nullptr)
        return;

    correctHeight(node);

    if (node -> diff_ == -2) {
        node -> right -> diff_ == 1 ? bigLeft(node) : smallLeft(node);
    }

    if (node -> diff_ == 2) {
        node -> left -> diff_ == -1 ? bigRight(node) : smallRight(node);
    }

    correctHeight(node);
    refresh_(node->parent);
}

template<class T, class Compare>
Node<T> *BST<T, Compare>::find_(Node<T> *node, const T &value) {
    if (node == nullptr) {
        return node;
    }
    if (node -> value_ == value)
        return node;

    comp(node -> value_, value) ? find_(node -> right, value) : find_(node -> left, value);
}

template<class T, class Compare>
Node<T> *BST<T, Compare>::next_(Node<T> *node, const T &value) {
    Node<T> *ret = nullptr;
    while (node != nullptr) {
        if (value >= node -> value_) {
            node = node -> right;
        } else {
            ret = node;
            node = node -> left;
        }
    }
    return ret;
}

template<class T, class Compare>
Node<T> *BST<T, Compare>::prev_(Node<T> *node, const T &value) {
    Node<T> *ret = nullptr;
    while (node != nullptr) {
        if (value <= node -> value_) {
            node = node -> left;
        } else {
            ret = node;
            node = node -> right;
        }
    }
    return ret;
}

template<class T, class Compare>
void BST<T, Compare>::insert_(Node<T> *node, const T &value, Node<T> *parent) {
    if (node != nullptr && value == node -> value_)
        return;

    if (parent == nullptr && node == nullptr) {
        root_ = new Node<T>(value);
        begin_ = root_;
        end_ = root_;
        size_++;
        refresh_(node);
        return;
    }

    if (node == nullptr) {
        node = new Node<T>(value);
          parent -> value_ > node -> value_ ? parent -> left = node : parent -> right = node;
        node -> parent = parent;
        if (begin_.getPointer() == parent && node == parent -> left) {
            begin_ = node;
        } else if (end_.getPointer() == parent && node == parent -> right) {
            end_ = node;
        }
        size_++;
        refresh_(node);
        return;
    }

    value > node -> value_ ? insert_(node -> right, value, node) : insert_(node -> left, value, node);

}

template<class T, class Compare>
void BST<T, Compare>::remove_(Node<T> *node, const T &value) {
    if (node == nullptr)
        return;

    if (node -> left == nullptr && node -> right == nullptr) {
        if (node -> parent == nullptr) {
            root_ = nullptr;
            begin_ = nullptr;
            end_ = nullptr;
            return;
        }

        node == node -> parent -> right ? node -> parent -> right = nullptr : node -> parent -> left = nullptr;
        if (begin_.getPointer() == node) {
            begin_ = node -> parent;
        }
        if (end_.getPointer() == node) {
            end_ = node -> parent;
        }
        refresh_(node->parent);
        return;
    }

    if (node -> left != nullptr && node -> right != nullptr) {
        Node<T> *nextNode = next_(node->right, value);
        node -> value_ = nextNode -> value_;
        remove_(nextNode, value);
        return;
    }

    if (node -> left != nullptr) {
        if (node -> parent == nullptr) {
            root_ = node -> left;
            node -> left -> parent = nullptr;
            if (end_.getPointer() == node) {
                end_ = root_;
            }
            return;
        }
        if (node == node -> parent -> right) {
            node -> parent -> right = node -> left;
            node -> left -> parent = node -> parent;
            if (end_.getPointer() == node) {
                end_ = node -> left;
            }
        } else {
            node -> parent -> left = node -> left;
            node -> left -> parent = node -> parent;
        }

    } else {
        if (node -> parent == nullptr) {
            root_ = node -> right;
            node -> right -> parent = nullptr;
            if (begin_.getPointer() == node) {
                begin_ = root_;
            }
            return;
        }
        if (node == node -> parent -> right) {
            node -> parent -> right = node -> right;
            node -> right -> parent = node -> parent;
        } else {
            node -> parent -> left = node -> right;
            node -> right -> parent = node -> parent;
            if (end_.getPointer() == node) {
                end_ = node -> right;
            }
        }
    }
    size_--;
    refresh_(node->parent);
}

template<class T, class Compare>
void BST<T, Compare>::print_(Node<T> *node) const {
    if (node == nullptr)
        return;

    cout << node -> value_ << " - value; " << node -> height_ << " - height; " <<  node -> diff_ << " - diff " << endl;
    print_(node->left);
    print_(node->right);
}

template<class T, class Compare>
Node<T> *BST<T, Compare>::copy_(Node<T> *dest, Node<T> *parent, Node<T> *src) {
    if (src == nullptr) {
        return nullptr;
    }
    dest = new Node<T>(*src);
    dest -> parent = parent;
    dest -> left = copy_(dest -> left, dest, src -> left);
    dest -> right = copy_(dest -> right, dest, src -> right);
    return dest;
}

int main() {
    BST<int, std::less<int>> tree, tree2;
    string q;
    int x;
    BST<int, std::less<int>>::iterator b, e;

    while (!cin.eof()) {
        cin >> q;
        if (q == "insert") {
            cin >> x;
            tree.insert(x);
        } else if (q == "delete") {
            cin >> x;
            tree.remove(x);
        } else if (q == "exists") {
            cin >> x;
            tree.exists(x) ? std::cout << "true\n" : std::cout << "false\n";
        } else if (q == "copy") {
            tree2 = tree;
            tree2.remove(10);
            tree2.print();
            std::cout << "\n";
        }
        b = tree.begin();
        e = tree.end();
        std::cout << "*b = " << (*b) << ", *e = " << (*e) << ", ";
        BST<int, std::less<int>>::iterator b1 = ++b, e1 = --e;
        b1.getPointer() == nullptr ? cout << "b++ = null, " : cout << "b++ = " << *b1 << ", ";
        e1.getPointer() == nullptr ? cout << "e-- = null,\n" : cout << "e-- = " << *e1 << "\n";
        tree.print();
    }

    return 0;
}
