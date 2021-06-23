/*
Aluno: João Victor Freitas de Mesquita
Matricula: 412796

Como rodar o programa:

NO TERMINAL:
 - abra a pasta onde o arquivo foi colocado
 - rode o comando:
    g++ sudoku.cpp -o (nome_do_executavel)
 - depois rode os seguintes comandos abaixo

1º Gere (n) Sudokus completos utilizando os argumentos:
    (nome_do_arquivo_executavel) --criar (nº_de_sudokus)
        EX: ./sudoku --criar 10

2º Remova (n) células de um determinado sudoku criado usando os argumentos:
    (nome_do_arquivo_executavel) --remover (nº_de_celulas) (sudoku"numero_do_sudoku_gerado")
        EX: ./sudoku --remover 30 sudoku3

3º Resolve um sudoku qualquer que tenha tudo as celulas removidas
    (nome_do_arquivo_executavel) --resolver (sudoku"nº do sudoku")
        EX: ./sudoku --resolver sudoku1
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

using namespace std;

class Sudoku {
private:
    int* _sudoku;
    int l, c;
public:
    Sudoku(int l, int c);
    ~Sudoku();

    int& operator() (int i, int j){
        int p = (this->c * i) + j;
        return _sudoku[p];
    }
    bool checarL(int l, int n, int mat[9*9]);
    bool checarC(int c, int n, int mat[9*9]);
    bool checarQ(int l, int c, int n, int mat[9*9]);
    void popularMatriz(); 
    bool checarLinhas(); 
    bool checarColunas();
    bool checarQuadrado();
    void printsudoku();
    void removerCelulas(int n);  
    void resolverSudoku(); 
    int* getSudoku();
    void setSudoku(int m[9*9]);
    int getSudokuNumber(int n);
};
Sudoku::Sudoku(int l, int c){
    this->l=l;
    this->c=c;
    _sudoku = new int[l*c]; 
}
Sudoku::~Sudoku(){
    delete [] _sudoku;
}
int* Sudoku::getSudoku(){
    int* temp = new int[9*9];
    for(int i = 0; i < 81; i++){
        temp[i] = this->_sudoku[i];
    }
    return temp;
}
int Sudoku::getSudokuNumber(int n){ return this->_sudoku[n];}
void Sudoku::setSudoku(int m[9*9]){
    for(int i = 0; i < 81; i++){
        this->_sudoku[i] = m[i];
    }
}

int pegarProximo(int possiveis[]){
    bool temApenasZeros = true;
    for(int i = 0; i < 9; i++){
        if(possiveis[i]) temApenasZeros = false;
    }
    if(temApenasZeros){ return 0; } 
    int valor = 0;
    while(true){
        int i = rand() % 9;
        valor = possiveis[i];
        if(valor){
            possiveis[i] = 0;
            break;
        }
    }
    return valor;
}

void Sudoku::printsudoku(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            cout << _sudoku[(9 * i) + j] << " ";
        cout << endl;
    }
    return;
}

void zerar(int mat[9*9]){
    for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                mat[(9 * i) + j] = 0;
    return;
}

void Sudoku::popularMatriz(){
    bool precisaRepetir = false;
    do{
        precisaRepetir = false;
        zerar(_sudoku);
        for(int i = 0; i < this->l; i++){
            for(int j = 0; j < this->c; j++){
                int possiveis[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                int n = pegarProximo(possiveis);
                bool sucesso = false;
                while(true){ 
                    if(n == 0){ break; }
                    else if(
                        checarL(i, n, _sudoku) &&
                        checarC(j, n, _sudoku) &&
                        checarQ(i, j, n, _sudoku)){ 
                        _sudoku[(9 * i) + j] = n;
                        sucesso = true;
                        break;
                    }else{ n = pegarProximo(possiveis); }
                } 
                if(!sucesso){ precisaRepetir = true; } 
                if(precisaRepetir){ break; }   
            }
            if(precisaRepetir){ break; }
        }
    }while(precisaRepetir);         
}
bool Sudoku::checarL(int l, int n, int mat[9*9]){
    for(int j = 0; j < this->c; j++)
        if(mat[(this->l * l) + j] == n)
            return false;
    return true;
}
bool Sudoku::checarC(int c, int n, int mat[9*9]){
    for(int j = 0; j < this->l; j++)
        if(mat[(this->c * j) + c] == n)
            return false;
    return true;
}
int checarQuadrante(int l, int c){
    int quadrante = 0;
    if(l>0 && l<=2){
        if(c <= 2) quadrante = 1;
        else if(c <=5) quadrante = 2;
        else quadrante = 3;
    }
    else if(l <= 5){
        if(c <= 2) quadrante = 4;
        else if(c <= 5) quadrante = 5;
        else quadrante = 6;
    }else if(l <= 8){
        if(c <= 2) quadrante = 7;
        else if(c <= 5) quadrante = 8;
        else quadrante = 9;
    }
    return quadrante;
}
bool Sudoku::checarQ(int l, int c, int n, int mat[9*9]){
    int quadrante = checarQuadrante(l,c);
    switch(quadrante){
        case 1:
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 2:
            for(int i = 0; i < 3; i++)
                for(int j = 3; j < 6; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 3:
            for(int i = 0; i < 3; i++)
                for(int j = 6; j < 9; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 4:
             for(int i = 3; i < 6; i++)
                for(int j = 0; j < 3; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 5:
             for(int i = 3; i < 6; i++)
                for(int j = 3; j < 6; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 6:
            for(int i = 3; i < 6; i++)
                for(int j = 6; j < 9; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 7:
            for(int i = 6; i < 9; i++)
                for(int j = 0; j < 3; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 8:
            for(int i = 6; i < 9; i++)
                for(int j = 3; j < 6; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
        case 9: 
            for(int i = 6; i < 9; i++)
                for(int j = 6; j < 9; j++)
                    if(mat[(this->c * i) + j] == n)
                        return false;
            break;
    }
    return true;
}
void Sudoku::removerCelulas(int n){
    for(int i = 0; i < n; i++){
        while(true){
            int celula = rand() % 81;
            if(this->_sudoku[celula] != 0){
                cout << "removi a posicao:" << celula << endl;
                this->_sudoku[celula] = 0; //apagou um numero
                break;
            }
        }
    }
}
void Sudoku::resolverSudoku(){
    /**
    * 1. Preencher os espaços que tem 0 com numeros que satisfaçam
    * as regras do sudoku
    * 2. Testar combinações diferentes e, caso encontre mais de uma
    *    lançar uma escessão dizendo que ha mais de uma forma de
    *    resolve-lo 
    */
    time_t comecoDeEspera = time(NULL);
    time_t tempoDeEspera = 10; // fim do loop
    time_t fimDeEspera = comecoDeEspera + tempoDeEspera;

    int contadorPossiveis = 0;
    bool precisaRepetir = false;
    int* temp_res_sudoku = new int[81];
    int* first_res_sudoku = new int[81];
    // guardando valor de _sudoku
    for(int i = 0; i < 81; i++){
        temp_res_sudoku[i] = this->_sudoku[i];
    }
    do{
        precisaRepetir = false;
        // resetando _sudoku
        for(int i = 0; i < 81; i++){
            this->_sudoku[i] = temp_res_sudoku[i];
        }
        // buscando sulução
        for(int i = 0; i < this->l; i++){
            for(int j = 0; j < this->c; j++){
                // testa se a posição [i,j] == 0
                if(this->_sudoku[(this->c * i) + j] == 0){
                    int possiveis[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    int n = pegarProximo(possiveis);
                    bool sucesso = false;
                    while(true){ 
                        if(n == 0){
                            break; 
                        }
                        else if(
                            checarL(i, n, this->_sudoku) &&
                            checarC(j, n, this->_sudoku) &&
                            checarQ(i, j, n, this->_sudoku)){ 
                            _sudoku[(9 * i) + j] = n;
                            sucesso = true;
                            break;
                        }else{
                            printf("loop time is : %s", ctime(&comecoDeEspera));
                            n = pegarProximo(possiveis);
                        }
                    } 
                    if(!sucesso){ precisaRepetir = true; } 
                    if(precisaRepetir){ break; }   
                }
            }
            if(precisaRepetir){ break; }
        }
        if(!precisaRepetir) contadorPossiveis++;
        if(contadorPossiveis == 1){
            // copiando valores de this->sudoku para first_res_sudoku
            for(int i = 0; i < 81; i++){
                first_res_sudoku[i] = this->_sudoku[i];
            }
        }
        comecoDeEspera = time(NULL);
    }while(comecoDeEspera < fimDeEspera);
    if(contadorPossiveis != 1){
        cout << "tempo de espera excedido... nao foi possivel encontrar uma solucao diferente da original" << endl;
        return;
    }
    // rodar uma segunda vez para buscar uma outra solucao
    do{
        precisaRepetir = false;
        // resetando _sudoku
        for(int i = 0; i < 81; i++){
            this->_sudoku[i] = temp_res_sudoku[i];
        }
        // buscando sulução
        for(int i = 0; i < this->l; i++){
            for(int j = 0; j < this->c; j++){
                // testa se a posição [i,j] == 0
                if(this->_sudoku[(this->c * i) + j] == 0){
                    int possiveis[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    int n = pegarProximo(possiveis);
                    bool sucesso = false;
                    while(true){ 
                        if(n == 0){ break; }
                        else if(
                            checarL(i, n, this->_sudoku) &&
                            checarC(j, n, this->_sudoku) &&
                            checarQ(i, j, n, this->_sudoku)){ 
                            _sudoku[(9 * i) + j] = n;
                            sucesso = true;
                            break;
                        }else{ n = pegarProximo(possiveis); }
                    } 
                    if(!sucesso){ precisaRepetir = true; } 
                    if(precisaRepetir){ break; }   
                }
            }
            if(precisaRepetir){ break; }
        }
    }while(precisaRepetir);

    // comparar as duas matrizes
    for(int i = 0; i < 81; i++){
        if(first_res_sudoku[i] != this->_sudoku[i]){
            cout << "ESTE SUDOKU TEM MAIS DE UMA SOLUCAO" << endl;
        }
    }
    return;
}
void gerarNames_files(int n, string *c, int* cont){
    string file_name = "SDK\\sudoku_";
    string file_number;
    for(int i = 0; i < n; i++){
        stringstream ss;
        int temp = cont[0]+1; // cont[0] = --criar
        ss << temp;
        ss >> file_number;
        string str_final = file_name + file_number;
        c[i] = str_final;
        cont[0] = temp; // atualiza cont
    }
}

char* convertStringToChar(int i, string *c){
    string str = c[i];
    char* name = new char[str.length()+1];
    strcpy(name, str.c_str());
    return name;
}
string convertCharToString(char* c){
    string str;
    stringstream ss;
    ss << c;
    ss >> str;
    return str;
}

void criarIteratorArq(int* n){
    fstream iterator;
    iterator.open("iterator",ios::in);
    if(!iterator){
        cout << "arquivo n existe"<< endl;
        fstream c_iterator;
        c_iterator.open("iterator", ios::out);
        string s_cont;
        for(int i = 0; i < 3; i++){
            stringstream ss;
            ss << n[i];
            ss >> s_cont;
            c_iterator << s_cont << " ";
            c_iterator.close();
        }
        cout << "escrevi no arquivo" << endl;
    }
    iterator.close();
    return;
}
void lerIterator(int* n){
    fstream c_iterator;
    c_iterator.open("iterator", ios::in);
    for(int i = 0; i < 3; i++){
        c_iterator >> n[i];
    }
    c_iterator.close();
    return;
}

void escreverIterator(int* n){
    fstream new_c_iterator;
    new_c_iterator.open("iterator", ios::out);
    string s_new_cont;
    for(int i = 0; i < 3; i++){
        stringstream ss;
        ss << n[i];
        ss >> s_new_cont;
        new_c_iterator << s_new_cont << " ";
    }
    new_c_iterator.close();   
}

int main(int argc, char * args[]){
    srand(time(NULL));

    int* cont = new int[3];
    // 0 = criados , 1 = removidos, 2 = resolvidos
    cont[0] = 0; cont[1] = 0; cont[2] = 0;
    //criar arquivo / testar
    criarIteratorArq(cont);
    //escrever o valor do arquivo em cont
    lerIterator(cont);
    //escrever o valor de cont no arquivo
    escreverIterator(cont);
    // Criando sudokus
    if(strcmp(args[1], "--criar") == 0){
        int qtd_sudokus;
        sscanf(args[2], "%d", &qtd_sudokus);
        fstream write_sudoku_file;
        string name_files[qtd_sudokus];
        gerarNames_files(qtd_sudokus, name_files, cont);
        for(int i = 0; i < qtd_sudokus; i++){
            char* nameF = {convertStringToChar(i, name_files)};
            write_sudoku_file.open(nameF, ios::out);
            cout << "Gerando " << i+1 << "(o) sudoku, aguarde..." << endl;
            Sudoku nSudoku(9,9);
            nSudoku.popularMatriz();
            nSudoku.printsudoku();
            if(!write_sudoku_file) cout << "ERRO: arquivo nao criado!" << endl;
            else{
                cout << "arquivo criado com sucesso!" << endl;
                // escrever no arquivo
                string str;
                for(int i = 0; i < 81; i++){
                    stringstream ss;
                    ss << nSudoku.getSudokuNumber(i);
                    ss >> str;
                    write_sudoku_file << str << " ";
                }
                write_sudoku_file.close();
                //return 0;
            }
        }
        escreverIterator(cont);
        return 0;
    }
    // removendo células do sudoku
    else if(strcmp(args[1], "--remover") == 0){
        string n_celulas_removidas = convertCharToString(args[2]); 
        int qtd_celulas = stoi(n_celulas_removidas);
        fstream read_sudoku_file;
        read_sudoku_file.open("SDK\\" + convertCharToString(args[3]), ios::in);
        // testa se as entradas são validas
        if(qtd_celulas < 0 || qtd_celulas > 81){
             cout << "ERRO: numero de celulas para remocao eh invalido, tente novamente." << endl;
        }else if(!read_sudoku_file){
             cout << "ERRO: arquivo nao encontrado" << endl; }
        else{
            cout << "Arquivo lido com sucesso" << endl;
            // ler arquivo
            Sudoku rem_sudoku(9,9);
            int* temp_rem_sudoku = rem_sudoku.getSudoku();
            for(int i = 0; i < 81; i++){
                // ler sudoku e atribuir
                read_sudoku_file >> temp_rem_sudoku[i];    
                if(read_sudoku_file.eof()) break;
            }
            rem_sudoku.setSudoku(temp_rem_sudoku);
            rem_sudoku.removerCelulas(qtd_celulas);
            rem_sudoku.printsudoku();
            read_sudoku_file.close();
            // 2. -> guardar num arquivo chamado rem_sudoku_n 
            // criar arquivo
            fstream write_sudoku_file;
            string namefile = convertCharToString(args[3]);
            string name_file = "SDK\\rem_" + namefile; // rem_ qualqeur coisa
            char nameF[name_file.length() + 1];
            strcpy(nameF, name_file.c_str());
            write_sudoku_file.open(nameF,ios::out);
            // escrevendo no arquivo
            string str;
            for(int i = 0; i < 81; i++){
                stringstream ss;
                ss << rem_sudoku.getSudokuNumber(i);
                ss >> str;
                write_sudoku_file << str << " ";
            }
            write_sudoku_file.close();
        }
    }
    // resolvendo sudoku
    else if(strcmp(args[1], "--resolver") == 0){
        fstream read_res_sudoku_file;
        read_res_sudoku_file.open("SDK\\rem_" + convertCharToString(args[2]), ios::in);
        if(!read_res_sudoku_file){
            cout << "ERRO: arquivo nao encontrado" << endl;
            return 0;
        }else{
            cout << "Arquivo lido com sucesso" << endl;
            // ler arquivo
            Sudoku res_sudoku(9,9);
            int* temp_res_sudoku = res_sudoku.getSudoku();
            for(int i = 0; i < 81; i++){
                read_res_sudoku_file >> temp_res_sudoku[i];
                if(read_res_sudoku_file.eof()) break;
            }
            res_sudoku.setSudoku(temp_res_sudoku);
            // resolver sudoku aqui
            res_sudoku.resolverSudoku();
            fstream read_sudoku_file;
            for(int i = 0; i < 81; i++){
                if(res_sudoku.getSudokuNumber(i) == 0){
                    int * aux = res_sudoku.getSudoku();
                    read_sudoku_file.open("SDK\\" + convertCharToString(args[2]), ios::in);
                    for(int i = 0; i < 81; i++){
                        read_sudoku_file >> aux[i];
                    }
                    res_sudoku.setSudoku(aux);
                }
            }
            read_sudoku_file.close();
            res_sudoku.printsudoku();
            read_res_sudoku_file.close();
            // Guardar num arquivo camado res_sudoku_n
            // criar arquivo
            fstream write_res_sudoku_file;
            string namefile = convertCharToString(args[2]);
            string name_file = "SDK\\sol_" + namefile;
            char nameF[name_file.length() + 1];
            strcpy(nameF, name_file.c_str());
            write_res_sudoku_file.open(nameF, ios::out);
            // escrevendo no arquivo
            string str;
            for(int i = 0; i < 81; i++){
                stringstream ss;
                ss << res_sudoku.getSudokuNumber(i);
                ss >> str;
                write_res_sudoku_file << str << " ";
            }
            write_res_sudoku_file.close();
        }
    }
    else{
        cout << "ERROR: Entrada invalida " << endl;
        cout << "Use os seguintes comandos: " << endl;
        cout << "1. Para gerar SUDOKUS completos use: (nome_executavel) --criar (qtd_sudokus)" << endl;
        cout << "2. Para remover celulas de determinado SUDOKU use: (nome_executavel) --remover (0 < n_de_casas_removidas < 81) (arquivo_com_Sudoku)" << endl;
        cout << "3. Para resolver SUDOKUS incompletos use: (nome_do_arquivo) --resolver (sudoku_especifico)" << endl;
    }
    return 0;
}