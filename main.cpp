#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

ifstream f("heap.in");
ofstream g("heap.out");

struct node {   //struct pentru nod
    int val, grad;
    node* copilstanga, * fratedreapta, * parinte;
};

node* newNode(int n) {    //nod nou cu valorile initializate
    node* newNode = new node;
    newNode->grad = 0;
    newNode->val = n;
    newNode->copilstanga = newNode->fratedreapta=  newNode->parinte = NULL;
    return newNode;
}

class heap_binomial{
list < node* > H; //facem lista pentru heap-ul cu care vom lucra

list < node* > :: iterator get_radacina(){ //nodul cu cea mai mica valoare va fi radacina

        list < node* > :: iterator it, it_min;
        node* vmin = newNode( 999999 );

        for( it = H.begin(); it != H.end(); ++it )
            if( (*it) -> val < vmin -> val ){
                vmin = *it;
                it_min = it;
            }

        return it_min;
    }

    void delete_root( node* tree, heap_binomial& heap ){

        if( tree -> grad == 0 ){
            delete tree;
            return;
        }

        node* temp = tree;

        heap.H.push_front( tree -> copilstanga );

        tree = tree -> copilstanga;
        while( tree -> fratedreapta ){
            heap.H.push_front( tree -> fratedreapta );
            tree = tree -> fratedreapta;
        }
        delete temp;
    }

    void merge_tree( node* tree1, node* tree2 ){

        if( tree1 -> val > tree2 -> val ) //lipim 2 arbori asezandu-l pe cel cu nodul mai mic primul
            swap ( *tree1, *tree2 );

        tree2 -> fratedreapta = tree1 -> copilstanga;
        tree2 -> parinte = tree1;
        tree1 -> copilstanga = tree2;
        tree1 -> grad++;

    }
    void modifica(){
    if( H.size() <= 1 ) return;

        list < node* > :: iterator prev;
        list < node* > :: iterator curr;
        list < node* > :: iterator next;

        prev = H.begin();
        curr= prev++;
        next = curr++;

        while( curr != H.end() ){

            merge_tree( *curr, *prev );
            prev++;
            if( curr != H.end() ) curr++;
            if( next != H.end() ) next++;
        }
    };


public:
    int top(){
        return (*get_radacina()) -> val; //returneaza valoarea primului element din lista
    }
    void push( int val ){//adauga element apoi modifica lista
        node *tree = newNode( val );
        H.push_front( tree );
        modifica();
    }
    void pop(){ //sterge primul element

        list < node* > :: iterator root = get_radacina();

        heap_binomial heap_nou;
        delete_root( (*root), heap_nou );

        H.erase( root );

        heap_union( heap_nou );

    }
    void heap_union( heap_binomial& heap2){
        list < node* > :: iterator h1 = H.begin();
        list < node* > :: iterator h2 = heap2.H.begin();

        list < node* > heap_nou;

        while( h1 != H.end() && h2 != heap2.H.end() ){ //cat timp cele 2 heap-uri au elemente, adaugam in heap-ul nou in functie de valoare
            if( (*h1) -> grad <= (*h2) -> grad ){
                heap_nou.push_back( *h1 );
                h1++;
            }
            else{
                heap_nou.push_back( *h2 );
                h2++;
            }
        }

        while( h1 != H.end() ){ //verificam daca mai sunt elemente in heap-ul 1
            heap_nou.push_back( *h1 );
            h1++;
        }

        while( h2 != heap2.H.end() ){ //verificam daca mai sunt elemente in heap-ul 2
            heap_nou.push_back( *h2 );
            h2++;
        }
        H = heap_nou;
        modifica();
    }
};

int main()
{
    int N, Q;
    heap_binomial Heap[100];
    f >> N >> Q;

    int actiune, h, x, h1, h2;
    for( int i = 1; i <= Q; ++i ){
        f >> actiune;

        if( actiune == 1 ){

            f >> h >> x;
            Heap[h].push( x );

        }
        if( actiune == 2 ){

            f >> h;
            g << Heap[h].top() << '\n';
            Heap[h].pop();
        }
        if( actiune == 3 ){

            f >> h1 >> h2;

            Heap[h1].heap_union( Heap[h2] );

        }
    }
    return 0;
}
