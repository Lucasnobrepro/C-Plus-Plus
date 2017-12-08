#include <iostream>
#include <vector>
using namespace std;

template <class T>
T read(){
    T t;
    cin>> t;
    return t;
};

class Transaction{
public:
    string name;
    float value;
    Transaction(string name = "", float value = 0) {
        this->name= name;
        this->value = value;
    }
};

    class Sistem{
    public:
        vector<Transaction> transactions;
        float swing;

        Sistem(float swing = 0) {
            this->swing = swing;
        }


        //1.iniciar.
        void start(float value){
            this->swing = value;
        }

        //2.Incluir trasação.
        bool addTran(string name, float value){
            float resultado = value + swing;

            if(resultado < 0)
                return false;

            transactions.push_back(Transaction(name,value));
            swing += value;
            return true;
        }

        //3.Exclui uma trasação.
        bool rmTran(int id){
            for(int i = 0; i < (int) this->transactions.size(); i++){
                if(i == id){
                    transactions.erase(transactions.begin() + i);
                    return true;
                }
            }
            return false;

        }

        //4.Mostrar todas as trasações.
        void showTran(){
            for(auto a : transactions){
                cout<<"---------------------------\n"
                    <<"Nome: "<< a.name << endl
                    <<"Valor: "<< a.value << endl
                    <<"\n";

            }
                cout <<"---------------------------\n";
        }


        //5.Mostrar cliente.
        void showCli(string name){
            float valor = 0;
            cout<<"Lista de trasacoes de "<< name<<":"<<endl;
            for(int i = 0; i < (int) this->transactions.size(); i++){
                if(transactions[i].name == name){
                    cout<<"Id: "<< i<<" Nome: "<<transactions[i].name<< "Valor: "<<transactions[i].value<<endl;
                    valor += transactions[i].value;

                }
            }
            cout<<"\n"
                <<"Saldo: "<<valor<<endl;
         }

        //6.Mostra o balanço.
        float getBalanco(){
            return swing;
        }

        //7.Contar cliente.
        int contaCli(){
            int i = 0;
            string name = transactions[i].name;
            for(auto cliente : transactions){
                if(cliente.name != name){
                    i++;
                    name = cliente.name;
                }
            }
            return i;
        }


};



int main()
{
    string op = "ok";
    Sistem sistema;

    coutcout<<"-------------------\n"<<endl;
            <<"SISTEMA DE AGIOTAGEM."<<endl
            <<"-------------------\n"<<endl
            <<"\n";

    while(op != "sair"){
        cin >>op;
        if(op == "help"){
            cout<<"-------------------\n"<<endl
                <<"1.showcli"<<endl
                <<"2.balanco"<<endl
                <<"3.showtran"<<endl
                <<"4.contar"<<endl
                <<"5.rm"<<endl
                <<"6.addtra"<<endl
                <<"7.iniciar"<<endl
                <<"8.sair"<<endl
                <<"-------------------\n"<<endl;
        }
        if(op == "iniciar")
            sistema.start(read<float>());
            cout<<"-------------------\n"<<endl;

        if(op == "addtra"){
            cout<<"-------------------\n"<<endl;
            string a = read<string>();
            float b = read<float>();
            cout<< (sistema.addTran(a,b) ? "ok" : "erro")<<endl;
            cout<<"-------------------\n"<<endl;
        }

        if(op == "showcli")
            sistema.showCli(read<string>());
            cout<<"-------------------\n"<<endl;

        if(op == "balanco"){

            cout<<"Balanco: "<< sistema.getBalanco()<<endl;
            cout<<"-------------------\n"<<endl;
        }

        if(op == "contar"){

            cout<<"Qtd clientes: "<<sistema.contaCli()<<endl;
            cout<<"-------------------\n"<<endl;
        }

        if(op == "showtran")
            sistema.showTran();

        if(op == "rm"){

            cout<< (sistema.rmTran(read<int>()) ? "Ok" : "Erro")<<endl;
            cout<<"-------------------\n"<<endl;
        }


    }
    return 0;
}
