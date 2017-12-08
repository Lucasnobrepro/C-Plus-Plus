#include <iostream>
#include <vector>
using namespace std;

template <class T>
T read() {
    T t;
    cin >>t;
    return t;
};

class Espiral{
public:
    string nome;
    float preco;
    int qtd;


    Espiral(string nome = "", int qtd = 0, float preco = 0){
        this->qtd = qtd;
        this->nome = nome;
        this->preco = preco;
    }

    bool alterarEspiral(string nome, int qtd, float preco){
        if(nome == "" || qtd < 0 || preco < 0)
            return false;

        this->nome = nome;
        this->qtd = qtd;
        this->preco = preco;
        return true;
    }

};

//Maquina junkFood.
class Maquina{
private:
    vector<Espiral> spin;
    float saldo {0};
    float troco {0};
    float lucro {0};

public:
    Maquina(int qtd = 0){
        for(int i = 0; i < qtd; i++)
            spin.push_back(Espiral());
    }

    void altera(int indice){

                string alt0 = read<string>();
                float alt1 = read<float>();
                float alt2 = read<float>();

                spin[indice].alterarEspiral(alt0,alt1,alt2);
    }

//Mostra o saldo da maquina.
    float showSaldo(){
        return saldo;
    }

//Inseri dinheiro na maquina.
    bool inserirDinheiro(float din){
        if(din < 0)
            return false;

        saldo += din;
        return true;
    }

//Mostra o lucro da maquina.
    void mostrarLucro(){
        cout<<"lucro: "<< lucro<<endl;
    }

//Retorna troco.
    void perdirTroco(){
        cout<< saldo << endl;
        saldo = 0;
    }

//Procura o perdido nas espirais e devine o troco a ser devolvido.
    void Pedido(int i){
                if(spin[i].preco < saldo && spin[i].qtd > 0){
                    saldo -= spin[i].preco;
                    lucro += spin[i].preco;
                    spin[i].qtd--;
                    cout<< "Voce comprou um "<< spin[i].nome <<endl;

                }else if(spin[i].preco > saldo){

                cout<< "Dinheiro insulficiente"<< endl;

                }else if (spin[i].qtd <= 0){
                    cout<<"Produto nao existe\n";

            }
        }


    void inicia(){

            spin[0] = (Espiral("vo",3,1.5));
            spin[1] = (Espiral("choco", 5, 3));
            spin[2] = (Espiral("milho",2,5));


    }

    void showSpin(){
        for(auto esp : spin){
            cout<<"Nome: "<<esp.nome<<" Quantidade: "<<esp.qtd<<" Preco: "<<esp.preco<<endl
                <<"\n";
        }
    }

};

int main()
{

    cout<<"Junk Food\n";
    cout<< "Digite o numero de espirais na maquina\n";

    cout<<"\n";

    Maquina maquina = Maquina(read<int>());
    cout<< "maquina criada\n";

    maquina.inicia();
    maquina.showSpin();

    string op;
    int i = 0;
    while(op != "fim"){
        cin >>op;
        if(op == "inserir"){
            cout<< (maquina.inserirDinheiro(read<float>()) ? "Ok" : "erro")<< endl;
            i = 1;
        }
        if(op == "saldo"){
            cout<< maquina.showSaldo()<<endl;
        }
        if(op == "pedido" && i != 0){
            maquina.Pedido(read<int>());
        }
        if(op == "troco"){
            maquina.perdirTroco();
        }
        if(op == "admin"){

        }
        if(op == "lucro"){
            maquina.mostrarLucro();
        }
        if(op == "altera"){
            maquina.altera(read<int>());
        }
        if(op == "show"){
            cout << "Saldo do cliente: "<< maquina.showSaldo()<<endl;
                 maquina.mostrarLucro();

                 maquina.showSpin();
        }
    }























}
