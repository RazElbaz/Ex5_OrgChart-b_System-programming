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
        if (!LookFor(&this->root, nameONE, nameTWO)) {
            throw runtime_error("The first person the Knesset does not exist in the organization tree!") ;
        }
        return *this;
    }

    bool OrgChart::LookFor(Node *root, const string &father,const string &son) {
    //check it the father is the root
        bool ans=false;
        if(root->Name==father){
            Node* temp=new Node();
            temp->Name=son;
            root->Sons.push_back(temp);
            this->children.push_back(temp);
            ans=true;
        }
        else{//if the father is not the root we will look for him
            for(int i=0;i<root->Sons.size();++i){
                if(LookFor(root->Sons.at((unsigned int)i),father, son)){
                    return true;
                }
            }
        }
        return ans;
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

    //I used the website https://www.geeksforgeeks.org/introduction-iterators-c/
    ostream &operator<<(ostream &output, OrgChart &start) {
//        for (auto i = start.begin(); i != start.end(); ++i) {
//            output << (*i) << " ";
//            output << "->";
//        }
        output<<start.root.Name<<"->"<<endl;
        for (int i = 0; i < start.root.Sons.size(); ++i) {
        Node* curr = start.root.Sons.at((size_t)i);
        output<<curr->Name<<"->"<<endl;
        for (int j = 0; j < curr->Sons.size(); ++j) {
            output<<(curr->Sons.at((size_t) j)->Name);
            output << "->";
        }
        output<<"\n";
        }
        return  output;
    }
}