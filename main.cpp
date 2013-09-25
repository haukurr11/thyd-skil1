#include "lex.yy.cc"
#include <iostream>
int token;
FlexLexer* f = new yyFlexLexer(&std::cin,&std::cout);
void parse_error();
void lex();
void parse();
void Slist();
void S();
void NP();
void AP();
void VP();
void VPRest();

int main() {
  parse();
}

void parse_error(std::string s) {
  std::cout << "Parse error:" << s << " " << token << " " << f->YYText();
  exit(0);
}

void lex() {
  token = f->yylex();
  std::cout << f->YYText();
}

void parse() {
  Slist();
}

void Slist() 
{
  S();
  lex();
  if(token == newline) {
    Slist();
    return;
  }
}

void S() 
{
  NP();
  VP();
}

void NP() 
{
  lex();
  if(token == det) {
    AP();
    lex();
    if(token == noun)
      return;
  }
  parse_error("NP");
}

void AP() 
{
  lex();
  if(token == adj) {
    return;
  }
  else if(token == nil) {
    return;
  }
  parse_error("AP");
}

void VP() 
{
  lex();
  if(token == verb) {
    VPRest();
    return;
  }
  parse_error("VP");
}

void VPRest() 
{
  NP();
}
