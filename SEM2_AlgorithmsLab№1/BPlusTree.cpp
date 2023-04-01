#include "BPlusTree.h"
#include <algorithm>
#include <iostream>
#include <string>

template<typename DataType>
BPlusNode<DataType>::BPlusNode() :
    leaf{ false },
    size{ 0 },
    key(),
    children(),
    nextLeaf{ nullptr },
    prevLeaf{ nullptr },
    parent{ nullptr } {}

template<typename DataType>
BPlusTree<DataType>::BPlusTree(unsigned minimum_degree) :
    _minimumDegree{ minimum_degree < 2 ? 2 : minimum_degree },
    _minNodeFill{ minimum_degree < 2 ? 1 : minimum_degree - 1 },
    _maxNodeFill{ minimum_degree < 2 ? 3 : 2 * minimum_degree - 1 },
    _root{ (std::make_shared<BPlusNode<DataType>>()) } {
    _root->leaf = true;
    _lenght = 0;
}
BPlusTree<int>::BPlusTree(unsigned minimum_degree);
BPlusTree<std::string>::BPlusTree(unsigned minimum_degree);

template<typename DataType>

void BPlusTree<DataType>::_printStep(std::shared_ptr<BPlusNode<DataType>> node, int level) {
    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }

    if (!node.get()) {
        std::cout << "*\n";
    }
    else {
        std::cout << "Root size: (" << node->size << ")\n";

        for (auto& item : node->key) {
            std::cout << '|';
            for (int i = 0; i < level; i++) {
                std::cout << '\t' << '|';
            }
            std::cout << item << "\n";
        }

        if (!node->leaf) {
            std::cout << '|';
            for (int i = 0; i < level; i++) {
                std::cout << '\t' << '|';
            }
            std::cout << "Children:\n";
            for (auto& item : node->children) {
                _printStep( item, level + 1);
            }
        }
    }
    std::cout << '|';
    for (int i = 0; i < level; i++) {
        std::cout << '\t' << '|';
    }
    std::cout << "=====\n";
}

template<typename DataType>
void BPlusTree<DataType>::Print() {
    _printStep( _root, 0);
}


template<typename DataType>

void BPlusTree<DataType>::PrintSorted() {
    Node_ptr ptr = _root;
    while (!ptr->leaf) {
        ptr = ptr->children[0];
    }

    int i = 0;
    while (ptr.get()) {
        for (auto& item : ptr->key) {
            std::cout << ++i << ") " << item << "\n";
        }
        ptr = ptr->nextLeaf;
    }
}
template<typename DataType>

std::vector<DataType>  BPlusTree<DataType>::GetSorted()
{
    std::vector<DataType> elements;
    Node_ptr ptr = _root;
    while (!ptr->leaf) {
        ptr = ptr->children[0];
    }

    int i = 0;
    while (ptr.get()) {
        for (auto& item : ptr->key) {
            elements.push_back(item);
        }
        ptr = ptr->nextLeaf;
    }
    return elements;
}
template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtreeSearch(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key) {
    if (subtree_root->leaf) {
        auto it = std::find(subtree_root->key.begin(), subtree_root->key.end(), key);
        if (it != subtree_root->key.end()) {
            return { subtree_root, std::distance(subtree_root->key.begin(), it) };
        }
        else {
            return { nullptr, 0 };
        }
    }
    else {
        unsigned index = 0;
        while (index < subtree_root->size && key >= subtree_root->key[index]) {
            index++;
        }
        return _subtreeSearch(subtree_root->children[index], key);
    }
}

template<typename DataType>
bool BPlusTree<DataType>::Includes(const DataType& key) {
    return _subtreeSearch(_root, key).first.get();
}

template<typename DataType>
void BPlusTree<DataType>::_splitNode(std::shared_ptr<BPlusNode<DataType>> node) {
    unsigned split_index = (node->size / 2);
    std::vector<DataType> data_first_part(node->key.begin(), node->key.begin() + split_index);
    std::vector<DataType> data_second_part(node->key.begin() + split_index, node->key.end());

    std::vector<Node_ptr> children_first_part(node->children.begin(), node->children.begin() + split_index + 1);
    std::vector<Node_ptr> children_second_part(node->children.begin() + split_index + 1, node->children.end());
    children_second_part.insert(children_second_part.begin(), nullptr);

    node->key = data_first_part;
    node->size = data_first_part.size();
    node->children = children_first_part;

    Node_ptr new_node = std::make_shared<BPlusNode<DataType>>();
    new_node->leaf = node->leaf;
    new_node->key = data_second_part;
    new_node->size = data_second_part.size();
    new_node->children = children_second_part;
    for (auto& item : new_node->children) {
        if (item.get()) {
            item->parent = new_node;
        }
    }

    if (!node->parent.get()) {
        Node_ptr new_parent = std::make_shared<BPlusNode<DataType>>();
        new_parent->leaf = false;
        new_parent->size = 1;
        new_parent->key = { data_second_part.front() };
        new_parent->children = { node, new_node };

        node->parent = new_parent;
        new_node->parent = new_parent;

        _root = new_parent;
    }
    else {
        Node_ptr parent = node->parent;
        new_node->parent = node->parent;
        unsigned index = 0; //max index of element, smaller than element to insert
        while (index < parent->size && data_second_part.front() > parent->key[index]) {
            index++;
        }

        parent->key.insert(parent->key.begin() + index, data_second_part.front());
        parent->size++;
        parent->children.insert(parent->children.begin() + index + 1, new_node);

        if (parent->size > _maxNodeFill) {
            _splitNode(parent);
        }
    }


    if (node->nextLeaf.get()) {
        new_node->nextLeaf = node->nextLeaf;
        node->nextLeaf->prevLeaf = new_node;
    }
    node->nextLeaf = new_node;
    new_node->prevLeaf = node;
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtreeInsert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key) {
    if (subtree_root->leaf) {
        unsigned index = 0; //max index of element, smaller than key
        while (index < subtree_root->size && key > subtree_root->key[index]) {
            index++;
        }
        if (subtree_root->key.empty()) {
            subtree_root->key.push_back(key);
            subtree_root->children.push_back(Node_ptr(nullptr));
            subtree_root->children.push_back(Node_ptr(nullptr));
        }
        else {
            subtree_root->key.insert(subtree_root->key.begin() + index, key);
            subtree_root->children.push_back(Node_ptr(nullptr));
        }
        subtree_root->size++;

        if (subtree_root->size > _maxNodeFill) {
            _splitNode(subtree_root);
        }

        return { subtree_root, index };

    }
    else {
        unsigned index = 0; //index of child where key should be insert
        while (index < subtree_root->size && key >= subtree_root->key[index]) {
            index++;
        }

        _subtreeInsert(subtree_root->children[index], key);
    }
    _lenght++;
    return std::pair<Node_ptr, unsigned int>();
}

template<typename DataType>
void BPlusTree<DataType>::Insert(const DataType& key) {
    if (!_root.get()) {
        _root = std::make_shared<BPlusNode<DataType>>();
        _root->leaf = true;
    }
    _subtreeInsert(_root, key);
}
void BPlusTree<int>::Insert(const int& key);

template<typename DataType>
void BPlusTree<DataType>::_removeFromNode(BPlusTree::Node_ptr node, unsigned index) {
    auto key = node->key[index];
    node->key.erase(node->key.begin() + index);
    node->children.erase(node->children.begin() + index + 1);
    node->size--;

    if (node == _root && node->size == 0) {
        _root = node->children[0];
        return;
    }
    if (node == _root) return;


    auto parent = node->parent;
    unsigned child_index = std::distance(parent->key.begin(),
        std::find_if(parent->key.begin(), parent->key.end(),
            [&key](const DataType& item) { return item > key; }));

    if (child_index > 0) parent->key[child_index - 1] = node->key[0];

    if (node->size >= _minNodeFill) return;

    auto left_sib = (child_index != 0) ? parent->children[child_index - 1] : nullptr;
    auto right_sib = (child_index < parent->size) ? parent->children[child_index + 1] : nullptr;

    if (left_sib.get() && left_sib->size - 1 >= _minNodeFill) {
        //take max element from left_sib;
        node->key.insert(node->key.begin(), left_sib->key.back());
        left_sib->key.pop_back();

        node->children.insert(node->children.begin() + 1, left_sib->children.back());
        left_sib->children.pop_back();

        node->size++;
        left_sib->size--;

        parent->key[child_index - 1] = node->key[0];
        return;
    }

    if (right_sib.get() && right_sib->size - 1 >= _minNodeFill) {
        //take min element from right_sib;
        node->key.push_back(right_sib->key[0]);
        right_sib->key.erase(right_sib->key.begin());

        node->children.push_back(right_sib->children[1]);
        right_sib->children.erase(right_sib->children.begin() + 1);

        node->size++;
        right_sib->size--;

        parent->key[child_index] = right_sib->key[0];
        return;
    }

    if (left_sib.get()) {
        //merge node with left_sib; recursively delete corresponding constraint element from parent;
        unsigned new_size = node->size + left_sib->size;

        std::vector<DataType> new_data;
        new_data.reserve(new_size);
        new_data.insert(new_data.end(), left_sib->key.begin(), left_sib->key.end());
        new_data.insert(new_data.end(), node->key.begin(), node->key.end());

        std::vector<Node_ptr> new_children;
        new_children.reserve(new_size + 1);
        new_children.insert(new_children.end(), left_sib->children.begin(), left_sib->children.end());
        new_children.insert(new_children.end(), node->children.begin() + 1, node->children.end());

        for (auto& item : new_children) {
            if (item.get())item->parent = left_sib;
        }

        left_sib->size = new_size;
        left_sib->key = new_data;
        left_sib->children = new_children;

        if (node->nextLeaf.get()) {
            node->nextLeaf->prevLeaf = left_sib;
            left_sib->nextLeaf = node->nextLeaf;
        }

        _removeFromNode(node->parent, child_index - 1);

        return;
    }

    if (right_sib.get()) {
        //merge node with right_sib; recursively delete corresponding constraint element from parent;
        unsigned new_size = node->size + right_sib->size;

        std::vector<DataType> new_data;
        new_data.reserve(new_size);
        new_data.insert(new_data.end(), node->key.begin(), node->key.end());
        new_data.insert(new_data.end(), right_sib->key.begin(), right_sib->key.end());

        std::vector<Node_ptr> new_children;
        new_children.reserve(new_size + 1);
        new_children.insert(new_children.end(), node->children.begin(), node->children.end());
        new_children.insert(new_children.end(), right_sib->children.begin() + 1, right_sib->children.end());

        for (auto& item : new_children) {
            if (item.get()) item->parent = node;
        }

        node->size = new_size;
        node->key = new_data;
        node->children = new_children;

        if (right_sib->nextLeaf.get()) {
            right_sib->nextLeaf->prevLeaf = node;
            node->nextLeaf = right_sib->nextLeaf;
        }

        _removeFromNode(node->parent, child_index);
        return;
    }
}


template<typename DataType>
void BPlusTree<DataType>::Remove(const DataType& key) {
    auto node = _subtreeSearch(_root, key).first;
    auto index = _subtreeSearch(_root, key).second;
    if (!node) return;

    _removeFromNode(node, index);
}
