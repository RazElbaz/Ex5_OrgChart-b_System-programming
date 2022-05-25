#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

namespace ariel {
    struct Node {
        string Name;
        vector<Node *> Sons;
    };

    class iterator {
    private:
        Node *pointer_to_current_node;
        string state;
        queue<Node*> levelorder;
        vector<Node*>preorder;
        vector<Node*> reverse;
        size_t index = 0;
    public:
        //----------------------------------------
        // constructors
        //----------------------------------------
        iterator():pointer_to_current_node(){}
        iterator(Node* ptr,string State):pointer_to_current_node(ptr){
            this->state= std::move(State);
            if(state=="LevelOrder"){
                this->levelorder.push(ptr);
            }
            else if(state=="Reverse"){
                ReverseTable(ptr);
                this->pointer_to_current_node = this->reverse.at(this->index++);
            }
            else if(state=="Preorder"){
                this->preorder.push_back(ptr);
            }
        }
        //----------------------------------------
        // operators
        //----------------------------------------
        string& operator*() const {
            if(this->pointer_to_current_node== nullptr){
                throw ("The current pointer is null");
            }
            return pointer_to_current_node->Name;
        }
        string* operator->() const  { return &(pointer_to_current_node->Name);}

        iterator& operator++() {
            this->pointer_to_current_node= nullptr;
            if(state=="LevelOrder") {
                LevelOrderTable();
                if (this->levelorder.size()>1) {
                    this->levelorder.pop();
                    this->pointer_to_current_node = levelorder.front();
                }
            }
            else if(state=="Reverse"){
                if(this->reverse.size()>=this->index+1){
                    this->pointer_to_current_node=this->reverse.at(this->index++);
                }
            }
            else if(state=="Preorder"){
                PreorderTable();
                if(!preorder.empty()){
                    this->pointer_to_current_node=preorder.at(this->preorder.size()-1);
                }
            }
            return *this;
        }

        friend bool operator==(const iterator &one, const iterator &two) {
            return one.pointer_to_current_node == two.pointer_to_current_node;
        }

        friend bool operator!=(const iterator &one, const iterator &two) {
            return one.pointer_to_current_node != two.pointer_to_current_node;
        }

        //----------------------------------------
        // Operator Auxiliary Functions
        //----------------------------------------
        void PreorderTable(){
            Node* curr=this->preorder.at(this->preorder.size()-1);
            this->preorder.pop_back();
            for(int i=int(curr->Sons.size()-1);i>=0;--i){
                preorder.push_back(curr->Sons.at((unsigned int)i));
            }
        }
        void LevelOrderTable(){
            Node *curr = this->levelorder.front();
            for (size_t i = 0; i < curr->Sons.size(); ++i) {
                this->levelorder.push(curr->Sons.at(i));
            }
        }
        void ReverseTable(Node* ptr){
            this->reverse.clear();
            vector<Node*> temp_vector;
            temp_vector.push_back(ptr);
            for (size_t i = 0; i < temp_vector.size(); i++){
                Node *temp_node = temp_vector[i];
                int indx=int(temp_node->Sons.size() - 1);
                while (indx>=0){
                    temp_vector.push_back((temp_node->Sons[(size_t)indx--]));}
            }
            for (int i =int(temp_vector.size()-1); i >= 0; i--){
                this->reverse.push_back(temp_vector[(size_t)i]);}
        }
    };
}