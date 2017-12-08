#include <iostream>

using namespace std;

enum Tipo{FOGO, TERRA, AGUA, RELAMPAGO, NATUREZA};



struct Elemental{
    string nome;
    Tipo tipo;
    int idade;
    Tipo critico;
    int vida;
    int level;
    int forca;
    int exp;
    bool vivo;

        Elemental(string nome = "", Tipo tipo){
            this->nome = nome;
            this->tipo = tipo;
            vivo =  true;
            idade = 0;
            vida = 80;
            level = 1;
            forca = 10 * rand() % 5;
            exp = 0;
            if(this->tipo == FOGO){
                critico = NATUREZA;
            }else if(this->tipo == TERRA){
                critico = RELAMPAGO;
            }else if(this->tipo == AGUA){
                critico = FOGO;
             }else if(this->tipo == RELAMPAGO){
                critico = AGUA;
            }else if(this->tipo == NATUREZA){
                critico = TERRA;
            }
        }

        virtual void levardano(int valor){
            this->vida -= valor;
            if(vida < 0)
                vivo = false;
        }

        void attakCritico(Tipo &crit){
            if(crit == this->critico){
                this->forca *= 5;
                cout <<"Elemento Forte "<< nome <<endl;
            }
        }

        void attack(Elemental &other){
               cout << nome <<"(" <<vida<<")"
                    <<" ataca "
                    <<other.nome<<"("<<other.
                      vida<<")"
                    <<endl;

               int dano = rand () % this->forca;
               other.levardano(dano);
               if(other.vivo ){
                   int golpe = rand() % other.forca;
                   this->levardano(golpe);
                   cout<<"Golpe "<< dano <<" Contragolpe "<< golpe <<"\n"<<endl;

               }
               if(!other.vivo)
                   cout << other.nome <<" Morto"<<endl;
        }


        void show(){
            cout<<"NOME: "<< this->nome<<endl
                <<"VIDA: "<< this->vida<<endl
                <<"FORCA: "<<forca<<endl
                <<"TIPO: "<< this->tipo<<endl
                <<"LEVEL: "<< this->level<<endl
                <<"ELEMENTO FORTE: "<< this->critico<<endl
                <<"EXP: "<< this->exp <<endl<<endl;


        }

        int treinar(){
           if(exp != 3){
               this->exp += 1;
           }else{
               level += 1;
               this->exp = 0;
           }

           vida = vida +(level * 20);
           forca *= level;

           return 1;
        }
};

int main()
{
    srand(time(NULL));
    string op;

    Elemental t1 = new Elemental();
    Elemental t2 = new Elemental();

    if(op == "fogo") t1 = Elemental("fdfs", "fsdfd");
    if(op == "natureza") t2=Elemental("natureza", NATUREZA);




    while(t1.vivo && t2.vivo){
            if(rand() % 2 == 0)
                std::swap(t1, t2);
            t1.attakCritico(t2.tipo);
            t1.attack(t2);
            getchar();
        }


}
