#include <cstring>
#include <iostream>
#include <vector>
#include "IEstrutura.h"
// #include "IEstrutura.h"  
using namespace std;
// Classe abstrata representando a interface

class DID {
public:
  int idPag;
  int seq; // inicio do DID
  int tamDoc;
};

// cada noh terá a palavra e DID
struct nohDoc {
  DID did;
  char palavra[5];
  nohDoc *prox;
};
// Struct que representa uma página de disco

class Pagina {
public:
  int tamPag = 5;
  int PagOcpd = 0;
  nohDoc *listaDocs = nullptr;

  void inserirDID(const DID &DID, const vector<char> &palavra) {//manipular na pagina onde eu vou colocar o DID
    nohDoc *novoNoh = new nohDoc;
    novoNoh->did = DID;
    memcpy(novoNoh->palavra, palavra.data(), palavra.size());
    novoNoh->prox = nullptr;

    if (listaDocs == nullptr) {
      listaDocs = novoNoh;
    } else {
      nohDoc *temp = listaDocs;
      while (temp->prox != nullptr) {
        temp = temp->prox;
      }
      temp->prox = novoNoh;
    }
  }
};

