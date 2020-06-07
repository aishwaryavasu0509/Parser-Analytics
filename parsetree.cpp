#include<iostream>
#include<fstream>
#include <string>
using namespace std;

enum tokenType{
    PROGRAM, IS, BEGIN , END , VAR , INTEGER , BOOLEAN , READ , WRITE , IF , THEN , ELSE, WHILE, DO , OR , AND , TRUE , FALSE , NOT,
    ID , LPARN , RPARN , LESSEQUAL , LESS , EQUAL , GREATER , GREATEREQUAL , NOTEQUAL , PLUS , MINUS, DIV ,MULTI, COMMA , SEMICOL, COLON,
    ASSIGN , ERROR , ENDSOURCE , INTEGERVALUE
};

enum nodeType{
    UNDEFINED, START, PROGRAMN, ISN, BEGINN , ENDN , VARN , INTEGERN , BOOLEANN , READN , WRITEN , IFN , THENN, ELSEN, WHILEN, DON , ORN , ANDN , TRUEN , FALSEN , NOTN,
    IDN , LPARNN , RPARNN , LESSEQUALN , LESSN , EQUALN , GREATERN , GREATEREQUALN , NOTEQUALN , PLUSN , MINUSN, DIVN,MULTIN , COMMAN , SEMICOLN, COLONN,
    ASSIGNN ,PROGN,BLOCKN,DECSEQN,DECN,TYPEN,VARLISTN,VARLISTTAILN,COMSEQN,COMSEQTAILN,COMN,COMTAILN,EXPRN,EXPRTAILN,SIMEXPRN,SIMEXPRTAILN,
    TERMN,TERMTAILN,VARFN, RELATN,WEAKN,STRONGN,ELEMENTN,INTEGERVALUEN
};
//*****************************************
class Token{
public :
    tokenType type;
    string name;
    Token(){
        type = ERROR;
        name="";
    }
};
//*****************************************
class Node{
public:
    nodeType type;
    string Lexeme;
    Node* child[6];		// array of pointers (6 pointers)
    Node(){
        for(int i=0;i<6;i++){
            child[i]=NULL;
        }
    }
    ~Node(){
        for(int i=0;i<6;i++)
            delete child[i];
        }
};
//*****************************************
Node * root;			// pointer that pointing to the root node
//*****************************************
//*****************************************
//*****************************************
//*****************************************
//*****************************************
class Parser{
private:
    fstream f;
    Token currentToken;				//currentToken>>class>>(type,name)

    Token getToken(){				// ( >>>>>>>>>>>>>>>>>>>>>>>> (type:LPARN , name:"(")
	    char ch;
	    Token t;
	    f.get(ch);
	    while(isspace(ch)){
	        f.get(ch);
	        if(f.eof())
	        {
	            t.name="$$";
	            t.type=ENDSOURCE;
	            return t;
	        }
	    }

	    if(f.eof()){
	            t.name="$$";
	            t.type=ENDSOURCE;
	    }
	    else if(ch=='('){t.name=ch ;  t.type=LPARN;}		//t.name="(";
	    else if(ch==')'){t.name=ch ; t.type= RPARN;}
	    else if(ch=='+'){t.name= ch; t.type= PLUS;}
	    else if(ch=='-'){t.name= ch; t.type=MINUS ;}
	    else if(ch=='*'){t.name= ch; t.type=MULTI ;}
	    else if(ch=='/'){t.name= ch; t.type= DIV;}
	    else if(ch==';'){t.name=ch ; t.type= SEMICOL;}
	    else if(ch=='='){t.name=ch ; t.type= EQUAL;}
	    else if(ch==','){t.name=ch ; t.type= COMMA;}

	    else if(ch=='<')
	        {
	            t.name=ch ;
	            f.get(ch);
	            if(ch=='>'){
	                t.name+=ch;		//t.name="<>";
	                t.type=NOTEQUAL;
	            }
	            else if(ch=='='){
	                t.name+=ch;		//t.name = "<=";
	                t.type=LESSEQUAL;
	            }
	            else{
	                f.putback(ch);
	                t.type=LESS;	//t.name = "<";		return t >> t(name="<" , type=LESS)
	            }
	        }
	    else if(ch=='>')
	        {
	            t.name=ch ;
	            f.get(ch);
	            if(ch=='='){
	                t.name+=ch;
	                t.type=GREATEREQUAL;
	            }
	            else{
	                f.putback(ch);
	                t.type=GREATER;
	            }
	        }
	        else if(ch==':'){
	            t.name=ch;
	            f.get(ch);
	            if(ch=='='){
	                t.name+=ch;
	                t.type=ASSIGN;
	            }
	            else{
	                f.putback(ch);
	                t.type=COLON;
	            }
	        }
	        else if(isalpha(ch)){
	            t.name=ch;
	            f.get(ch);
	            while(isalnum(ch)){		//program	t.name="program" , t.type=	>>chech_reserved(t){t.name="program">>t.type=PROGRAM_SY}
	                t.name+=ch;
	                f.get(ch);
	            }
	            f.putback(ch);
	            return checkReserved(t);
	        }
	        else if(isdigit(ch)){
	            t.name=ch;
	            f.get(ch);
	            while(isdigit(ch)){
	                t.name+=ch;			// 250  t.name="250" , t.type=INTEGERVALUE
	                f.get(ch);
	            }
	            f.putback(ch);
	            t.type=INTEGERVALUE;
	        }
	        else{
	                t.name="ERROR !";
	                t.type=ERROR;
	        }

   //must be executed
	        return t;
}
//*****************************************
  Token checkReserved(Token t){
    if(t.name=="program") t.type=PROGRAM;
    else if(t.name=="is") t.type=IS;
    else if(t.name== "begin") t.type=BEGIN;
    else if(t.name== "end") t.type=END;
    else if(t.name== "var") t.type=VAR;
    else if(t.name== "integer") t.type=INTEGER;
    else if(t.name== "boolean") t.type=BOOLEAN;
    else if(t.name== "read") t.type=READ;
    else if(t.name== "write") t.type=WRITE;
    else if(t.name== "if") t.type=IF;
    else if(t.name== "then") t.type=THEN;
    else if(t.name== "else") t.type=ELSE;
    else if(t.name== "while") t.type=WHILE;
    else if(t.name== "or") t.type=OR;
    else if(t.name== "and") t.type=AND;
    else if(t.name== "true") t.type=TRUE;
    else if(t.name== "false") t.type=FALSE;
    else if(t.name== "not") t.type=NOT;
    else t.type=ID;
    return t;
}



//*****************************************


//*****************************************//*****************************************

// program id is	>> Grammar
// program x is     >> File			>> current_token(type=PROGRAM_SY  , name = "program")


// match(program);
// match(id);
// match(is);

void match(tokenType type){		//type=PROGRAM_SY
    if(currentToken.type==type){
        cout<<currentToken.name<<" is matched\n";			// program is matched
    }
    else{
        syntaxError(currentToken);
    }
    if(type!=ENDSOURCE)
        currentToken=getToken();
}
//*****************************************
void syntaxError(Token t){
    cout<<t.name<<" isn't expected\n";			//program is not expected
}
//*****************************************//*****************************************


//*****************************************
/// <program> ::= program <id> is <block>
Node* program(){
    Node* ptr= new Node();
    ptr->type=PROGN;
    if(currentToken.type==PROGRAM){
        ptr->child[0]=new Node();
        ptr->child[0]->Lexeme=currentToken.name;
        ptr->child[0]->type=PROGRAMN;
    }
    match(PROGRAM);
    if(currentToken.type==ID){
        ptr->child[1]=new Node();
        ptr->child[1]->Lexeme=currentToken.name;
        ptr->child[1]->type=IDN;
    }
    match(ID);
    if(currentToken.type==IS){
        ptr->child[2]=new Node();
        ptr->child[2]->Lexeme=currentToken.name;
        ptr->child[2]->type=ISN;
    }
    match(IS);
    ptr->child[3]=block();
    return ptr;
}
//*****************************************
/// <block> ::= <dec-seq> begin <command-seq> end
Node* block(){
    Node*ptr=new Node();
    ptr->type=BLOCKN;
    ptr->child[0]=decSeq();
    if(currentToken.type==BEGIN){
        ptr->child[1]=new Node();
        ptr->child[1]->type=BEGINN;
        ptr->child[1]->Lexeme=currentToken.name;
    }
    match(BEGIN);
    ptr->child[2]=comSeq();
    if(currentToken.type==END){
        ptr->child[3]=new Node();
        ptr->child[3]->Lexeme=currentToken.name;
        ptr->child[3]->type=ENDN;
    }
    match(END);
    return ptr;
}
//*****************************************
/// <dec-seq> ::= E | <dec><dec-seq>
Node* decSeq(){
    Node* ptr=new Node();
    ptr->type=DECSEQN;
    if(currentToken.type==VAR){
        ptr->child[0]=dec();
        ptr->child[1]=decSeq();
    }
    return ptr;
}
//*****************************************
/// <dec> ::= var <varlist> : <type> ;
Node* dec(){
    Node* ptr=new Node();
    ptr->type=DECN;
    if(currentToken.type==VAR){
        ptr->child[0]=new Node();
        ptr->child[0]->Lexeme=currentToken.name;
        ptr->child[0]->type=VARN;
    }
    match(VAR);
    ptr->child[1]=varList();
    if(currentToken.type==COLON){
        ptr->child[2]=new Node();
        ptr->child[2]->Lexeme=currentToken.name;
        ptr->child[2]->type=COLONN;
    }
    match(COLON);
     ptr->child[3]=type();
    if(currentToken.type==SEMICOL){
        ptr->child[4]=new Node();
        ptr->child[4]->Lexeme=currentToken.name;
        ptr->child[4]->type=SEMICOLN;
    }
    match(SEMICOL);

    return ptr;
}
//*****************************************
/// <type> ::= integer | boolean
Node* type(){
    Node* ptr=new Node();
    ptr->type=TYPEN;
    switch(currentToken.type){
    case INTEGER:
        ptr->child[0]=new Node();
        ptr->child[0]->Lexeme=currentToken.name;
        ptr->child[0]->type=INTEGERN;
        match(INTEGER);
        break;
    case BOOLEAN:
        ptr->child[0]=new Node();
        ptr->child[0]->Lexeme=currentToken.name;
        ptr->child[0]->type=BOOLEANN;
        match(BOOLEAN);
        break;
    default:
        syntaxError(currentToken);
    }
    return ptr;
}
//*****************************************
/// <var-list> ::= <var> | <var> , <var-list> -------- Left Common Prefix ---------
/// <var-list> ::= <var><var-list-tail>
Node*  varList(){
    Node* ptr=new Node();
    ptr->type=VARLISTN;
    ptr->child[0]=var();
    ptr->child[1]=varListTail();
    return ptr;
}
//*****************************************
/// <var-list-tail> ::= E | , <var-list>
Node*  varListTail(){
    Node* ptr=new Node();
    ptr->type= VARLISTTAILN;
    if(currentToken.type==COMMA){
        ptr->child[0]=new Node();
        ptr->child[0]->type=COMMAN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(COMMA);
        ptr->child[1]=varList();
    }
    return ptr;
}
//*****************************************
/// <com-seq> ::= <com> | <com> ; <com-seq>     ---------- Left Common Prefix --------
/// <com-seq> ::= <com> <com-seq-tail>
Node*  comSeq(){
    Node* ptr=new Node();
    ptr->type=COMSEQN;
    ptr->child[0]=command();
    ptr->child[1]=comSeqTail();
    return ptr;
}

//*****************************************
/// <com-seq-tail> ::= E | ; <com-seq>
Node*  comSeqTail(){
    Node* ptr=new Node();
    ptr->type=COMSEQTAILN;
    if(currentToken.type==SEMICOL){
        ptr->child[0]=new Node();
        ptr->child[0]->type=SEMICOLN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(SEMICOL);
        ptr->child[1]=comSeq();
    }
    return ptr;
}
//*****************************************
/// <com> ::= <var> := <expr> | read <var> | write <expr> | while <expr> do <com-seq> end while
///                     | if <expr> then <com-seq> end if | if <expr> then <com-seq> else <com-seq> end if

/// ------------------------------ Left Common Prefix in if statements ------------------------

/// <com> ::= <var> := <expr> | read <var> | write <expr> | while <expr> do <com-seq> end while
///                     | if <expr> then <com-seq> <com-tail>

Node*  command(){
    Node* ptr=new Node();
    ptr->type=COMN;

    switch(currentToken.type){

    case ID:
        ptr->child[0]=var();
        if(currentToken.type==ASSIGN){
            ptr->child[1]=new Node();
            ptr->child[1]->type=ASSIGNN;
            ptr->child[1]->Lexeme=currentToken.name;
        }
        match(ASSIGN);
        ptr->child[2]=expr();
        break;


    case READ:
        ptr->child[0]=new Node();
        ptr->child[0]->type= READN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(READ);
        ptr->child[1]=var();
        break;


    case WRITE:
        ptr->child[0]=new Node();
        ptr->child[0]->type=WRITEN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(WRITE);
        ptr->child[1]=expr();
        break;

    case WHILE:
        ptr->child[0]=new Node();
        ptr->child[0]->type=WHILEN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(WHILE);
        ptr->child[1]=expr();
        if(currentToken.type==DO){
            ptr->child[2]=new Node();
            ptr->child[2]->type=DON;
            ptr->child[2]->Lexeme=currentToken.name;
        }

        match(DO);
        ptr->child[3]=comSeq();
        if(currentToken.type==END){
            ptr->child[4]=new Node();
            ptr->child[4]->type=ENDN;
            ptr->child[4]->Lexeme=currentToken.name;
        }
        match(END);
        if(currentToken.type==WHILE){
            ptr->child[5]=new Node();
            ptr->child[5]->type=WHILEN;
            ptr->child[5]->Lexeme=currentToken.name;
        }
        match(WHILE);
        break;

    //if <expr> then <com-seq> <com-tail>
    case IF:
        if(currentToken.type==IF){
            ptr->child[0]=new Node();
            ptr->child[0]->type=IFN;
            ptr->child[0]->Lexeme=currentToken.name;
        }
        match(IF);
        ptr->child[1]=expr();
        if(currentToken.type==THEN){
            ptr->child[2]=new Node();
            ptr->child[2]->type=THENN;
            ptr->child[2]->Lexeme=currentToken.name;
        }
        match(THEN);
        ptr->child[3]=comSeq();
        ptr->child[4]=comTail();
        break;
    default : syntaxError(currentToken);
    }

    return ptr;
}
//*****************************************
/// <com-tail> ::= end if | else <com-seq> end if
Node*  comTail(){
    Node* ptr=new Node();
    ptr->type=COMTAILN;		//commandtailNode
    switch(currentToken.type){
    case END:
        ptr->child[0]=new Node();
        ptr->child[0]->type= ENDN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(END);
        if(currentToken.type==IF){
            ptr->child[1]=new Node();
            ptr->child[1]->type= IFN;
            ptr->child[1]->Lexeme=currentToken.name;
        }
        match(IF);
        break;
    case ELSE:
            ptr->child[0]=new Node();
            ptr->child[0]->type= ELSEN;
            ptr->child[0]->Lexeme=currentToken.name;
            match(ELSE);
            ptr->child[1]=comSeq();
        if(currentToken.type==END){
            ptr->child[2]=new Node();
            ptr->child[2]->type= ENDN;
            ptr->child[2]->Lexeme=currentToken.name;
        }
        match(END);
        if(currentToken.type==IF){
            ptr->child[3]=new Node();
            ptr->child[3]->type= IFN;
            ptr->child[3]->Lexeme=currentToken.name;
        }
        match(IF);
        break;
    default:
        ;
    }
    return ptr;
}
//*****************************************
/// <expr> ::= <simple-expr> | <simple-expr><relation><simple-expr> ------------ Left Common Prefix --------------
/// <expr> ::=<simple-expr> <expr-tail>
Node*  expr(){
    Node* ptr= new Node();
    ptr->type=EXPRN;
    ptr->child[0]=simpExpr();
    ptr->child[1]=exprTail();
    return ptr;
}
//*****************************************
/// <expr-tail> ::= E | <relation> < simple-expr>
Node*  exprTail(){
    Node* ptr=new Node();
    ptr->type=EXPRTAILN;
    if(currentToken.type==LESS||currentToken.type==LESSEQUAL||currentToken.type==NOTEQUAL||currentToken.type==EQUAL||
       currentToken.type==GREATER||currentToken.type==GREATEREQUAL){
           ptr->child[0]=relat();
           ptr->child[1]=simpExpr();
       }
    return ptr;
}
//*****************************************
/// <simple-expr> ::= <term> | <simple-expr><weak op><term> ------------ Left Recursive --------------
/// <simple-expr> ::=<term> <simple-expr-tail>
Node*  simpExpr(){
    Node* ptr=new Node();
    ptr->type= SIMEXPRN;
    ptr->child[0]=term();
    ptr->child[1]=simpExprTail();
    return ptr;
}
//*****************************************
/// <simple-expr-tail> ::= E | <weak op> <term> <simple-expr-tail>
Node*  simpExprTail(){
    Node* ptr=new Node();
    ptr->type=SIMEXPRTAILN;
    if(currentToken.type==PLUS||currentToken.type==MINUS||currentToken.type==OR){
        ptr->child[0]=weak();
        ptr->child[1]=term();
        ptr->child[2]=simpExprTail();
    }
    return ptr;
}
//*****************************************
/// <term>::= <element> | <term> < strong op > <element> ------------ Left Recursive --------------
/// <term> ::= <element> < term-tail>
Node*  term(){
    Node* ptr=new Node();
    ptr->type=TERMN;
    ptr->child[0]=element();
    ptr->child[1]=termTail();
    return ptr;
}
//*****************************************
/// <term-tail> ::= E | <strong op> <element> <term-tail>
Node*  termTail(){
    Node* ptr=new Node();
    ptr->type=TERMTAILN;
    if(currentToken.type==MULTI||currentToken.type==DIV||currentToken.type==AND){
        ptr->child[0]=strong();
        ptr->child[1]=element();
        ptr->child[2]=termTail();
    }
    return ptr;
}

//*****************************************
/// <element> ::= <numeral> | <var> | ( <expr> ) | true | false | not <element> | - <element>
Node*  element(){
    Node* ptr=new Node();
    ptr->type=ELEMENTN;
    switch(currentToken.type){
    case INTEGERVALUE:
        ptr->child[0]=new Node();
        ptr->child[0]->type=INTEGERVALUEN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(INTEGERVALUE);
        break;
    case ID:
        ptr->child[0]=var();
        break;
    case LPARN:
        ptr->child[0]=new Node();
        ptr->child[0]->type=LPARNN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(LPARN);
        ptr->child[1]=expr();
        if(currentToken.type==RPARN){
            ptr->child[2]=new Node();
            ptr->child[2]->type=RPARNN;
            ptr->child[2]->Lexeme=currentToken.name;
        }
        match(RPARN);
        break;
    case TRUE:
        ptr->child[0]=new Node();
        ptr->child[0]->type=TRUEN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(TRUE);
        break;
    case FALSE:
        ptr->child[0]=new Node();
        ptr->child[0]->type=FALSEN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(FALSE);
        break;
    case NOT:
        ptr->child[0]=new Node();
        ptr->child[0]->type=NOTN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(NOT);
        ptr->child[1]=element();
        break;
    case MINUS:
        ptr->child[0]=new Node();
        ptr->child[0]->type=MINUSN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(MINUS);
        ptr->child[1]=element();
        break;
    default:
        syntaxError(currentToken);

    }
    return ptr;
}
//*****************************************
/// <var> ::= ID
Node*  var(){
    Node* ptr=new Node();
    ptr->type=VARN;
    ptr->child[0]=new Node();
    ptr->child[0]->type=IDN;
    ptr->child[0]->Lexeme=currentToken.name;
    match(ID);
    return ptr;
}
//*****************************************
/// <relation> ::= < | <= | <> | = | > | >=
Node*  relat(){
    Node* ptr=new Node();
    ptr->type=RELATN;
    switch(currentToken.type){
    case LESS:
        ptr->child[0]=new Node();
        ptr->child[0]->type=LESSN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(LESS);
        break;
    case LESSEQUAL:
        ptr->child[0]=new Node();
        ptr->child[0]->type=LESSEQUALN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(LESSEQUAL);
        break;
    case EQUAL:
        ptr->child[0]=new Node();
        ptr->child[0]->type=EQUALN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(EQUAL);
        break;
    case NOTEQUAL:
        ptr->child[0]=new Node();
        ptr->child[0]->type=NOTEQUALN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(NOTEQUAL);
        break;
    case GREATER:
        ptr->child[0]=new Node();
        ptr->child[0]->type=GREATERN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(GREATER);
        break;
    case GREATEREQUAL:
        ptr->child[0]=new Node();
        ptr->child[0]->type=GREATEREQUALN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(GREATEREQUAL);
        break;
    default:
        syntaxError(currentToken);
    }
    return ptr;
}
//*****************************************
/// <weak op>::= + | - | or
Node*  weak(){
    Node* ptr=new Node();
    ptr->type=WEAKN;
    switch(currentToken.type){
    case PLUS:
        ptr->child[0]=new Node();
        ptr->child[0]->type=PLUSN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(PLUS);
        break;
    case MINUS:
        ptr->child[0]=new Node();
        ptr->child[0]->type=MINUSN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(MINUS);
        break;
    case OR:
        ptr->child[0]=new Node();
        ptr->child[0]->type=ORN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(OR);
        break;
    default:
        syntaxError(currentToken);
    }
    return ptr;
}
//*****************************************

/// <strong op> ::= * | / | and
Node*  strong(){
    Node* ptr=new Node();
    ptr->type=STRONGN;
    switch(currentToken.type){
    case MULTI:
        ptr->child[0]=new Node();
        ptr->child[0]->type=MULTIN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(MULTI);
        break;
    case DIV:
        ptr->child[0]=new Node();
        ptr->child[0]->type=DIVN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(DIV);
        break;
    case AND:
        ptr->child[0]=new Node();
        ptr->child[0]->type=ANDN;
        ptr->child[0]->Lexeme=currentToken.name;
        match(AND);
        break;
    default:
        syntaxError(currentToken);
    }
    return ptr;
}

//***************************************************************************************************************************
//***************************************** END OF PRIVATE MEMBERS **********************************************************
//***************************************************************************************************************************
public:
    Parser(string fileName){
		f.open(fileName.c_str());
			 if (!f)
		     {
		          cout<<"Unable to open file"<<endl; //system("pause");
		          //exit(1);
		     }
	}
//*****************************************
    ~Parser(){
		f.close();
	}
//*****************************************
//<sampleParser> ::= <program> eof
void  sampleParser(){
	    Node* ptr = new Node();									//START
	    root=ptr;

	    ptr->type=START;
	    currentToken=getToken();
	    ptr->child[0]=program();
	    if(currentToken.type==ENDSOURCE){
	        ptr->child[1]=new Node();
	        ptr->child[1]->Lexeme=currentToken.name;
	    }
	    match(ENDSOURCE);
}

//******************************************
void displayTree(Node* Tree){		//Tree = root
    if(Tree){
        cout<<"|||| " <<Tree->Lexeme<<endl;
        displayTree(Tree->child[0]);
        displayTree(Tree->child[1]);
        displayTree(Tree->child[2]);
        displayTree(Tree->child[3]);
        displayTree(Tree->child[4]);
        displayTree(Tree->child[5]);
    }
}
//*****************************************

//*****************************************
};	// Class Ending
int main(){
	string filename;
	cout<<"Filename?: ";
	cin>>filename;
    Parser in(filename);
    in.sampleParser();
    in.displayTree(root);
    return 0;
}

