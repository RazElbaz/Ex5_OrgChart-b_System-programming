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
        Node *pointer_to_current_node; //The name is taken from the lecture
        string state;
        queue<Node*> levelorder;
        vector<Node*>preorder;
        vector<Node*> reverse;
        size_t index = 0;
    public:
        //--------------------------------------------------------------------------------------------------------------
        // constructors
        //--------------------------------------------------------------------------------------------------------------
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
        //--------------------------------------------------------------------------------------------------------------
        // operators
        //--------------------------------------------------------------------------------------------------------------
        string& operator*() const {
            if(this->pointer_to_current_node== nullptr){
                throw ("The current pointer is null");
            }
            return pointer_to_current_node->Name;
        }
        string* operator->() const  { return &(pointer_to_current_node->Name);}

        iterator& operator++() {
            /***
             * This function checks the state of transition on the OrgChart and determines
             * the current pointer accordingly to return the pointer instead of the ++
             */
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

        //--------------------------------------------------------------------------------------------------------------
        // Operator Auxiliary Functions
        //--------------------------------------------------------------------------------------------------------------
        void PreorderTable(){
            /***
             * This function takes the sons of the root and inserts them in the order of Preorder
               explain: We go through the whole child from the top of the root from right to left, and put the child in a pile
             */
            Node* curr=this->preorder.at(this->preorder.size()-1);
            this->preorder.pop_back();
            for(int i=int(curr->Sons.size()-1);i>=0;--i){
                preorder.push_back(curr->Sons.at((unsigned int)i));
            }
        }
        void LevelOrderTable(){
            /***
             * This function takes the sons of the root and inserts them in the order of by level
               explain: In this function we take NODE each time and put its children in the queue
             */
            Node *curr = this->levelorder.front();
            for (size_t i = 0; i < curr->Sons.size(); ++i) {
                this->levelorder.push(curr->Sons.at(i));
            }
        }
        void ReverseTable(Node* ptr){
            /***
              This function takes the sons of the root and keeps them in the vector of the NODES of the class in reverse order
              explain: In this function we get a root, push it a temporary locator, then go over each of its children and put them in reverse order.
                       Finally, we will copy the class' temporary vector
             */
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