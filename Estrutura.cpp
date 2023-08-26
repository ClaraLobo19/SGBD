#include <cstring>
#include <iostream>
#include <vector>
#include "IEstrutura.h"
#include "classes.cpp"

using namespace std;



class Estrutura : public IEstrutura  {

  vector<Pagina> paginas;
public:
  Estrutura() { paginas.resize(20); }

  //-----------------------------INSERT---------------------------------------
  bool inserirNoh(const vector<char> &palavra) override {
  int indPag = -1;
  int seq = -1;

  // PROCURAR EM QUE PAGINA SERÁ INSERIDA E A SUA SEQ
  for (int i = 0; i < paginas.size(); i++) {
    Pagina &pagina = paginas[i];
    if (pagina.PagOcpd + palavra.size() <= pagina.tamPag) {
      indPag = i;
      seq = pagina.PagOcpd + 1;
      break;
    }
  }

  if (seq != -1 && indPag != -1) {
    Pagina &pagina = paginas[indPag];
    
    //CONSTROI O DOCUMENTO
    DID DID;
    DID.idPag = indPag;
    DID.seq = seq;
    DID.tamDoc = palavra.size();

    //INSERIR ELE NA PAGINA( ULTIMA POSIÇÃO DA LISTA)
    pagina.inserirDID(DID, palavra);

    //ATUALIZAR O DADOS DA PAGINA(QUANTO JÁ FOI OCUPADO)
    pagina.PagOcpd += DID.tamDoc;
  }

  else {//se todas as páginas estiverem lotadas
    cout << "ERRO! Não há espaço disponível para a palavra." << endl;
    return true;
  }

  return false;
}

  //---------------------SEEK---------------------------------------
  DID seek(const vector<char> &palavra)  override{
    for (int i = 0; i < paginas.size(); i++) { // percorrer cada página
      Pagina &pagina = paginas[i];
      nohDoc *temp = pagina.listaDocs;

      while (temp != nullptr) { // percorrer cada noh
        bool flag = true;
        for (int i = 0; i < palavra.size();
             i++) { // ver letra por letra da palavra
          if (temp->palavra[i] != palavra[i]) {
            flag = false;
            break; // BREAK DO FOR
          }
        }
        if (flag) {
          return temp->did;
        }
        temp = temp->prox; //VAI PARA PROXIMO DOCUMENTO

        
      }
    }
    DID did;
    did.idPag = -1;
    did.seq = -1;
    did.tamDoc = -1;
    return did;
  }

  //------------------------SCAN-----------------------------------------
  vector<DID> Scan() override {
    vector<DID> DIDs;

    for (int i = 0; i < paginas.size(); i++) {
      Pagina &pagina = paginas[i];
      nohDoc *temp = pagina.listaDocs;

      while (temp != nullptr) {
        DIDs.push_back(temp->did);
        temp = temp->prox;
      }
    }

    return DIDs;
  }


  // //---------------------------DELETE---------------------------------------
  // não terminado

  bool Delete(const vector<char> &palavra) override{
    for (int i = 0; i < paginas.size(); i++) {
      Pagina &pagina = paginas[i];
      nohDoc *temp = pagina.listaDocs;
      nohDoc *prev = nullptr;

      while (temp != nullptr) {
        if (memcmp(temp->palavra, palavra.data(), palavra.size()) == 0) {
          // Encontrou o DID com a palavra correspondente
          if (prev == nullptr) {
            // É o primeiro DID da página
            pagina.listaDocs = temp->prox;
          } else {
            // Não é o primeiro DID, ajustar o encadeamento
            prev->prox = temp->prox;
          }

          // Atualizar o espaço ocupado da página
          pagina.PagOcpd -= temp->did.tamDoc;

          // Atualizar cada seq
          nohDoc *aux = temp->prox; // primeiro a ser modificado
          while (aux != nullptr) {
            aux->did.seq -= temp->did.tamDoc;
            aux = aux->prox;
          }
          delete aux;

          // Liberar a memória do nó removido
          delete temp;
          return true;
        }

        prev = temp;
        temp = temp->prox;
      }
    }

    // A palavra não foi encontrada nos DIDs
    cout << "O Documento não existe."
         << "\n";
    return false;
  }
};