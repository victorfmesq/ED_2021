/**
 * --------------TRABALHO 2--------------
 * Aluno: João Victor Freitas de Mesquita
 * Matrícula: 412796
 * 
 * NOTAS: Arquivos serão gerados ao final da execução do programa conforme pedido nas instruções
 * 
 *      parte_01: referente aos resultados da primeia parte do trabalho
 *          M = tamanho da bolha
 *          P = quantidade de SWAPS
 *      parte_02: referente aos resultados da segunda parte do trabalho.
 *          Size = tamanho do vetor
 *          P = quantidade de SWAPS (parse)
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <direct.h>
using namespace std;

typedef unsigned int uint; 

unsigned long int GLOBAL_P = 0;  // contador de inserções

inline string separator(){
#ifdef _WIN32
    return "SDK\\";
#else
    return "SDK/";
#endif
}

//função que preenche o vetor com valores aleatórios
void preencherVetor(uint* v, uint size){
    for(uint i = 0; i < size; i++)
        v[i] = i + 10;
    for(uint i = 0; i < size; i++)
        std::swap(v[i], v[std::rand() % size]);
}
//função que printa todos os elementos do vetor
void print(uint* v, unsigned long int size){
    for(uint i = 0; i < size; i++){
        cout << v[i] << " ";
    }
}
//função que copia os valores do vetor W para o vetor V
void cpy(uint* w, uint* v, uint size){
    for(uint i = 0; i < size; i++){
        v[i] = w[i];
    }
}
void myswap(uint& x, uint& y){
    std::swap(x, y);
    GLOBAL_P++;
}
void insertion(uint* v, uint m){
    uint aux;
    for (uint i = 1; i < m; i++){
        aux = v[i];
        int j = i - 1;
 
        while ((j >= 0) && (v[j] > aux)){
            myswap(v[j + 1], v[j]);
            j--;
        }
        v[j + 1] = aux;
    }
}

void ordenar(uint* v, uint size, uint m){
    // chamar bubblesort
    for(uint i = 0; i < size-(m-1); i++){   // seria apenas size - 1 se a bolha tivesse tamanho fixo em 2, mas como o valor varia entao dizemos que i < size-(m-1)
        for(uint j = 0; j < size-(m-1)-i; j++){

            uint* aux = v+j;
            insertion(aux, m);//inicio e fim 
        }
    }
    return;
}

void quicksort(uint v[], int comeco, uint fim)
{
	int pivo;
	int i = comeco;
	int j = fim - 1;
	pivo = v[(comeco + fim) / 2];
	while(i <= j)
	{
		while(v[i] < pivo && i < fim)
		{
			i++;
		}
		while(v[j] > pivo && j > comeco)
		{
			j--;
		}
		if(i <= j)
		{
            myswap(v[i],v[j]);
			i++;
			j--;
		}
	}
	if(j > comeco) quicksort(v, comeco, j+1);
	if(i < fim)	quicksort(v, i, fim);
}

int main(){
    //srand(time(NULL));
    srand(0);

    _mkdir("SDK");

    // PARTE 1 bouble + insertion
    uint size = 10000;         // size é o tamanho do vetor
    uint w[size];   // W é um vetor de back up
    preencherVetor(w,size);
    uint v[size];   // V é o vetor que será ordenado
    cpy(w,v,size);
    fstream part1_file;
    part1_file.open(separator() + "parte_01", ios::out);  // arquivo que vai guardar os valores de M e GLOBAL_P
    if(!part1_file){
        cout << "ERRO: arquivo não criado" << endl;
        return 0;
    }
    uint m = 2;                  // M é o tamanho da bolha
    cout << "Aguarde... o processo pode demorar. Vetor de tamanho: " << size << endl;
    while(m != size){
        cout << "Tamanho da bolha: " << m << "\t Tamanho do vetor: "<< size << endl;
        GLOBAL_P = 0;   // zeramos GLOBAL_P para reutilizarmos para proxima iteração com M
        cpy(w,v,size);
        ordenar(v, size, m);
        // escrever no arquivo
        string sm, sp;          // sm guarda a string de M  e sp guarda a string de GLOBAL_P      
        stringstream ss1, ss2;
        ss1 << m;
        ss1 >> sm;
        ss2 << GLOBAL_P;
        ss2 >> sp;
        part1_file << "M: "<< sm << "\t" << "P: " << sp << endl; 
        m++;
    }
    //print(v, size);
    
    // PARTE 2 quicksort
    fstream part2_file;
    part2_file.open(separator() + "parte_02", ios::out); // arquivo que vai guardar os valores de M e Global_P
    if(!part2_file){
        cout << "ERRO: arquivo não encontrado" << endl;
        return 0;
    }

    uint size2 = 10;
    while(size2 <= 100000){
        uint v2[size2];
        GLOBAL_P = 0;
        preencherVetor(v2,size2);
        quicksort(v2,0,size2);
        // escrever no arquivo
        string sn, sp;          // sn guarda a string de SIZE e sp guarda a string de GLOBAL_P (Parse)
        stringstream ss1, ss2;
        ss1 << size2;
        ss1 >> sn;
        ss2 << GLOBAL_P;
        ss2 >> sp;
        part2_file << "Size: " << sn << "\t" << "P: " << sp << endl;
        size2 += 5;
        cout << "vet size: " << size2 << endl;
    }
    //print(v2,size2);


    return 0;
}