#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

char stack[MAX];
char infix[MAX];
char postfix[MAX];
//char prefix[MAX];
int top = -1;

void push(int);
int pop();
int isEmpty();
void infix_to_postfix();
int space(char);
void print_postfix();
int precedence(char);
int postfix_eval();

//void infix_to_prefix(){
//}

int postfix_eval(){
	int i,a,b;
	for (i=0; i<strlen(postfix); i++){
		if(postfix[i] >= '0' && postfix[i] <= '9'){
			push(postfix[i]-'0');	//using ascii
		} else {
			a = pop(); //operand 1
			b = pop(); //operand 2
			switch(postfix[i]) {
				case '+':
				push(b+a);
				break;
			case '-':
				push(b-a);
				break;
			case '*':
				push(b*a);
				break;
			case '/':
				push(b/a);
				break;
			case '^':
				push(pow(b,a));
				break;
			}
		}
	}
	return pop();
}

int space(char c){
	//symbol is blank space or tab
	if(c ==' ' || c=='\t') return 1;
	else return 0;
}

int precedence(char symbol){
	switch(symbol){
		case '^':
			return 3;
		case '/':
		case '*':
			return 2;
		case '+':
		case '-':
			return 1;
		default :
			return 0;
	}
}

void print_postfix(){
	int i = 0;
	printf("The postfix expression is: ");
	while (postfix[i]){
		printf("%c", postfix[i++]);
	}
	printf("\n");
}

void push(int val){
	if(top == MAX-1){
		printf("Stack maximum\n");
		return;
	}
	top++;
	stack[top] = val;
}

int pop(){
	int val;
	if(top == -1){
		printf("There is no data\n");
		exit(1);
	}
	val = stack[top];
	top = top-1;
	return val;
}

int isEmpty(){
	if(top == -1){
		return 1;
	} else {
		return 0;
	}
}

//void infix_to_prefix(){
//int i, j = 0;
//char symbol, next;
//strrev(infix); //to reverse
//while (infix[i] != '\0'){
//	if(!space(symbol)){
//	prefix[j++]= infix[i];
//switch(symbol){
//}

void infix_to_postfix(){
	int i, j = 0;
	char symbol, next;
	for (i = 0; i < strlen(infix); i++){
		symbol = infix[i];
		if (!space(symbol)){
		
		switch(symbol){
			case '(':
				push(symbol);
				break;
			case ')':
				while ((next=pop()) != '(')
					postfix[j++] = next;
					break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				while (!isEmpty() && precedence(stack[top]) >= precedence(symbol))
					postfix[j++] = pop();
				push(symbol);
				break;
			default :
				postfix[j++] = symbol;
		}
	}
}
	while(!isEmpty())
		postfix[j++] = pop();
	postfix[j] = '\0';
}

int main(){
	// infix to postfix
	printf("Enter the infix expression: ");
	gets(infix);
	
	infix_to_postfix();
	print_postfix();
	printf("The result after postfix evaluation is: %d\n", postfix_eval());
	
	return 0;
}
