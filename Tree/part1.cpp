/**
 * Aluno: João Victor Freitas de Mesquita
 * Matricula: 412796
 * 
 * COMO EXECUTAR O PROGRAMA?
 * Para rodar a parte 1 basta ter o arquivo portugues.txt no mesmo diretorio do programa e executa-lo.
 */
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void fnc(vector<string> u, int i, int j, ostream& out){
    if(i > j)
        return;
    int m = (i+j)/2;
    out << u[m] << endl; 
    fnc(u, i, m-1, out);
    fnc(u, m+1, j, out);
}

int main(){
// PARTE 1
    fstream txt, final_txt;
    txt.open("portugues.txt", ios::in);
    final_txt.open("portugues~.txt", ios::out|ios::trunc);
    if(txt.is_open()){
        vector<string> v;
        string p;
        while(getline(txt, p)){
            v.push_back(p);
        }
        fnc(v, 0, v.size()-1, final_txt);
    }
    txt.close();
    final_txt.close();
}