#include <iostream>
#include <vector>
#include <string>
#include "iterator.hpp"
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
namespace ariel {
    class OrgChart {
    private:
        Node root;
        vector<Node*>children;
        int index;
        bool LookFor(Node *root,const string &father,const string &son);

    public:
        //----------------------------------------
        // constructors
        //----------------------------------------
        //contracture
        OrgChart(){
            this->root.Name= "";
            this->index=0;
        }
        //deep copy
        OrgChart(OrgChart &other){
            if(!other.root.Name.empty()){ this->root=other.root;}
            for (int i = 0; i < other.root.Sons.size(); ++i) {
                Node* curr=other.root.Sons[(size_t)i];
                this->root.Sons[(size_t )i]=curr;
                for (int j = 0; j < curr->Sons.size(); ++j) {
                    this->children[(size_t )j]=other.children[(size_t )j];
                }
            }
            this->index=other.index;
        }
        //Move constructors, credit: https://www.educative.io/edpresso/what-is-a-move-constructor-in-cpp
        OrgChart(OrgChart &&other)noexcept{
            this->root=other.root;
            this->children=other.children;
            this->index=other.index;
        }

        //----------------------------------------
        // operators
        //----------------------------------------
        //https://en.cppreference.com/w/cpp/language/move_assignment
        //move operator in C++ : the move assignment operator = is used for transferring a temporary object to an existing object
        OrgChart& operator=(OrgChart &&other)noexcept=default;
        OrgChart& operator=(const OrgChart &other){
            if (this==&other){
                return *this;}
            //I was helped by Lecture 5
            //delete these children
            for(Node* node: this->children){
                removeOrgChart(node);
            }
            //copy
            for (int i = 0; i < other.root.Sons.size(); ++i) {
                Node* curr=other.root.Sons[(size_t)i];
                this->root.Sons[(size_t )i]=curr;
                for (int j = 0; j < curr->Sons.size(); ++j) {
                    this->children[(size_t )j]=other.children[(size_t )j];
                }
            }
            return *this;
        }
        void removeOrgChart(Node* node_del) {
            if (node_del != nullptr) {
            for (int i = 0; i < node_del->Sons.size(); ++i) {
                removeOrgChart(node_del->Sons[(size_t)i]);
            }
            delete node_del;
        }
        }
        //----------------------------------------
        //  Functions
        //----------------------------------------
        OrgChart &add_root(string name);
        OrgChart &add_sub(const string &nameONE,const string &nameTWO);
        friend ostream &operator<<(ostream &output, OrgChart &start);
        void print(Node &node, string s, bool isLast);
        Node getRoot() { return this->root;}
        //Return of iterator
        iterator begin_level_order();
        iterator end_level_order()const;
        iterator begin_preorder();
        iterator begin_reverse_order();
        iterator end_preorder()const;
        iterator reverse_order()const;
        iterator begin();
        iterator end()const;

        //destructor
        ~OrgChart(){
            for(Node* node: this->children){
                delete node;
            }
        }
    };
}