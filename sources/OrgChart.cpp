#include "OrgChart.hpp"
using namespace std;
namespace ariel {
    OrgChart &OrgChart::add_root(string name) {
        if (name.empty() || name == "\t"|| name == "\r" || name == "\n"|| name == " " ){
            throw invalid_argument("One or both of the strings are invalid");
        }
        this->root.Name = move(name);
        return *this;
    }

    OrgChart &OrgChart::add_sub(const string &nameONE, const string &nameTWO) {
        if (nameONE.empty() || nameTWO.empty() || nameONE == "\t" || nameTWO == "\t"|| nameTWO == "\r" || nameONE == "\r"|| nameTWO == "\n" || nameTWO == "\n"|| nameONE == " " || nameTWO == " " ){
            throw invalid_argument("One or both of the strings are invalid");
        }
        if (!LookForNode(&this->root, nameONE, nameTWO)) {
            throw runtime_error("The first person the Knesset does not exist in the organization tree!") ;
        }
        return *this;
    }

    bool OrgChart::LookForNode(Node *root, const string &father,const string &son) {
        bool ans= false;
        if(root->Name==father) { //check it the father is the root
            AddNode(root, father,son);
            ans= true;
        }
        else{//if the father is not the root we will look for him
            for(int i=0;i<root->Sons.size();++i){
                if(LookForNode(root->Sons.at((unsigned int)i),father, son)){
                    ans= true;
                }}
        }
        return ans;
    }
    void OrgChart::AddNode(Node *root, const string &father, const string &son) {
        Node* temp=new Node();
        temp->Name=son;
        root->Sons.push_back(temp);
        this->children.push_back(temp);
    }


    iterator OrgChart::begin_level_order() {
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator(&this->root, "LevelOrder");
    }

    iterator OrgChart::end_level_order() const{
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator();
    }

    iterator OrgChart::begin_reverse_order() {
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator(&this->root, "Reverse");
    }

    iterator OrgChart::begin_preorder() {
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator(&this->root, "Preorder");
    }

    iterator OrgChart::end_preorder() const{
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator();
    }

    iterator OrgChart::reverse_order() const{
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator();
    }

    iterator OrgChart::begin() {
        if (this->root.Name.empty()) {
            throw "This chart not exist";
        }
        return iterator(&this->root, "LevelOrder");
    }

    iterator OrgChart::end() const{
        if (this->root.Name.empty()) {
            throw runtime_error("This chart not exist");
        }
        return iterator();
    }
     string& OrgChart::print(string& oldString, const string& start, Node *node){
        oldString += start;
        if(!oldString.empty()){oldString += "->";}
        oldString = oldString+ node->Name+"\n";
        for(int i = 0; i < node->Sons.size(); ++i){
            print(oldString, start + "\t", (node->Sons[(size_t)i]));
        }
        return oldString;
    }
    ostream &operator<<(ostream &output, OrgChart &start) {
        if(start.root.Name.empty()){throw "Error:this OrgChart is empty";}
        string oldString;
        output << OrgChart::print(oldString, "", &start.root);
        return output;
    }
}