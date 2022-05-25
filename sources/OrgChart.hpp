
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
        //contracture
        OrgChart(){
            this->root.Name= "";
            this->index=0;
        }
        OrgChart(OrgChart &other);
        OrgChart(OrgChart &&other)noexcept;
        OrgChart& operator=(OrgChart &&other)noexcept;
        OrgChart& operator=(const OrgChart &other);
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