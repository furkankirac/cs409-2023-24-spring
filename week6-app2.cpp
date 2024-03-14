// perfect forwarding

// Node<T> implementation with virtual functions + inheritance
// a List<T> implementation, go low-level, then implement with standard library
// move-ctor, move-assignment


#include <iostream>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!


struct NodeBase {
    NodeBase* next = nullptr;

    virtual void printYourself() = 0; // this is the 0th index at vtable
};

template<typename T>
struct Node : NodeBase
{
    T s;

    Node(const T& s) : s(s) {
        cout << "copy" << endl;
    } // copy c-tor
    Node(T&& s) : s(std::move(s)) {
        cout << "move" << endl;
    } // move c-tor

    void printYourself() override {
        cout << s << endl;
    }
};

struct List
{
    NodeBase* head = nullptr;

    List() { }
    List(NodeBase* head) : head(head) { }

    void push(NodeBase* ptr) {
        ptr->next = head;
        head = ptr;
    }
};


void print(const List& l) {
    auto* node = l.head;
    while(node) {
        node->printYourself();
        // cout << node->s << endl;
        node = node->next;
    }
}


int main(int argc, char* argv[])
{
    auto* node1_ptr = new Node(string("hello")); // string("hello") is r-value
    auto k = string("world");
    auto* node2_ptr = new Node<string>(k); // k is an l-value --> copy c-tor will be called

    auto* list = new List();

    auto* list2 = new List(node1_ptr);

    list->push(node2_ptr);

    cout << "!" << endl;
    list->push(new Node<string>("Blabla")); // const char[7] --->
    // (*list).push(node2_ptr);
    list->push(new Node<int>(10));

    print(*list);

    delete list;
    delete list2;

    return 0;
}
