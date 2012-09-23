#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include "Parser.h"
#include "AST.h"


using namespace std;

EntornoTipos* entornoTiposActual = NULL;
MethodDeclNode* funcionActual = NULL;
int fila = -1;
IterationStatement* cicloActual = NULL;

int main()
{

	try
	{
		Parser par(new Lexer("PruebaPython.txt"));

		while(par.token.getTipo() != TokenType::EOFF)
		{
			ASTNode *prgm = par.program();
			ProgramNode* programnode = dynamic_cast<ProgramNode*>(prgm);
			programnode->validarSemantica();
			programnode->Interpretar();
			//cout << endl << endl << prgm->ToString() << endl << endl ; 
		}

		if(par.token.getTipo() == TokenType::EOFF)
		{
			cout<<"Compilacion Exitosa!!"<<endl;
		}
		
	}catch(exception err){
		cout<<err.what()<<endl;
	}

	system("pause");
	return 0;
}