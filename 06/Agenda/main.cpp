#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

class Telefone{
    string id;
    string numero;
public:
    Telefone(string num = "", string id = ""){
        this->numero = num;
        this->id = id;
    }

    static bool validate(string numero) {
            string data = "1234567890()- ";
            for(auto c : numero)
                if(data.find(c) == string::npos)
                    return false;
            return true;
        }

    string getNumero(){
        return numero;
    }

    string getId(){
        return id;
    }
};

class Contato{
    string nome;
    vector<Telefone> numeros;
    bool isFavorite {false};

public:
    Contato(string nome = "", string id = "", string numero = ""){
        this->nome = nome;
        numeros.push_back(Telefone(numero,id));
    }

    string getNome(){
        return this->nome;
    }

    bool addFone(Telefone fone){
        for(auto cont : numeros)
           if(cont.getNumero() == fone.getNumero())
               return false;

        numeros.push_back(fone);
        return true;
    }

    vector<Telefone> allNumeros(){
        vector<Telefone> allNum;
        for(auto cont : numeros)
            allNum.push_back(cont);

        return allNum;
    }

    bool rmFone(string foneid){
        for(int i = 0; i < (int) numeros.size(); i++){
            if(numeros[i].getId() == foneid){
                numeros.erase(numeros.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool isFavorited(){
        if(this->isFavorite)
            return true;
        return false;
    }

    void setFavoritar(bool value){
        isFavorite = value;
    }

    string tostring(){
        string saida = nome + "[ ";
        for(auto nums : numeros){
            saida += nums.getNumero() + " ";
        }
            saida += "]";
            return saida;
    }
};

class Agenda{
    map<string, Contato> contatos;
    map<string, Contato> favoritos;

public:
    Agenda(){}

    bool addContato(Contato cont){
        return contatos.insert(make_pair(cont.getNome(), cont)).second;
    }

    bool rmContato(string nome){
        if(contatos.erase(nome)){
            favoritos.erase(nome);
            return true;
        }
        return false;
    }

    Contato * getContato(string nome){
        auto it = contatos.find(nome);
        return (it != contatos.end()) ? (&it->second) : nullptr;
    }

    bool favoritar(string nome){
        Contato * contato = getContato(nome);
        if(!contato || contato->isFavorited())
            return false;
        contato->setFavoritar(true);
        favoritos[nome] = *contato;
        return true;
    }

    bool desfavoritar(string nome){
        Contato * contato = getContato(nome);
        if(contato && contato->isFavorited()){
            contato->setFavoritar(false);
            contatos.erase(nome);
            return true;
        }
        return false;
    }

    vector<Contato> getFavoritos(){
        vector<Contato> resp;
        for(auto par : favoritos)
            resp.push_back(par.second);
        return resp;
    }
    vector<Contato> getContatos(){
        vector<Contato> resp;
        for(auto par : contatos)
            resp.push_back(par.second);
        return resp;
    }

    vector<Contato> patternSearch(string pattern){
        vector<Contato> resp;
        for(auto par : contatos)
            if(par.second.tostring().find(pattern) != string::npos)
                resp.push_back(par.second);
        return resp;
    }
};

class Controller {
    Agenda agenda;
public:

    void commandLine(){
        string op = "";
        cout<<"Digite um comando ou digite help!"<<endl;
        while(op != "sair"){
            op = "";
            cin >> op;

            if(op == "help"){
                cout <<"\n"
                     <<"addcon &nome &id &numero"<<endl
                     <<"addFone &id &numero"<<endl
                     <<"favoritar &string"<<endl
                     <<"desfavoritar &string"<<endl
                     <<"rmcontato &string"<<endl
                     <<"rmnumero"<<endl
                     <<"getcon &nome"<<endl
                     <<"allfavor"<<endl
                     <<"pesquisa &string"<<endl
                     <<"------------------------"<<endl
                     <<"\n";
            }

            if(op == "addfone"){
                string nome, numero, foneId;
                cin >> nome >> foneId >> numero;
                auto contato = agenda.getContato(nome);

                if(!contato){
                    cout << "Contato nao existe";
                    continue;
                }
                cout << (contato->addFone(Telefone(numero,foneId)) ? "Sucesso Brother" : "Id duplicado") << endl;
            }
            if(op == "addcon"){
                cout<<"Digite nome id numero: ";
                string nomec = read<string>();
                string idc = read<string>();
                string num = read<string>();

               cout << (agenda.addContato(Contato(nomec,idc, num)) ? "Contato inserido\n" : "Contato não inserido\n");
               cout<<"___________________________\n";
            }
            if(op == "getcon"){
                cout <<"Digite um nome: "<<endl;

                auto contato = agenda.getContato(read<string>());

                cout<<"Nome:" << contato->getNome()<<endl;
                cout <<"_______________________________"<<endl;

                for(auto cont : contato->allNumeros()){
                    cout << "Id: "<< cont.getId()<<endl
                         << "Numero: "<< cont.getNumero()<<endl;
                }
                cout<<"___________________________\n";
            }
            if(op == "allfavor"){
                for(auto far : agenda.getFavoritos()){
                    cout<< far.getNome()<<endl;
                }
                cout<<"___________________________\n";
            }
            if(op == "favoritar"){
                cout << (agenda.favoritar(read<string>()) ? "Contato favoritado!\n" : "Erro!\n");
                cout<<"___________________________\n";
            }
            if(op == "desfavoritar"){
                cout<< (agenda.desfavoritar(read<string>()) ? "Contato desfavoritado!\n" : "Erro!\n");
                cout<<"___________________________\n";
            }
            if(op == "rmcontato"){
                cout<< (agenda.rmContato(read<string>()) ? "Contato removido com sucesso!\n" : "Erro!\n")<<endl;
                cout<<"___________________________\n";
            }
            if(op == "rmfone"){
                auto it = agenda.getContato(read<string>());
                if(it->rmFone(read<string>()))
                    cout<<"Telefone removido\n";
                cout<<"________________________"<<endl;

            }
            if(op == "pesquisa"){
                for(auto part : agenda.patternSearch(read<string>()))
                    cout<< part.getNome()<<endl;
            }
            if(op == "allcon"){
                for(auto cont : agenda.getContatos()){
                    cout<< cont.tostring()<<endl;
                }
            }
        }
     }
};

int main()
{
    Controller controller;
    controller.commandLine();
    cout <<"qui\n";
    return 0;
}
