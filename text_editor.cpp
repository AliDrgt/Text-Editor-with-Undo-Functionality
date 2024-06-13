#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;



//CODED BY ALI FATIH DURGUT
//20190702068 





void DisplayList(struct Node *node);
void openFile(string filename);
void append(struct Node** head, string info);
Node* getNode(string data);
void replace_n(struct Node **head,string newInfo,int pos);
void replaceWU(struct Node **head,string newInfo,int pos);
void delete_n(struct Node **head ,int pos);
void delete_nWU(struct Node **head ,int pos);
void insert_n(struct Node **head ,string info,int pos);
void insert_nWU(struct Node **head ,string info,int pos);
int pageNumber = 1;
int satirNo = 1;
struct Node* head = NULL;

struct Node { 
    string data; 
    Node* next;
};

struct undo_stack {
    stack<string> func_stack;
    stack<string> st_stack;
    stack<string> st_stack2;
    stack<int> pos_stack;
    stack<int> pos2_stack2;
};

struct undo_stack undo_stack;

Node* pushNode(Node** head, string info){  
    Node* new_node = new Node();  
    new_node->data = info;  
    new_node->next = (*head);  
    (*head) = new_node;
    return *head;  
}

void undo(struct Node** iter){
    if(undo_stack.func_stack.empty()){
        cout << "\nYou can't undo.Since there is no action to undo" << endl;
        return;
    }


    else if(undo_stack.func_stack.top() == "insert"){
        delete_nWU(iter,undo_stack.pos_stack.top());
        undo_stack.func_stack.pop();
        undo_stack.pos_stack.pop();
        return;
    }

    else if(undo_stack.func_stack.top() == "delete"){
        insert_nWU(iter,undo_stack.st_stack.top(),undo_stack.pos_stack.top());
        undo_stack.func_stack.pop();
        undo_stack.pos_stack.pop();
        return;
    }


    else if(undo_stack.func_stack.top() == "replace"){
        replaceWU(iter,undo_stack.st_stack.top(),undo_stack.pos_stack.top());
        undo_stack.func_stack.pop();
        undo_stack.pos_stack.pop(); 
        undo_stack.st_stack.pop();
        return;
    }

    else if(undo_stack.func_stack.top() == "move"){
        delete_nWU(iter,undo_stack.pos2_stack2.top());
        insert_nWU(iter,undo_stack.st_stack.top(),undo_stack.pos_stack.top());
        undo_stack.func_stack.pop();
        undo_stack.st_stack.pop();
        undo_stack.pos_stack.pop();
        undo_stack.pos2_stack2.pop();
    }
}


void append(struct Node** head, string info){
    struct Node* newNode = new Node;
    struct Node *last = *head; 
    newNode->data = info;
    newNode->next = NULL;
    if (*head == NULL){
        *head = newNode;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }
    last->next = newNode;       
    return;
}


Node* getnewNode(string data){ 
    Node* newNode = new Node(); 
    newNode->data = data; 
    newNode->next = NULL; 
    return newNode; 
}


void delete_n(struct Node **head ,int pos){
    struct Node *current = *head;
    struct Node *prev = *head;
    int a = pos;

    if(*head == NULL){
        cout << "position empty";
    }
    else if(pos==1){
        *head = current->next;
        undo_stack.func_stack.push("delete");
        undo_stack.pos_stack.push(1);
        free(current);
        current = NULL;
    }
    else{
        while(pos != 1){
            prev = current;
            current = current->next;
            pos--;
        }

        prev ->next  = current->next;
        undo_stack.func_stack.push("delete");
        undo_stack.st_stack.push(current->data);
        undo_stack.pos_stack.push(a);
        free(current);
        current = NULL;
    }
}


void delete_nWU(struct Node **head ,int pos){   //DELETE FUNCTION WITHOUT UNDO ELEMENTS.
    struct Node *current = *head;
    struct Node *prev = *head;
    int a = pos;

    if(*head == NULL){
        cout << "position empty";
    }
    else if(pos==1){
        *head = current->next;
        free(current);
        current = NULL;
    }
    else{
        while(pos != 1){
            prev = current;
            current = current->next;
            pos--;
        }

        prev ->next  = current->next;
        free(current);
        current = NULL;
    }
}


void replaceWU(struct Node **head,string newInfo,int pos){
    struct Node* iter = *head;
    while(pos--){
        if(pos == 0){
            Node* temp = getnewNode(newInfo);          //DELETE FUNCTION WITHOUT UNDO ELEMENTS.
            iter->data = temp->data;
        }
        else{
            iter = iter->next;  
        }
    }
}


void replace_n(struct Node **head,string newInfo,int pos){
    struct Node* iter = *head;
    int a = pos;
    while(pos--){
        if(pos == 0){
            Node* temp = getnewNode(newInfo);
            undo_stack.func_stack.push("replace");
            undo_stack.pos_stack.push(a);
            undo_stack.st_stack.push(iter->data);
            iter->data = temp->data;
        }
        else{
            iter = iter->next;  
        }
    }
}


void insert_n(struct Node **head ,string info,int pos){
    undo_stack.pos_stack.push(pos);
    undo_stack.func_stack.push("insert");

    while(pos--){
        if (pos == 0){ 
            Node* temp = getnewNode(info); 
            temp->next = *head; 
            *head = temp; 
        } 
        else
            head = &(*head)->next; 
        } 
}


void insert_nWU(struct Node **head ,string info,int pos){
    while(pos--){
        if (pos == 0){ 
            Node* temp = getnewNode(info); 
            temp->next = *head; 
            *head = temp;                    //DELETE FUNCTION WITHOUT UNDO ELEMENTS.
        } 
        else
            head = &(*head)->next; 
        } 
}


void Move(struct Node **head,int n,int m){
    undo_stack.func_stack.push("move");
    undo_stack.pos2_stack2.push(m);
    undo_stack.pos_stack.push(n);
    struct Node* temp = new Node();
    struct Node* iter = new Node();
    iter = *head;
    int a = n;

    if(a == 1){
        delete_nWU(head,a);
        insert_nWU(head,iter->data,m);
        undo_stack.st_stack.push(iter->data);
        return;
    }
    else{
        while(n--){
            if(n == 0){
                temp->data = iter->data;
                undo_stack.st_stack.push(iter->data);
                delete_nWU(head,a);
            }
            else{
                iter = iter->next;
            }
        }
    insert_nWU(head,temp->data,m);
    }
}


void DisplayList(struct Node* iter){
    struct Node* iter2 = iter;
    cout << "\n----PAGE " << pageNumber << "----" << endl;
    int a = (pageNumber*10)-9;
    for(int j = 0;j<(pageNumber-1)*10;j++){
        iter2 = iter2->next;
    }

    for(int i = a;i<=(pageNumber*10);i++){
        cout << a << ") " << iter2->data << endl;
        if(iter2->next == NULL){
            for(int i = 0;i<12-(a%10);i++){
                a++;
                cout << a << ") " << endl;
            }
            break;
        }
        iter2 = iter2->next;
        a++;
    }
    cout << "----PAGE " << pageNumber << "----" << endl;
    cout << "\n\n" ;
}


void next(){
    pageNumber++;
}


void prev(){
    pageNumber--;
}


void openFile(string filename,struct Node** Llist){
    ifstream file;
    string line;
    file.open(filename);

    while(getline(file,line)){
        append(Llist,line);
    }

    file.close();
}


void saveFile(string filename,struct Node* Llist){
    ofstream file;
    string line;


    file.open(filename);
    while(Llist->next != NULL){
        file << Llist->data << endl;
        Llist = Llist->next;
    }

    file.close();
}



int main(){
    int i,size,pos;
    string line,filename,select;
    cout << "Enter filename: ";
    cin >> filename;


    openFile(filename,&head);
    struct Node* iter = head;

    
    while(1){
        DisplayList(iter);
        cout << "0) exit" << endl;
        cout << "1) insert" << endl;
        cout << "2) delete" << endl;
        cout << "3) next" << endl;
        cout << "4) prev" << endl;
        cout << "5) replace" << endl;
        cout << "6) move" << endl;
        cout << "7) save" << endl;
        cout << "8) undo" << endl;
        cout << "Enter Selection by text :";
        cin >> select;
    
    
        if(select=="insert"){
            cout << "enter position and line" << endl;
            cin >> pos,cin.ignore(),getline(cin,line);
            insert_n(&iter,line,pos);
        }

        else if(select=="delete"){
            cout << "enter n" << endl;
            cin  >> pos;
            delete_n(&iter,pos);
        }

        else if(select=="next"){
            next();
        }

        else if(select=="exit"){
            cout << "\nGoodbye.";
            break;
        }


        else if(select=="prev"){
            prev();
        }

        else if(select=="replace"){
            cout << "enter position and line" << endl;
            cin >> pos,cin.ignore(),getline(cin,line);
            replace_n(&iter,line,pos);
        }

        else if(select=="move"){
            cout << "enter n and m" << endl;
            cin >> pos >> i;
            Move(&iter,pos,i);
        }

        else if(select=="save"){
            saveFile("note.txt",head);
        }

        else if(select=="undo"){
            undo(&iter);
        }

        else{
            cout << "Invalid input!" << endl;
        }

    }
}
