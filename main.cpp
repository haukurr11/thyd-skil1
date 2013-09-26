#include "lex.yy.cc"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int token;
string prevtoken_s;
FlexLexer* f = new yyFlexLexer(&std::cin,&cout);
string sentence;

bool match(int t);
bool Slist();
bool S();
bool NP();
bool AP();
bool VP();
bool VPRest();

int main() {
  token = f->yylex();
  Slist();
}


bool match(int t) {
  if(token == t) {
    prevtoken_s = f->YYText();
    token = f->yylex();
    return true;
  }
  if(token == error)
  {
    cout << "ERROR: Token not recognized!:" << f->YYText() << "\n";
    exit(0);
  }
  return false;
}


bool Slist() 
{
  if(S()) {
    if(match(newline)) {
      return Slist();
    }
    return true;
  }
  return false;
}

bool S() 
{
  sentence = "[S";
  if(!NP() || !VP()) {
    return false;
  };
  sentence += " ]";
  cout << sentence << "\n";
  return true;
}

bool NP()
{
  if(match(det)) {
    sentence += (" [NP " + prevtoken_s + " ");
    if(AP()) {
      if(match(noun))
        sentence += (prevtoken_s);
        sentence += " ]";
        return true;
     }
  }
  return false;
}

bool AP() 
{
  if(match(adj)) {
    sentence += ("[AP " + prevtoken_s + " ] ");
  }
  return true;
}

bool VP() 
{
  if(match(verb)) {
    sentence += (" [VP " + prevtoken_s);
    if(VPRest())
      sentence += " ]";
      return true;
  }
  return false;
}

bool VPRest() 
{
  return NP() || true;
}
