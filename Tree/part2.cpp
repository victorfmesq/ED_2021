
/**
 * Aluno: João Victor Freitas de Mesquita
 * Matricula: 412796
 * 
 * COMO EXECUTAR O PROGRAMA?
 * 
 * Condições: ter o arquivo portugues~.txt no mesmo diretório do programa. Portugues~.txt é gerado automaticamente
 * após a finalização da execução da Parte 1.
 * 
 * 
 * >> .\<Nome_do_exec> <Nome_arq_entrada>.txt <Nome_arq_saida>.txt
 * 
 * << <Nome_arq_saida>.txt = (todos os nomes que não estão contido em portugues~.txt)
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename N>
class Node {
public:
    Node *left;
    Node *right;
    N value;

    Node(N value)
    {
        this->value = value;
        this->left = 0;
        this->right = 0;
    }
};

template <typename T>
class BTree {
private:
    Node<T> *root;

    Node<T> *__add(Node<T> *node, T value){ 
        if (node == 0) 
            return new Node<T>(value); // cria um novo nó com value
        
        if (node->value >= value) 
            node->left = __add(node->left, value);

        else 
            node->right = __add(node->right, value);
        
        return node;
    }

    void __print__(Node<T> *base, int i = 0){
        if (base){
            i += 8;
            __print__(base->right, i);

            cout << endl;
            for (int x = 4; x < i; x++)
                cout << " ";
            cout << base->value << endl;

            __print__(base->left, i);
        }
    }

    Node<T> *__search(Node<T> *node, T value){
        if (node != 0){
            if (node->value == value){ return node; }
            else if (node->value < value)
                return __search(node->right, value);
            else
                return __search(node->left, value);
        }
        return 0;
    }
public:
    BTree() {
        this->root = 0;
    }

    void add(T value) {
        this->root = __add(this->root, value);
    }

    void print(){
        cout << endl << endl;
        __print__(this->root);
        cout << endl << endl;
    }

    Node<T> *search(T value){
        return __search(this->root, value);
    }

};

int main(int argc, char **argv){

    // PARTE 2
    BTree<string> *tree = new BTree<string>();

    fstream pt_txt; 
    pt_txt.open("portugues~.txt", ios::in);
    if (pt_txt.is_open())
    {
        // adicinando palavras à árvore
        string palavra;
        while(getline(pt_txt, palavra)){
            tree->add(palavra);
            cout << palavra << endl;
       }
    }
    pt_txt.close();

    fstream entrada; 
    entrada.open(argv[1], ios::in);
    if (entrada.is_open())
    {
        // compara palavras que não existem na arvore
        string line;
        fstream saida; 
        saida.open(argv[2], ios::out|ios::trunc);
        while(getline(entrada, line)){
            if (tree->search(line) == 0){ // caso palavra não exista
                // adiciona palavras incorreta (inexistente)
                saida << line << endl;
            }
        }
        saida.close();
    }
    entrada.close();
}