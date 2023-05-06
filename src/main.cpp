#include <iostream>
#include <map>
#include <set>

using namespace std;

map < pair <string, char>, set<string> > preenche(map < pair <string, char>, set<string> >funcaoT) {
    set<string>estados;
    /// 0 no q1 volta pro q1
    estados.insert("q1");
    funcaoT.insert({ {"q1",'0'},estados });

    ///1 no q1 volta no q1 e vai para q2, como ativa q3 com a vazia, automaticamente ativa o q3
    estados.insert("q2");
    estados.insert("q3");
    funcaoT.insert({ {"q1",'1'},estados });

    ///0 no q2 ativa q3
    estados.clear();
    estados.insert("q3");
    funcaoT.insert({ {"q2",'0'},estados });

    //1 no q3 ativa q4
    estados.clear();
    estados.insert("q4");
    funcaoT.insert({ {"q3",'1'},estados });

    ///0 e 1 no q4 ativa q4
    funcaoT.insert({ {"q4",'0'},estados });
    funcaoT.insert({ {"q4",'1'},estados });

    return funcaoT;

}



int main() {

    string estado_inicial = "q1", cadeia;
    map < pair <string, char>, set<string> > funcaoT;
    map < pair <string, char>, set<string> > ::iterator it;
    set<string>estados_ativos;
    set<string>::iterator itse;
    set<string>estados_retornados;
    set<string>estados_antigos;
    set<string>::iterator itse2;
    set<string>::iterator itaux;


    //Preenchendo a função de transição
    funcaoT = preenche(funcaoT);

    bool conf;
    cout << "O alfabeto é o padrão binário[(0,1)]." << endl << endl;

    estados_antigos.insert(estado_inicial);

    do {
        cout << "Qual cadeia deseja testar?" << endl;
        getline(cin, cadeia);

        conf = true;

        ////aplicando a função de transição na cadeia
        for (int i = 0;i < cadeia.size();i++) {
            if (cadeia[i] != '1' && cadeia[i] != '0') {
                conf = false;
            } else {
                for (itse = estados_antigos.begin();itse != estados_antigos.end();++itse) {
                    it = funcaoT.find({ *itse,cadeia[i] });

                    if (it != funcaoT.end()) {
                        estados_retornados = it->second;
                        for (itse2 = estados_retornados.begin();itse2 != estados_retornados.end();++itse2) {
                            estados_ativos.insert(*itse2);
                        }
                    }
                }
                estados_antigos = estados_ativos;
                if (i < cadeia.size() - 1)
                    estados_ativos.clear();

            }
        }


        if (!conf) {
            estados_ativos.clear();
            cout << "Há um elemento na cadeia digitada que não pertence ao alfabeto!" << endl << endl;
        }
    } while (!conf);

    cout << "Estados finais ativos: " << endl;
    for (itse = estados_ativos.begin();itse != estados_ativos.end();++itse) {
        cout << *itse << " ";
    }
    cout << endl;

    ///checando se um dos estados ativos é o final é o final (q4)
    itse = estados_ativos.find("q4");

    if (itse != estados_ativos.end())
        cout << endl << "ACEITA" << endl;
    else
        cout << endl << "REJEITA" << endl;


    return 0;
}