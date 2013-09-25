%option c++
%option noyywrap

%{
enum DataType {
newline,
det,
noun,
adj,
verb,
nil,
error
};
%}

%%
[ ]   {}
"the"    {return det;}
"good"   {return adj;}
"man"    {return noun;}
"ate"    {return verb;}
"a"      {return det;}
"fish"   {return noun;}
"strong" {return adj;}
"woman"  {return noun;}
"ran"    {return verb;}
"\n"     {return newline;}
.        {return error;}
%%
