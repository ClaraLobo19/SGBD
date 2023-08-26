#ifndef IESTRUTURA_H
#define IESTRUTURA_H

#include <vector>

class DID;

class IEstrutura {
public:
    virtual bool inserirNoh(const std::vector<char>& palavra) = 0;
    virtual DID seek(const std::vector<char>& palavra) = 0;
    virtual std::vector<DID> Scan() = 0;
    virtual bool Delete(const std::vector<char>& palavra) = 0;
};

#endif  // IESTRUTURA_H


// A interface é uma estrutura de declaração de métodos virtuais puros, que são implementados nas classes que a herdam. A implementação das classes que implementam a interface deve ser feita em seus respectivos arquivos de origem (source files).


