/*
            <Trabalho 3>

    Aluno: João Victor Freitas de Mesquita
    Matricula: 412796
*/
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

class Expression {
    private:
        map<string, int> exp; // estrutura que guardará as variáveis com seus valores
    public:
        // key = nome / value = valor da variáveil
        void put(string key, int value);     // set
        int getValueFrom(string key);        // get
        bool findVariable(string v);
};

void Expression::put(string key, int value){
    exp.insert(pair<string, int>(key, value));
}
int Expression::getValueFrom(string key){ 
    map<string,int>::iterator it;
    it = exp.find(key);
    if(it != exp.end())
        exp.erase (it);
    return exp.find(key)->second;
}
bool Expression::findVariable(string v){
    map<string,int>::iterator it;
    it = exp.find(v);
    if(it != exp.find(v)){
        return false;
    }
    return true;
}

string findNameIn_(string temp){
    string nome;
    for(int i = 0; i < temp.length(); i++){
        if((temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122)){ // usando valores ASCII para encontrar letras
            string aux;
            stringstream ss;
            ss << temp[i];
            ss >> aux;
            nome.append(aux); 
        }                                                            
    }
    return nome;
}
string findValueIn_(string temp){
    string valor;
    for(int i = 0; i < temp.length(); i++){
        if(temp[i] >= 48 && temp[i] <= 57){                                   // usando valores ASCII para encontrar numeros
            string aux;
            stringstream ss;
            ss << temp[i];
            ss >> aux;
            valor.append(aux);
        }
    }
    return valor;
}

void adicionarVariavel(Expression exp, string nome, string valor){
    int value = 0;
    stringstream ss;
    ss << valor;
    ss >> value;
    exp.put(nome, value);
}
bool ehValida(string temp){
    int cont = 0;
    for(int i = 0; i < temp.length(); i++){
        if(temp[i] == ' '){
            cont++;
        }
    }
    if(cont > 2){
        cout << "ERRO: Input invalido, deve conter apenas (:) + nome_variavel + valor(inteiro)" << endl;
        return false;
    }
    return true;
}

int compararPrioridade(char op1, char op2){
    int p_op1 = 0;
    int p_op2 = 0;
    if(op1 == '*' || op1 == '/')      { p_op1 = 2; }
    else if(op1 == '+' || op1 == '-') { p_op1 = 1; }
    else if(op1 == '(')               { p_op1 = 0; }
    else                              { p_op1 = 4; }

    if(op2 == '*' || op2 == '/')      { p_op2 = 2; }
    else if(op2 == '+' || op2 == '-') { p_op2 = 1; }
    else if(op2 == '(')               { p_op2 = 0; }
    else                              { p_op2 = 4; }

    if(p_op1 = 0)           { return 4; }
    else if(p_op1 = 4)      { return 3; }
    else if(p_op1 > p_op2)  { return 0; }
    else if(p_op1 < p_op2)  { return 1; }
    else if(p_op1 == p_op2) { return 2; }
}

bool temPrioridade(char op1, char op2){
    bool temPrioridade;
    int v_prioridade = compararPrioridade(op1, op2);
    switch (v_prioridade)
    {
    case 0:
        // op1 prioridade sobre op2
        temPrioridade = true;
        break;
    case 1:
        // op2 prioridade sobre op1
        temPrioridade = false;
        break;
    case 2:
        // op1 e op2 tem mesma prioridade
        temPrioridade = true;
        break;
    case 3: 
        // op1 é ')'
        temPrioridade = true;
        break;
    case 4:
        // op1 é '(' pode entrar sempre
        temPrioridade = true;
    default:
        break;
    }
    return temPrioridade;
}

string checarExpressao(string temp, stack<char> op_stack){
    string resposta;

    // * verificar se as variáveis foram criadas
            
    // checar expressão
    for(int i = 1; i < temp.length(); i++){
        if( (temp[i] >= 40 && temp[i] <= 43) || (temp[i] == '-') || (temp[i] == '/') ){ // operadores (,),*,+,-,/
            // verifciar se segue a regra de prioridades
            if(op_stack.empty()){
                cout << "a" <<endl;
                op_stack.push(temp[i]); // adicionando operador na pilha de operadores
            }    
            else{
                if(temPrioridade(temp[i], op_stack.top())){
                    // add op na pilha
                    cout << "b" <<endl;
                    op_stack.push(temp[i]);
                }
                else{
                    // add op na string
                    cout << "c" <<endl;
                    string aux;
                    stringstream ss;
                    ss << temp[i];
                    ss >> aux;
                    resposta.append(aux);
                }
                // tem prioridade
                if(temp[i] == ')'){
                    cout << "d" <<endl;
                    for(int i = 0; i < op_stack.size(); i++){
                        op_stack.pop();
                        if( (op_stack.top() == '*') || (op_stack.top() == '/') || (op_stack.top() == '+') || (op_stack.top() == '-')){
                            string aux;
                            stringstream ss;
                            ss << op_stack.top();
                            ss >> aux;
                            resposta.append(aux);
                        }
                    }
                }
            }
        }
        // variáveis
        else if((temp[i] >= 65 && temp[i] <= 90) || (temp[i] >= 97 && temp[i] <= 122)){ 
            cout << "e" << endl;
            string aux;
            stringstream ss;
            ss << temp[i];
            ss >> aux;
            resposta.append(aux); // adicionando variáveis à string de resposta
        }
        else if(temp[i] == ' '){ continue; }
        else{
            cout << "ERRO: expressao invalida, por favor verifique e tente novamente" << endl;
        }
    // se chegou no ultimo elemento
    if(temp[i] == temp[temp.length() - 1]){ 
            for(int i = 0; i < op_stack.size(); i++){
                if( (op_stack.top() == '*') || (op_stack.top() == '/') || (op_stack.top() == '+') || (op_stack.top() == '-')){
                    string aux;
                    stringstream ss;
                    ss << op_stack.top();
                    ss >> aux;
                    resposta.append(aux);
                }
                op_stack.pop();
            }
        }
    }
    return resposta;
}

int main(){
    /**
     *  # PROMPT #
     * 
     *  >> expressão: 
     *      (A + B) * C
     *  >> Valor de uma variável
     *      A = 5
     *      B = 4
     *      C = 2
     * --------------------------
     *  # É preciso atribuir variáveis e valores para utilizar uma expressão, caso contrario
     *    retornará uma excessão.
     * -------------------------
     *  << Pilha com resultado da expressão
     * 
    */
    cout << endl <<"Bem-vindo ao prompt do programa!" << endl 
    << "Para ATRIBUIR VARIAVEIS utilize o prefixo (:) seguido pelo nome da varievel e o seu valor" << endl
    << "EX: >> : A 5" << endl
    << "Para EXPRESSOES utilize o prefixo (!) seguido pela expressao" << endl
    << "EX: >> ! (A+B)*C" << endl;

    Expression exp;                         // guardar as variaveis criadas e seus valores 
    while(true){
        string temp;
        getline(cin, temp);
        char op = temp[0]; // operador

        if(op == ':'){
            // criar variáveis
            string nome, valor;
            nome = findNameIn_(temp);
            valor = findValueIn_(temp);
            if(ehValida(temp)){
                if(nome.empty())       cout << "ERRO: nao foi identificado o nome a variavel" << endl;
                else if(valor.empty()) cout << "ERRO: nao foi identificado o valor da variavel" << endl;
                else{ adicionarVariavel(exp, nome, valor); }
                cout << "Nome: "<< nome << endl;                                   
                cout << "Valor: "<< valor << endl;
            }
        }
        else if(op == '!'){
            // resovler expressões
            stack<char> op_stack;
            string resposta = checarExpressao(temp, op_stack);
            cout << resposta << endl;

            // checar se variáveis existem (BUG)
            for(int i = 0; i < resposta.length(); i++){
                if((resposta[i] >= 65 && resposta[i] <= 90) || (resposta[i] >= 97 && resposta[i] <= 122)){
                    string aux;
                    stringstream ss;
                    ss << resposta[i];
                    ss >> aux;
                    bool exist = exp.findVariable(aux);
                    if(!exist){
                        cout << "ERRO: Expressão inválida. Variável não encontrada..." << endl;
                    }
                }
            }
        }
        else{
            cout << "ERRO: Prefixo nao identificado por favor, verifique e tente novamente" << endl;
        }
    }
    return 0;
}
    /**
     * >> receber expressão (pré-fixo + nome + valor)
     * verificarExpressão();
     * if(expressão válida){
     *      if(pre-fixo == ":"){ -> adicionar variável
     *          testar se variável ja existe
     *          if(se existe){
     *              return exception (Variável 'nome' ja foi criada com valor 'value', deseja substituir?)
     *              >> sim / não
     *              if(sim){
     *                  variaveis->nome = atribuição -> nome (add)
     *                  cariaveis->valor = atribuição -> valor (add)
     *              }
     *          }
     *          else{
     *              variaveis->nome = atribuição -> nome (add)
     *              cariaveis->valor = atribuição -> valor (add)
     *          }  
     *      }
     *      else if(pre-fixo == "!"){ -> resolver expressão
     *          Testar se as variáveis existem e se têm valor
     *          if(!existe alguma){
     *              return excessão (variável não identificada)
     *          }
     *          expressão(string) = expressão(entrada)
     *          resolverExpressão();
     *          mostrarResultado();
     *      }
     *      else{
     *          Retornar excessão (préfixo desconhecido verifique e tente novamente)
     *      }
     *  }
    */