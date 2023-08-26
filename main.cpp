#include <cstring>
#include <iostream>
#include <vector>
#include "Estrutura.cpp"
#include "IEstrutura.h"
using namespace std;
//------------------------------MAIN-------------------------------------------
int main() {

 Estrutura* estrutura = new Estrutura();
  
  int opc;
  while (true) {

    cout << "\n1 - INSERT"
         << "\n";
    cout << "2 - SCAN"
         << "\n";
    cout << "3 - SEEK"
         << "\n";
    cout << "4 - DELETAR"
         << "\n";
    cout << "5 - TERMINAR"
         << "\n\n";

    cout << "Digite a opcao desejada: ";
    cin >> opc;
    
    cout<<"\n";
    if (opc == 1) { // Inserir palavra fornecida pelo usuário
      cout << "Digite uma palavra (com até 5 caracteres): ";
      string palavra;
      cin >> palavra;

      vector<char> palavraVec(palavra.begin(), palavra.end());
      bool a = estrutura->inserirNoh(palavraVec);
      if (a == false) { cout << "Inserção feita" << "\n"; }
    } // if


    else if (opc == 2) { // Chamar a função Scan(Exibir os doc)
      vector<DID> DIDs = estrutura->Scan();
      if(DIDs.empty()){cout<<"Não existe"<<"\n"<<"\n";}
      // cout << "DIDs encontrados:\n";
      for (const auto &DID : DIDs) {
        cout << "ID: " << DID.idPag << ",      Seq: " << DID.seq
             << ",      Tamanho: " << DID.tamDoc << endl;
      } // for
    }   // else if


    else if (opc == 3) { // SEEK(nao feito)
      cout << "Digite uma palavra (com até 5 caracteres): ";
      string palavra;
      cin >> palavra;

      vector<char> palavraVec(palavra.begin(), palavra.end());
      DID doc = estrutura->seek(palavraVec);
      
      if (doc.idPag != -1) {
        cout << "ID: " << doc.idPag << ", Seq: " << doc.seq
             << ", Tamanho: " << doc.tamDoc << endl;
      } else {
        cout << "DID não existe! "<<"\n";
      }
    }


    else if (opc == 4) {
      cout << "Digite uma palavra (com até 5 caracteres): ";
      string palavra;
      cin >> palavra;

      // Chamar a função Delete
      vector<char> palavraVec(palavra.begin(), palavra.end());
      estrutura->Delete(palavraVec);

    }


    else if (opc == 5) { break; }


    else{
      cout<<"Opcao nao valida!"<<"\n"; 
      break;
    }
  } // while

  cout << "Programa encerrado";
  return 0;
} // main

