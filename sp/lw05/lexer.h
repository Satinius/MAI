//                 lexer.h 2018
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
//********************************************
//*        Developed by  xxx		     *
//*             (c)  2018                    *
//********************************************
class tLexer:public tBaseLexer{
public:
// персональный код разработчика
 std::string Authentication()const{
                     return "SVS"
                +std::string("2018");}
//конструктор
 tLexer():tBaseLexer(){
//создать автоматы:

//  ноль Azero
    addstr  (Azero,0,"+-", 2);
    addstr  (Azero,0,"0",  1);
    addstr  (Azero,2,"0",  1);
  Azero.final(1);

//________________________________________

// число
    addrange(Adec,0,'0','9',1);
    addstr(Adec,0,"+-",5);
    addstr(Adec,0,"0",6);
    addstr(Adec,6,"eE",3);
    addstr(Adec,6,".",7);
    addstr(Adec,1,".",7);
    addrange(Adec, 7, '0', '9', 2);
    addrange(Adec,5,'1','9',1);
    addstr(Adec,5,"0",6);
    addrange(Adec,1,'0','9',1);
    addstr(Adec,1,"eE",3);
    addstr(Adec,2,"eE",3);
    addrange(Adec,2,'0','9',2);
    addstr(Adec,3,"0123456789",4);
    addstr(Adec,3,"+-", 8);
    addrange(Adec,8,'0','9',4);
    addrange(Adec,4,'0','9',4);
 Adec.final(1);
 Adec.final(2);
 Adec.final(4);
//________________________________________

// идентификатор
    addrange(Aid,0,'a','z',1);
    addrange(Aid,1,'a','z',1);
    addrange(Aid,0,'A','Z',1);
    addrange(Aid,1,'A','Z',1);
    addstr(Aid,0,"!",1);
    addrange(Aid,1,'a','z',1);
    addrange(Aid,1,'A','Z',1);
    addrange(Aid,1,'0','9',1);
    addstr(Aid,1,"!",1);
    addstr(Aid,1,"-",2);
    addstr(Aid,2,"-",2);
    addrange(Aid,2,'a','z',1);
    addrange(Aid,2,'A','Z',1);
    addrange(Aid,2,'0','9',1);
    addstr(Aid,2,"!",1);
  Aid.final(1);
//________________________________________

// идентификатор предиката
    addstr(Aidq,0,"?",2);
    addrange(Aidq,0,'a','z',1);
    addrange(Aidq,0,'A','Z',1);
    addstr(Aidq,0,"-",1);
    addrange(Aidq,1,'a','z',1);
    addrange(Aidq,1,'A','Z',1);
    addrange(Aidq,1,'0','9',1);
    addstr(Aidq,1,"-",1);
    addrange(Aidq,2,'a','z',1);
    addrange(Aidq,2,'A','Z',1);
    addrange(Aidq,2,'0','9',1);
    addstr(Aidq,1,"?",2);
    addstr(Aidq,2,"?",2);
  Aidq.final(2);
}
};
#endif

