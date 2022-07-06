#include "catch.hpp"
#include "../Dominios.h"
#include <unordered_map>
#include "testes-valores.h"

using namespace std;

template<> const pair<string, string> 
ValoresEInfo< Nome >::VALORES_VALIDOS[] = {
    make_pair("Artur Padovezi", "comum"),
    make_pair("Enzo Zanetti", "comum"),
    make_pair("A B", "com numero minimo de caracteres"),
    make_pair("Artur Zbcdefghijklmnopqrstuvw", "com 30 caracteres (o limite)"),
};

template<> const pair<string, string>
ValoresEInfo<Nome>::VALORES_INVALIDOS[] = {
    make_pair("ArtUr Padovezi", "com maiuscula a mais"),
    make_pair("Ab", "sem sobrenome e sem espaço"),
    make_pair("ArturPadovezi", "sem espaco entre nome e sobrenome"),
    make_pair("Artur  Padovezi", "com dois espacos no meio"),
    make_pair("Artur ", "sem sobrenome"),
    make_pair(" Artur Padovezi", "com um espaco a mais antes"),
    make_pair("Artur Padovezi ", "com um espaco a mais depois"),
    make_pair("artur Padovezi", "nome sem maiuscula"),
    make_pair("Artur padovezi", "sobrenome sem maiuscula"),
    make_pair("Artur pAdovezi", "sobrenome começando com minuscula"),
    make_pair("Artur Padove_zi", "contendo caracter invalido"),
    make_pair("Artur Padove-zi", "contendo caracter invalido"),
    make_pair("Artur Padove.zi", "contendo caracter invalido"),
    make_pair("Artur Padove@zi", "contendo caracter invalido"),
    make_pair("Artur Zbcdefghijklmnopqrstuvwx", "contendo 31 caracteres (max=30)"),
    make_pair("Artur Zbcdefghijklmnopqrstuvwxz", "contendo 32 caracteres (max=30)"),
    make_pair("Artur Padovezi Piratelli", "contendo nome a mais"),
    make_pair("Artur de Sa", "contendo nome a mais, nome do meio so de minusculas"),
    make_pair("Artur Padovezi piratelli", "contendo nome a mais, nome final so de minusculas"),
};



template<> const pair<string, string> 
ValoresEInfo< Nota >::VALORES_VALIDOS[] = {
    make_pair("0", "limite inferior"),
    make_pair("9", "maximo com unico digito"),
    make_pair("10", "limite superior"),
};
    

template<> const pair<string, string> 
ValoresEInfo< Nota >::VALORES_INVALIDOS[] = {
    make_pair("11", "acima do limite superior (nota <= 10)"),
    make_pair("-1", "abaixo do limite inferior (nota <= 0)")
}; 


template<> const pair<string, string> 
ValoresEInfo< Data >::VALORES_VALIDOS[] = {
    make_pair("01/Jan", "primeiro dia do ano"),
    make_pair("29/Fev", ""),
    make_pair("31/Dez", "ultimo dia do ano"),
};

template<> const pair<string, string> 
ValoresEInfo< Data >::VALORES_INVALIDOS[] = {
    make_pair("00/Jan", ""), 
    make_pair("30/Fev", ""), 
    make_pair("32/Mar", ""), 
    make_pair("300/Jan", "")
};


// const string CODIGOS_VALIDOS[] = {
//     "01/Jan", "29/Jan", "31/Mar"
// };

// const string CODIGOS_INVALIDOS[] = {
//     "00/Jan", "30/Fev", "32/Mar", "300/Jan"
// };


TEMPLATE_TEST_CASE( "dominios tem construtor, set e get funcionando", "[dominios][template]",
                    Nome , Nota, Data //, outros dominios. Acessiveis no teste por TestType
    ) {
    
 
    SECTION("Método set", "[set]"){
        TestType dominio{
            ValoresEInfo<TestType>::VALORES_VALIDOS[0].first
        };
 
        SECTION("Valores validos", "[validos]"){
 
            for(const pair<string, string> &valor_e_info : ValoresEInfo<TestType>::VALORES_VALIDOS){
                const string &valor = valor_e_info.first, &info = valor_e_info.second;
 
                SECTION(valor + '\n' + info){
                    CHECK_NOTHROW(dominio.setValor(valor));
 
                    CHECK((dominio.getValor() == valor));
                }
            }
 
        }
 
        SECTION("Valores invalidos", "[invalidos]"){
            for(const pair<string, string> &valor_e_info : ValoresEInfo<TestType>::VALORES_INVALIDOS){
                const string& valor = valor_e_info.first, info = valor_e_info.second;
 
                SECTION(valor + '\n' + info){
                    CHECK_THROWS_AS(dominio.setValor(valor), invalid_argument);
                    CHECK((dominio.getValor() != valor));
                }
            }
        }
    }
 
 
    SECTION("Construtor", "[construtor]"){
        TestType* dominioptr;
 
        SECTION("Valores validos", "[validos]"){
 
            for(const pair<string, string> &valor_e_info : ValoresEInfo<TestType>::VALORES_VALIDOS){
                const string& valor = valor_e_info.first, info = valor_e_info.second;
 
                SECTION(valor + '\n' + info){
 
                    dominioptr = 0;
 
                    CHECK_NOTHROW(dominioptr = new TestType(valor));
                    if(dominioptr != 0)
                        CHECK((dominioptr->getValor() == valor));
 
                    delete dominioptr;
                }
            }
        }
 
        SECTION("Valores invalidos", "[invalidos]"){
 
            for(const pair<string, string> &valor_e_info : ValoresEInfo<TestType>::VALORES_INVALIDOS){
                const string& valor = valor_e_info.first, info = valor_e_info.second;
 
                SECTION(valor + '\n' + info){
                    dominioptr = 0;
 
                    CHECK_THROWS_AS((dominioptr = new TestType(valor)), invalid_argument);
 
                    delete dominioptr;
                }
            }
        }
    }
}


// TEST_CASE("Testando Domínio Nome", "[Nome]"){ 
//     SECTION("Método set", "[set]"){
//         Nome nome{NOMES_VALIDOS[0].first};
        
//         SECTION("Valores validos", "[validos]"){
            
//             for(const pair<string, string> &valor_e_info : NOMES_VALIDOS){
//                 const string &valor = valor_e_info.first, &info = valor_e_info.second;

//                 UNSCOPED_INFO("O valor é " << valor << "\n" << info);

//                 CHECK_NOTHROW(nome.setValor(valor));

//                 CHECK((nome.getValor() == valor));
//             }

//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const pair<string, string> &valor_e_info : NOMES_INVALIDOS){
//                 const string& valor = valor_e_info.first, info = valor_e_info.second;

//                 UNSCOPED_INFO("O valor é " << valor << "\n" << info);

//                 CHECK_THROWS_AS(nome.setValor(valor), invalid_argument);
//                 CHECK((nome.getValor() != valor));

//             }
//         }
//     }
//     SECTION("Construtor", "[construtor]"){
//         Nome* nomeptr;

//         SECTION("Valores validos", "[validos]"){
            
//             for(const pair<string, string> &valor_e_info : NOMES_VALIDOS){
//                 const string& valor = valor_e_info.first, info = valor_e_info.second;

//                 nomeptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor << "\n" << info);

//                 CHECK_NOTHROW(nomeptr = new Nome(valor));
//                 if(nomeptr != 0)
//                     CHECK((nomeptr->getValor() == valor));
                
//                 delete nomeptr;
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){

//             for(const pair<string, string> &valor_e_info : NOMES_INVALIDOS){
//                 const string& valor = valor_e_info.first, info = valor_e_info.second;
                
//                 nomeptr = 0;

//                 UNSCOPED_INFO("O valor é " << valor << "\n" << info);
                
//                 CHECK_THROWS_AS((nomeptr = new Nome(valor)), invalid_argument);
                
//                 delete nomeptr;
//             }
//         }
//     }
// }


// TEST_CASE("Testando Domínio Nota", "[Nota]"){
//     SECTION("Método set", "[set]"){
//         Nota nota{NOTAS_VALIDAS[0]};

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : NOTAS_VALIDAS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(nota.setValor(valor));
//                 CHECK((nota.getValor() == valor));
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : NOTAS_INVALIDAS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(nota.setValor(valor), invalid_argument);
//                 CHECK((nota.getValor() != valor));
//             }
//         }
//     }
//     SECTION("Construtor", "[construtor]"){
//         Nota* notaptr;

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : NOTAS_VALIDAS){
//                 notaptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(notaptr = new Nota(valor));
//                 if(notaptr != 0)
//                     CHECK((notaptr->getValor() == valor));
                
//                 delete notaptr;
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : NOTAS_INVALIDAS){
//                 notaptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(notaptr = new Nota(valor), invalid_argument);
                
//                 delete notaptr;
//             }
//         }
//     }
// }




// TEST_CASE("Testando Domínio Idioma", "[Idioma]"){
//     SECTION("Método set", "[set]"){
//         Idioma idioma{IDIOMAS_VALIDOS[0]};

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : IDIOMAS_VALIDOS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(idioma.setValor(valor));
//                 CHECK((idioma.getValor() == valor));
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : IDIOMAS_INVALIDOS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(idioma.setValor(valor), invalid_argument);
//                 CHECK((idioma.getValor() != valor));
//             }
//         }
//     }
//     SECTION("Construtor", "[construtor]"){
//         Idioma* idiomaptr;

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : IDIOMAS_VALIDOS){
//                 idiomaptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(idiomaptr = new Idioma(valor));
//                 if(idiomaptr != 0)
//                     CHECK((idiomaptr->getValor() == valor));
                
//                 delete idiomaptr;
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : IDIOMAS_INVALIDOS){
//                 idiomaptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(idiomaptr = new Idioma(valor), invalid_argument);
                
//                 delete idiomaptr;
//             }
//         }
//     }
// }




// TEST_CASE("Testando Domínio Data", "[Data]"){
//     SECTION("Método set", "[set]"){
//         Data data{DATAS_VALIDAS[0]};

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : DATAS_VALIDAS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(data.setValor(valor));
//                 CHECK((data.getValor() == valor));
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : DATAS_INVALIDAS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(data.setValor(valor), invalid_argument);
//                 CHECK((data.getValor() != valor));
//             }
//         }
//     }
//     SECTION("Construtor", "[construtor]"){
//         Data* dataptr;

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : DATAS_VALIDAS){
//                 dataptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(dataptr = new Data(valor));
//                 if(dataptr != 0)
//                     CHECK((dataptr->getValor() == valor));
                
//                 delete dataptr;
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : DATAS_INVALIDAS){
//                 dataptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(dataptr = new Data(valor), invalid_argument);
                
//                 delete dataptr;
//             }
//         }
//     }
// }



// TEST_CASE("Testando Domínio Codigo", "[Codigo]"){
//     SECTION("Método set", "[set]"){
//         Codigo codigo{CODIGOS_VALIDOS[0]};

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : CODIGOS_VALIDOS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(codigo.setValor(valor));
//                 CHECK((codigo.getValor() == valor));
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : CODIGOS_INVALIDOS){
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(codigo.setValor(valor), invalid_argument);
//                 CHECK((codigo.getValor() != valor));
//             }
//         }
//     }
//     SECTION("Construtor", "[construtor]"){
//         Codigo* codigoptr;

//         SECTION("Valores validos", "[validos]"){
//             for(const string &valor : CODIGOS_VALIDOS){
//                 codigoptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_NOTHROW(codigoptr = new Codigo(valor));
//                 if(codigoptr != 0)
//                     CHECK((codigoptr->getValor() == valor));
                
//                 delete codigoptr;
//             }
//         }

//         SECTION("Valores invalidos", "[invalidos]"){
//             for(const string &valor : CODIGOS_INVALIDOS){
//                 codigoptr = 0;
                
//                 UNSCOPED_INFO("O valor é " << valor);

//                 CHECK_THROWS_AS(codigoptr = new Codigo(valor), invalid_argument);
                
//                 delete codigoptr;
//             }
//         }
//     }
// }

