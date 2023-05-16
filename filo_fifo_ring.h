//
// Created by User on 05.04.2023.
//

#ifndef WORK_ON_LESSON_FILO_FIFO_RING_H
#define WORK_ON_LESSON_FILO_FIFO_RING_H
#include <fstream>
#include <vector>
template <typename T>
class IData{
public:
    T*ar;
    int size1;
    int datalen=0;
public:
    IData(){}
    virtual bool addToEnd(T el){return false;}
    virtual bool getFromEnd(T& el){};
    virtual ~IData(){}
};
template <class T>
class Filo:public IData<T>{
public:
    Filo(){
        IData<T>::datalen=0;
        IData<T>::size1=9;
        IData<T>::ar=new T [IData<T>::size1];
    }
    Filo(int size){
        IData<T>::datalen=0;
        IData<T>::size1=size;
        IData<T>::ar=new T [IData<T>::size1];
    }
    bool addToEnd (T el) override{
        if(IData<T>::datalen==IData<T>::size1){
            return false;
        }
        IData<T>::ar[IData<T>::datalen++]=el;
        return true;
    }
    bool getFromEnd(T& el) override{
        if(IData<T>::datalen==0){
            return false;
        }
        el=IData<T>::ar[--IData<T>::datalen];
        return true;
    }
    void output(){
        std::cout<<"Filo: ";
        for (int i = 0; i<IData<T>::datalen; i++) {
            std::cout<<IData<T>::ar[i]<<std::endl;
        }
    }
    ~Filo(){
        IData<T>::datalen=0;
        IData<T>::size1=0;
        delete[] IData<T>::ar;
        IData<T>::ar=nullptr;
    }
};
template <class T>
class Fifo:public IData<T> {
public:
    Fifo(){
        IData<T>::datalen=0;
        IData<T>::size1=128;
        IData<T>::ar=new T [IData<T>::size1];
    }
    Fifo(int size){
        IData<T>::datalen=0;
        IData<T>::size1=size;
        IData<T>::ar=new T [size];
    }
    bool addToEnd(T el) override {
        if (IData<T>::datalen == IData<T>::size1) {
            return false;
        }
        IData<T>::ar[IData<T>::datalen++] = el;
        return true;
    }

    bool getFromEnd(T &el) override {
        if (IData<T>::datalen == 0) {
            return false;
        }
        el = IData<T>::ar[0];
        for (int i = 1; i < IData<T>::datalen; ++i) {
            IData<T>::ar[i - 1] = IData<T>::ar[i];
        }
        IData<T>::datalen--;
        return true;
    }
    ~Fifo(){
        IData<T>::datalen=0;
        IData<T>::size1=0;
        delete[] IData<T>::ar;
        IData<T>::ar= nullptr;
    }
};
template <class T>
class ringBuffer:public IData<T>{
private:
    int beginData;
    int endData;
public:
    ringBuffer(){
        IData<T>::size1=128;
        IData<T>::ar=new T [128];
    }
    ringBuffer(int size){
        IData<T>::size1=size;
        IData<T>::ar=new T [size];
    }
    bool addToEnd(T el) override{
        if(IData<T>::datalen==IData<T>::size1){
            return false;
        }
        IData<T>::datalen++;
        IData<T>::ar[endData++]=el;
        if(endData==IData<T>::size1){
            endData=0;
        }
        return true;
    }
    bool getFromBegin(T& el) override{
        if(IData<T>::datalen==0){
            return false;
        }
        IData<T>::datalen--;
        el=IData<T>::ar[beginData++];
        if(beginData==IData<T>::size1){
            beginData=0;
        }

    }
};
template <class T>
class LinkNodes  {
public:
    LinkNodes* next;
    LinkNodes* prev;
    T nameNode;
    virtual void writeToFileFromTail(){}
    virtual void writeToFileFromHead(){}
    virtual bool insert(T el, int position){ return false;}
    virtual ~LinkNodes(){}
};

template <class T>
class LinkedList: public LinkNodes<T>,public IData<T>{
public:
        LinkNodes<T>* Head= nullptr;
        LinkedList() {
            Head = new LinkNodes<T>;
            Head->next = nullptr;
            IData<T>::datalen++;
        }
       LinkedList(T value) {
               Head = new LinkNodes<T>;
               Head->next = nullptr;
               Head->nameNode = value;
                IData<T>::datalen++;
       }
      LinkedList(LinkedList<T>& lst){
           this->DeleteList();
           LinkNodes<T>* temp =lst.Head;
           while(temp!= nullptr){
               this->addToEnd(temp->nameNode);
               temp=temp->next;
           }
        }
        void DeleteList(){
            for (int i = 0; i <IData<T>::datalen; ++i) {
                LinkNodes<T>* temp =Head;
                Head=Head->next;
                if(Head==NULL){
                    break;
                }
                delete temp;
            }
        }
        ~LinkedList(){
           for (int i = 0; i <IData<T>::datalen; ++i) {
               if(Head==NULL){
                   break;
               }
               LinkNodes<T>* temp =Head;
               Head=Head->next;

               delete temp;
           }
        }
        int getValue () const{
            return this->nameNode;
        }
        bool addToEnd(T name) override{
            if(Head== nullptr){
                Head=new LinkNodes<T>;
                Head->nameNode=name;
                Head->next= nullptr;
                IData<T>::datalen++;
                return true;
            }
            LinkNodes<T>* temp=Head;
            for (int i = 0; temp->next!= nullptr; ++i) {
                temp=temp->next;
            }
            temp->next=new LinkNodes<T>;
            temp=temp->next;
            temp->nameNode=name;
            temp->next= nullptr;
            IData<T>::datalen++;
            return true;
        }
        bool insert(T el, int position) override{
            if(position>IData<T>::datalen+1){
                std::cout<<"The list is not replenished"<<std::endl;
                return false;
            }
            if(position>0) {
                LinkNodes<T>* temp;
                LinkNodes<T>* middle=Head;
                for (int i = 0; i <position-1; ++i) {
                    middle=middle->next;
                }
                temp=middle->next->next;
                middle->next=new LinkNodes<T>;
                middle->next->nameNode=el;
                middle->next->next=temp;
                return true;
            }
            else{
                if(position==0){
                    LinkNodes<T>* temp =new LinkNodes<T>;
                    temp->next=Head->next;
                    temp->nameNode=el;
                    Head=temp;
                    IData<T>::datalen++;
                }
            }
        }
        void writeToFileFromHead()override {
            LinkNodes<T>* temp=Head;
            std::ofstream flog("LinkLs_res.txt",std::ios::out);
            for (int i = 0; temp!= nullptr; ++i) {
                 flog<<i+1<<"\t"<<temp->nameNode<<"\n";
                 temp=temp->next;
            }
            flog.close();
        }
        int& operator[](int index){
            LinkNodes<T>* temp=Head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->nameNode;
        }
        bool operator==(LinkedList<T>& first){
            if(first.datalen!=this->datalen){
                return false;
            }else{
                LinkNodes<T>* temp=first.Head;
                LinkNodes<T>* sec_temp=Head;
                while (temp->next!= nullptr) {
                    if(sec_temp->nameNode!=temp->nameNode){
                        return false;
                    }
                    temp=temp->next;
                    sec_temp=sec_temp->next;
                }
                return true;
            }

        }

    //Мне руку на сердце, на грудь и на бёдра.
        void operator =(LinkedList<T>& first){
            this->DeleteList();
            LinkNodes<T>* temp=first.Head;
            while(temp!= nullptr){
                this->addToEnd(temp->nameNode);
                temp=temp->next;
            }
        }

        //переопределние операторов ввода и вывода, конструктор-копиратора
        //popen(..), socket
        void swap_L(LinkNodes<T>* first, LinkNodes<T>* second){
            LinkNodes<T>* temp= Head;
            LinkNodes<T>* sec_temp=Head;
            LinkNodes<T>* buff, *kor, *ukz;
            if(first!=Head&&second!=Head) {
                while (temp->next != first) {
                    temp = temp->next;
                }
                while (sec_temp->next != second) {
                    sec_temp = sec_temp->next;
                }
                if(first->next==second){
                    kor=temp->next;
                    buff=sec_temp->next;
                    ukz=sec_temp->next->next;
                    temp->next=buff;
                    buff->next=kor;
                    kor->next=ukz;
                }
                else {
                    if(second->next==first){
                        kor=sec_temp->next;
                        buff=temp->next;
                        ukz=temp->next->next;
                        sec_temp->next=buff;
                        buff->next=kor;
                        kor->next=ukz;
                    }else {
                        buff = temp->next->next;
                        kor = sec_temp->next->next;
                        ukz = temp->next;
                        temp->next = sec_temp->next;
                        temp->next->next = buff;
                        sec_temp->next = ukz;
                        sec_temp->next->next = kor;
                    }
                }
            }
            else{
                if(first==Head){
                    if(second!=Head) {
                        while (sec_temp->next != second) {
                            sec_temp = sec_temp->next;
                        }
                        if (first->next != second) {
                            buff = temp->next;
                            kor = sec_temp->next->next;
                            Head = sec_temp->next;
                            Head->next = buff;
                            sec_temp->next = temp;
                            sec_temp->next->next = kor;
                        } else {
                            buff = sec_temp->next;
                            kor = sec_temp->next->next;
                            ukz = Head;
                            Head = buff;
                            buff->next = ukz;
                            ukz->next = kor;
                        }
                    }
                }else {
                    if (second == Head) {
                        if(first!=Head) {
                            while (temp->next != first) {
                                temp = temp->next;
                            }
                            if (second->next != first) {
                                buff = temp->next->next;
                                kor = sec_temp->next;
                                Head = temp->next;
                                Head->next = kor;
                                temp->next = sec_temp;
                                temp->next->next = buff;
                            } else {
                                buff = temp->next;
                                kor = temp->next->next;
                                ukz = Head;
                                Head = buff;
                                buff->next = ukz;
                                ukz->next = kor;
                            }
                        }

                    }
                }

            }
        }
        LinkNodes<T>* getMin(LinkNodes<T>* first){
            LinkNodes<T>*temp=first;
            int mn=first->nameNode;
            LinkNodes<T>* mn_lst=first;
            while (temp!= nullptr){
                if(temp->nameNode<mn){
                    mn=temp->nameNode;
                    mn_lst=temp;
                }
                temp=temp->next;
            }
            return mn_lst;
        }
        void selection_sort(){
            LinkNodes<T>* temp;
            for (int i=0;i<IData<T>::datalen-1;++i){
                temp=Head;
                for (int j = 0; j < i; ++j) {
                    temp=temp->next;
                }
                LinkNodes<T>* mn = getMin( temp);
                if(temp!=mn) {
                    swap_L(mn, temp);
                }
            }
        }


};
template <typename T>
std::ostream& operator <<(std::ostream& out,LinkedList<T>& element){
    LinkNodes<T>* temp=element.Head;
    while(temp!= nullptr){
        out<<temp->nameNode<<" ";
        temp=temp->next;
    }
    return out;
}
template <class T>
class DoubleLinkNode:public LinkNodes<T>,public IData<T>{
private:
    LinkNodes<T>* Head=nullptr;
    LinkNodes<T>* Tail= nullptr;
public:
    DoubleLinkNode(){
        Head = new LinkNodes<T>;
        Tail = new LinkNodes<T>;
        Head->prev=nullptr;
        Head->next=Tail;
        Tail->prev=Head;
        Tail->next=nullptr;
        LinkNodes<T>::len++;
    }
    DoubleLinkNode(T el){
        Head=new LinkNodes<T>;
        Tail=new LinkNodes<T>;
        Head->prev= nullptr;
        Head->next=Tail;
        Tail->prev=Head;
        Tail->next= nullptr;
        Head->nameNode=el;
        LinkNodes<T>::len++;
    }
    bool addToEnd(T name) override{
        Tail->next=new LinkNodes<T>;
        LinkNodes<T>* temp = Tail->next;
        Tail->nameNode=name;
        temp->prev=Tail;
        temp->next=nullptr;
        Tail=temp;
        LinkNodes<T>::len++;
        return true;
    }
    bool insert(T el, int position) override {
        if(position>LinkNodes<T>::len){
            std::cout<<" The list is not replenished"<<std::endl;
            return false;
        }
        if(position>0) {
            LinkNodes<T>* temp = Head;
            LinkNodes<T>* middle;
            for (int i = 0; i < position-1; ++i) {
                temp= temp->next;
            }
            middle=temp->next;
            temp->next=new LinkNodes<T>;
            temp=temp->next;
            temp->next=middle;
            temp->prev=middle->prev;
            temp->nameNode=el;
            if(position==LinkNodes<T>::len){
                Tail=temp;
            }
            LinkNodes<T>::len++;
            return true;
        }
        else {
            if (position == 0) {
                LinkNodes<T> *temp = new LinkNodes<T>;
                temp->nameNode = el;
                Head->prev = temp;
                temp->next = Head;
                Head = temp;
                temp->prev = nullptr;
                LinkNodes<T>::len++;
                return true;
            }
        }
    }
    void output(){
        LinkNodes<T>* temp=Head;
        std::cout<<"Double Link list elements:";
        for (int i = 0; i <LinkNodes<T>::len; ++i) {
            std::cout<<temp->nameNode<<" ";
            temp=temp->next;
        }
    }
    void writeToFileFromHead(){
        LinkNodes<T>* temp=Head;
        std::ofstream flog("DLst_res_Head.txt", std::ios::out);
        for (int i = 0; i < LinkNodes<T>::len; ++i) {
            flog<<i+1<<"\t"<<temp->nameNode<<"\n";
            temp=temp->next;
        }
        flog.close();
    }
    void writeToFileFromTail(){
        LinkNodes<T>* temp=Tail;
        std::ofstream flog("DLst_res_Tail.txt", std::ios::out);
        for(int i=LinkNodes<T>::len-1;i>-1;i--){
            flog<<i<<"\t"<<temp->nameNode<<"\n";
            temp=temp->prev;
        }
        flog.close();
    }

};

template <typename T>
struct Node{
    Node(){
        listChilds.Head= nullptr;
        name=countNodes;
        ishere=false;
    }
    Node* parent;
    LinkedList<Node*> listChilds;
    bool ishere;
    T name;
    static int countNodes;
};
template <typename T>
int Node<T>::countNodes=0;
template <class T>
class Graph: public IData<T>{
private:
    Node<T> *head;
    Node<T>* DFS_1(Node<T>* first,std::ofstream& flog){
        if(first->listChilds.Head!= nullptr){
            flog<<first->name<<"{";
            LinkNodes<Node<T>*>* temp = first->listChilds.Head;
            while (temp!= nullptr){
                if(temp->nameNode->ishere==false){
                    DFS_1(temp->nameNode,flog);
                }
                temp=temp->next;
            }
            flog<<"}";
        }else{
            flog<<first->name;
            first->ishere=true;
            return first->parent;
        }
    }
    Node<T>* BFS_tree_1(Node<T>* first, int number,Fifo<Node<T>*> &stack){
        if(number==0){
            return first;
        }
        for (int i = 0; i < number; ++i) {
            Node<T>::countNodes++;
            Node<T>* boxx = new Node<T>;
            boxx->parent=first;
            first->listChilds.addToEnd(boxx);
            stack.addToEnd(boxx);
            if(i==number-1){
                LinkNodes<Node<T>*>* temp = first->listChilds.Head;
                while(temp!= nullptr){
                    BFS_tree_1(temp->nameNode,number-1,stack);
                    temp=temp->next;
                }
            }
        }
    }
    Node<T>* BFS_tree(Node<T>* first,int number) {
        Fifo<Node<T>*> stack;
        for (int i = 0; i < number; ++i) {
            Node<T>::countNodes++;
            Node<T>* boxx = new Node<T>;
            boxx->parent=head;
            head->listChilds.addToEnd(boxx);
            stack.addToEnd(boxx);
        }
        for (int i = 0; i < number; ++i) {
            Node<T>* korob;
            stack.getFromEnd(korob);
            BFS_tree_1(korob,number-1,stack);
        }
    }
    Node<T>* DFS_tree(Node<T>* first, int number){
        if(first== nullptr){
            return first->parent;
        }
        Node<T>* temp=first;
        int counter = number;
        for (int i = 0; i < counter; ++i) {
            Node<T>::countNodes++;
            Node<T>* boxx = new Node<T>;
            boxx->parent=temp;
            first->listChilds.addToEnd(boxx);
            DFS_tree(boxx,counter-1);
        }
    }

public:
    void DFS(){
        std::ofstream flog;
        flog.open("Test_graph.txt",std::ios::out);
        DFS_1(head,flog);
        flog.close();
    }
    Graph(int number){
        head=new Node<T>;
        head->parent= nullptr;
        BFS_tree(head,number);
    }
};

#endif //WORK_ON_LESSON_FILO_FIFO_RING_H
