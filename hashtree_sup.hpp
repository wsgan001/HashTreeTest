#ifndef HASHTREESUP_HPP
#define HASHTREESUP_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

template<typename Data, class Hasher>
class HashTreeSup
{
    typedef std::vector<Data> Itemset;
    typedef std::pair<std::vector<Data>,unsigned long> ItemsetSup;
public:
    HashTreeSup();
    ~HashTreeSup();
    void insert(const ItemsetSup& d);
    unsigned long contains(const Itemset& d) const;
    unsigned int getCap() const {return capacity;}
    void erase();
    void out(std::ofstream &stream);
private:
    static const int size = 10;
    unsigned capacity;
    struct Node{
        std::list<ItemsetSup> data;
        std::vector<Node*> children;
        Node();
    };
    void out(std::ofstream& stream, Node * p, unsigned n);
    Node * root;
    Hasher hash;
    void erase_rec(Node* p);
};

template<typename Data, class Hasher>
HashTreeSup<Data, Hasher>::HashTreeSup() :  capacity(0), root(new Node)
{
    root->children.resize(size);
}

template<typename Data, class Hasher>
HashTreeSup<Data, Hasher>::~HashTreeSup(){
    erase();
}

template<typename Data, class Hasher>
HashTreeSup<Data, Hasher>::Node::Node() : children(size){}

template<typename Data, class Hasher>
void HashTreeSup<Data, Hasher>::insert(const ItemsetSup& d){
    Node * p = root;
    for(auto i = d.first.begin(); i !=  d.first.end(); ++i){
        unsigned h = hash( *i );
        if( p->children[h] == nullptr){
            p->children[h] = new Node;
            capacity++;
        }
        if( i == d.first.end()-1  ){
            p->children[h]->data.push_back(d);
            return;
        }else{
            p = p->children[h];
        }
    }
}

template<typename Data, class Hasher>
unsigned long HashTreeSup<Data, Hasher>::contains(const Itemset &d) const{
    Node * p = root;
    for(unsigned int i = 0; i < d.size(); ++i){
        unsigned h = hash( d[i] );
        if( p->children[h] == nullptr){
            return false;
        }else{
            p = p->children[h];
        }
    }
    auto res = std::find_if(p->data.begin(),p->data.end(),[&](ItemsetSup& x){return d == x.first;});
    if(res != p->data.end()){
        return (*res).second;
    }else{
        return 0;
    }
}

template<typename Data, class Hasher>
void HashTreeSup<Data, Hasher>::erase(){
    erase_rec(root);
}

template<typename Data, class Hasher>
void HashTreeSup<Data, Hasher>::erase_rec(Node *p){
    bool empty = true;
    if( nullptr != p ){
        for( auto it = p->children.begin(); it != p->children.end(); ++it){
            if( *it != nullptr){
                empty = false;
                break;
            }
        }
        if(empty){
            if(p) delete p;
        }else{
            for(int i = 0; i< size;++i)
                erase_rec(p->children[i]);
        }
    }
}

template<typename Data, class Hasher>
void HashTreeSup<Data,Hasher>::out(std::ofstream& stream){
    out(stream,root,1);
}

template<typename Data, class Hasher>
void HashTreeSup<Data,Hasher>::out(std::ofstream& stream, Node * p, unsigned n){
    if(p->data.size() > 0){
        for(auto& x : p->data){
            for (unsigned i = 0; i < n-1; ++i) {
                stream << ' ';
            }
            for(auto& y : x.first){
                stream << ' ' << y;
            }
            stream << ';';
        }
        stream << std::endl;
    }
    for(auto x : p->children){
        if(x != nullptr){
            out(stream,x,n+1);
        }
    }
}

#endif // HASHTREESUP_HPP
