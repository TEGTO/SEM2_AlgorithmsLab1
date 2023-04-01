#pragma once
#include <memory>
#include<iostream>
#include <vector>
//клас для опису вузла В+ -дерева, містить вектр даних та вектор покажчиків на дітей 

template<typename DataType>
class BPlusNode {
    typedef std::shared_ptr<BPlusNode> Node_ptr;
public:
    bool leaf;
    unsigned size;
    std::vector<DataType> key;
    std::vector<Node_ptr> children;
    Node_ptr nextLeaf;
    Node_ptr prevLeaf;
    Node_ptr parent;
    //конструктор 
    BPlusNode();
};

//клас самого В+ -дерева
template<typename DataType>
class BPlusTree {
    typedef std::shared_ptr<BPlusNode<DataType>> Node_ptr;
private:
    unsigned _minimumDegree;
    unsigned _minNodeFill;
    unsigned _maxNodeFill;
    unsigned _lenght;
    Node_ptr _root;


    void _printStep( std::shared_ptr<BPlusNode<DataType>> node, int level);//функція для вивіду деерева на консоль

    std::pair<Node_ptr, unsigned> _subtreeSearch(std::shared_ptr<BPlusNode<DataType>> subtreeRoot, const DataType& key);//пошук элемента у піддереві

    void _splitNode(std::shared_ptr<BPlusNode<DataType>> node);//функція розділяє дерево на два піддерева

    std::pair<Node_ptr, unsigned> _subtreeInsert(std::shared_ptr<BPlusNode<DataType>> subtreeRoot, const DataType& key);//функція для додавання елемента у піддерево

    void _removeFromNode(Node_ptr node, unsigned index);//функція для видалення елемента з піддерева

public:

    explicit BPlusTree(unsigned minimum_degree = 2);//конструктор

  
    void Print();//функція для вивіду деерева на консоль
  

   
    void PrintSorted();//функція для вивіду деерева на консоль в порядку зростання елементів
    std::vector<DataType>  GetSorted();//функція для того щоб отримати сортурованні елементи

    bool Includes(const DataType& key);//функція яка перевіряє наявність елемента в дереві

    void Insert(const DataType& key);//функція для додавання елемента у дерево

    void Remove(const DataType& key);//функція для видалення елемента з дерева
};

template BPlusTree<int>;
template BPlusNode<int>;
template BPlusTree<std::string>;
template BPlusNode<std::string>;
