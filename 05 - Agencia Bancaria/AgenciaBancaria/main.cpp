#include <iostream>
#include <vector>
using namespace std;


template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

//Classe de operação.
struct Operacao{
    string descricao;
    float valor;

    Operacao(string descricao = "", float valor = 0){
        this->descricao = descricao;
        this->valor = valor;
    }
};

//Classe conta que contem varias operações.
class Conta{
private:
    int id;
    float saldo{0};
    vector<Operacao> extrato;
    bool status = true;

public:
    Conta(int id = 0){
        this->id = id;
        extrato.push_back(Operacao("deposito", 1000));
        saldo = 1000;
    }


    bool transferir(Conta &other,float valor){

        if(valor > saldo)
            return false;

        other.saldo += valor;
        extrato.push_back(Operacao("Tranferencia", valor));

    }

//Serta status para false;
    bool setFalse(){
        status = false;
        return true;
    }

//Retorna o startus.
    bool getStatus(){
        return status;
    }

//Retorna Saldo.
    float getSaldo(){
        return this->saldo;
    }

//Retorna ID.
    int getId(){
        return this->id;
    }

//Serta ID.
    void setId(int id){
        this->id = id;
    }

//Faz um saque.
    bool saque(float valor){
        if((this->saldo < valor) || (valor < 0))
            return false;

        this->saldo -= valor;
        this->extrato.push_back(Operacao("Saque: ", valor));

        return true;
    }

//Faz um saque.
    bool deposito(float valor){
        if(valor < 1)
            return false;

        this->saldo += valor;
        this->extrato.push_back(Operacao("Deposito: ", valor));
        return true;
    }

//Retorna extrato.
    vector<Operacao> getExtrato(){
        return this->extrato;
    }

};

class Cliente{
    int qtdCont{1};
    string cpf;
    string nome;
    string pass;
    vector<Conta> contas;
public:
    Cliente(string cpf = 0, string nome = "", string pass = ""){
        this->cpf = cpf;
        this->nome = nome;
        this->pass = pass;
        contas.push_back(Conta(1));
    }


    vector<Conta> getContas(){
        return contas;
    }

    bool matchSenha(string senha){
        return this->pass == senha;
    }

    string getNome(){
        return nome;
    }

//Adiciona uma conta.
    bool addConta(){
        if(qtdCont >= 3)
            return false;

        contas.push_back(Conta(qtdCont));
        qtdCont += 1;
        return true;
    }

//Retorna o CPF.
    string getCpf(){
        return cpf;
    }

//Encerra conta.
    bool encerraConta(int numero){
        for(auto conCpf : contas){
            if(conCpf.getId() == numero){
                if(conCpf.getSaldo() == 0 && conCpf.getStatus() != false){
                   conCpf.setFalse();
                   return true;
                }
                return false;
            }
        }
        return false;
    }
};

class Agencia{
    vector<Cliente> clientes;
    int log{0};

public:
    static constexpr const char * adminUsers = "admin";
    static constexpr const char * adminPassword = "admin";

    Agencia(){
        clientes.push_back(Cliente(0,Agencia::adminUsers, Agencia::adminPassword));
    }

    void show(string nome){
        for(auto elem : clientes)
            if(elem.getNome() == nome){
                cout<<"Cliente: "<<nome<<endl;
                for(auto cona : elem.getContas()){
                    cout<<"Conta: "<< cona.getId() <<" Value: "<< cona.getSaldo() <<endl;
                }
            }
    }

    Cliente *login(string nome, string senha){
        for(auto &elem : clientes){
            if(elem.getNome() == nome)
                if(elem.matchSenha(senha))
                    return &elem;

            return nullptr;
        }
    }

//Adiciona cliente.
    bool addCli(string cpf){
        for(auto confCPF : clientes){
            if(confCPF.getCpf() == cpf)
                return false;            
        }
        string nome, pass;
        cout<<"\tDigite: $nome $senha: ";
        cin>> nome >> pass;
        clientes.push_back(Cliente(cpf, nome, pass));
        return true;
    }

//Adiciona Conta.
    bool addConta(string cpf){
        for(auto conCPF : clientes){
            if(conCPF.getCpf() == cpf){
                conCPF.addConta();
                return true;
            }
        }
        return false;
    }

    void showCli(){
        for(auto client : clientes){
            cout<<"CPF: "<< client.getCpf();
                for(auto cont : client.getContas()){
                    cout<<" Conta"<< cont.getId() <<": "<<endl;
           }
        }
    }

    bool login(string cpf){
        for(auto elemento : clientes){
            if(cpf == elemento.getCpf()){
                log = 1;
                return true;
            }
        }
        return false;
    }

    void logout(){
        log = 0;
    }


};

int main(){

    return 0;

}
