#include <iostream>
#include <fstream>
using namespace std;

struct EquationNode {
	char op;
	double num;
	bool isNumber;
	EquationNode * next;
};

EquationNode * newEqNode(char c)
{
	EquationNode * v = new EquationNode;
	v->next = NULL;
	v->num = 0;
	v->op = c;
	v->isNumber = false;
	return v;
}

EquationNode * newEqNode(double a)
{
	EquationNode * v = new EquationNode;
	v->next = NULL;
	v->num = a;
	v->op = -1;
	v->isNumber = true;
	return v;
}

struct equation {
	EquationNode * first;
	EquationNode * last;
};

enum type_statement {
	open,
	close,
	buy,
	add,
	times,
	discount,
	total,
	price
};

string before(string s, string b)
{
    return s.substr(0,s.find(b));
}

string after(string s, string b)
{
    return s.substr(s.find(b)+1);
}

struct lineSplit {
	string name;
	string op;
	string value;
};

lineSplit * newLineSplit()
{
	lineSplit * split = new lineSplit;
	split->name = "";
	split->op = "";
	split->value = "";
	return split;
}

struct symb {
	char op;
	double num;
	bool isNumber;
	symb * next;
};

symb * newSymb(char c)
{
	symb * v = new symb;
	v->next = NULL;
	v->num = 0;
	v->op = c;
	v->isNumber = false;
	return v;
}

symb * newSymb(double a)
{
	symb * v = new symb;
	v->next = NULL;
	v->num = a;
	v->op = -1;
	v->isNumber = true;
	return v;
}

void printSymb(symb * s)
{
	if(s->isNumber)
	{
		cout << s->num;
	}
	else
	{
		cout << s->op;
	}
}

struct stack {
	symb * top;
};

stack * newStack()
{
	stack * s = new stack;
	s->top = NULL;
	return s;
}

symb * pop(stack * s)
{
	symb * v = s->top;
	s->top = v->next;
	return v;
}

void push(symb * v, stack * s)
{
	if(s->top == NULL)
	{
		s->top = v;
	}
	else
	{
		v->next = s->top;
		s->top = v;
	}
}

void printStack(stack * s)
{
	symb * sym = s->top;
	
	while(sym)
	{
		printSymb(sym);
		sym = sym->next;
	}
	cout << endl;
}

bool isEmpty(stack * s)
{
	return s->top == NULL;
}

bool isNumber(char c)
{
	return (int)c > 47 && (int)c < 58;
}

lineSplit * split(string line)
{
	lineSplit * split = newLineSplit();
	
	split->name = before(line, "\t");
	split->op = before(after(line, "\t"), "\t");
	split->value = after(after(line, "\t"), "\t");
	
	return split;
}

bool equals(string s1, string s2)
{
	return s1.compare(s2) == 0;
}

type_statement getTypeStatement(string s)
{
	if(equals(s,"open")) 		return open;
	if(equals(s,"close")) 		return close;
	if(equals(s,"buy")) 		return buy;
	if(equals(s,"add")) 		return add;
	if(equals(s,"times")) 		return times;
	if(equals(s,"discount%")) 	return discount;
	if(equals(s,"total")) 		return total;
}

string convertToInfix(string filename)
{
    ifstream file(filename);
    
    string all = "";
    string values = "";
    string line = "";
    
    while (getline(file,line))
    {
        if(line.length() != 0 && line.at(0) != '#')
        {
            lineSplit * s = split(line);
            
            switch(getTypeStatement(s->op))
            {
				case open:	all += "(";
							break;
				case close:	all += ")";
							break;
				case buy:	all += s->value;
							break;
				case add:	all += "+" + s->value;
							break;
				case times:	all += "*" + s->value;
							break;
				case discount:	all += "*((100-" + s->value + ")/100)";
							break;
				case total:	
							break;
				case price: 
							break;
			}
        }
    }
    
    return all;
}

bool topPriority(symb * s)
{
	return s != NULL && (s->op == '*' || s->op == '/');
}

double eval(stack * s)
{
    if(!isEmpty(s))
    {
    	symb * sym = pop(s);
    	if(sym->isNumber)
    	{
    		return sym->num;
    	}
    	else 
	    {
			double e1 = eval(s);
			double e2 = eval(s);
	    	switch((int)sym->op)
    		{
		    	case 43: return e2 + e1;
	    		 		 break;
    			case 45: return e2 - e1;
			    		 break;
		    	case 42: return e1 * e2;
	    				 break;
			    case 47: return e2 / e1;
		    			 break;
	    	}
    	}
    }
}

int main(int argc, char ** argv)
{
    string filename = argv[1];
    filename = filename.substr(6);
    
    string infix = convertToInfix(filename);
    
    stack * output = newStack();
    stack * operators = newStack();
    
    bool number = false;
    int storage = 0;
    
    for(int x = 0; x < infix.length(); x++)
    {
		
	}
}
 
