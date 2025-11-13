/**
 * @file lab5.cpp
 * @author : Tianze Li
 * @description Doubly LinkedList implementation in C++
 * @date modified 2025-02-16
 */
//starter_code_begins
#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<ctype.h>

using namespace std;

bool isOperator(char); //Function that checks if the input char is an operator
bool isgeq(char, char); //Helper function that compare two operators  and return True if the presedence of first operator is greater than or equal to the second operator
int convertOpToInt (char); //Function that converts operators into int so their precdence can be compared
string infix2postfix(string);   //Function that converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);	 //Function that will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton that will check for balanced parentheses 
//==========================================
int main()
{

	while(true)
	{
		string infix;  						//Infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>infix;
		try
		{
			if(infix=="exit") 	break;
			
			else if(!isBalanced(infix)) 
			{
				cout<<"Expression is not Balanced "<<endl;
				continue;
			}

			string postfix = infix2postfix(infix);	//Postfix Expression
			cout<<"The postfix form is: "<<postfix<<endl;
			float ans=evaluate(postfix);			//evaluate the postfix Expresion
			cout<<infix<<"="<<ans<<endl;		//print the final answer
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}

	return EXIT_SUCCESS;
}

bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;
}
//Function that converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper method that compare two operators and return True if first operator
//has greater or equal predence than the second operator
bool isgeq(char opA, char opB)
{
	return (convertOpToInt(opA)>=convertOpToInt(opB));
}
//starter_code_ends

//===============================================================================
//uses template to reduce redundent code of typenames
template <typename T>
class MyStack {
private:
    T* arr;
    int capacity;
    int topIndex;

public:
	//the constructor of the array based stack of capacity of 100 and topindex of -1
    MyStack(int size = 100) : capacity(size), topIndex(-1) {
		//array created dynamically of size 100
        arr = new T[capacity];
    }
	//destructor of the class
    ~MyStack() {
		//deletes the array
        delete[] arr;
    }
	//push function of the class
    void push(T e) {
		//check if stack is full then throws an error
        if (topIndex == capacity - 1) {
            throw overflow_error("Stack is full");
        }
		//push the new element into the stack
        arr[++topIndex] = e;
    }
	//pop function of the class
    void pop() {
		//checks if the array is empty then throws an error
        if (empty()) {
            throw underflow_error("Stack is empty");
        }
		//decrements the topindex
        topIndex--;
    }
	//top function of the class
    T& top() {
		//checks if the array is empty then throws an error
        if (empty()) {
            throw underflow_error("Stack is empty");
        }
		//returns the element at the topindex of the array
        return arr[topIndex];
    }
	//size function of the class
    int size() {
		//returns the size of the array by doing topindex + 1
        return topIndex + 1;
    }
	//empty function of the class
    bool empty() {
		//returns true if the array is empty
        return topIndex == -1;
    }
};
//===============================================================================


//Function that will check for balanced parentheses 
bool isBalanced(string expression)
{
	//intiallises a char type array based stack
	MyStack<char> stack;
	//loops through the whole string expression
    for (char ch : expression) {
		//if the character = "("
        if (ch == '(') {
			//then push it into the stack
            stack.push(ch);
		//when character is ")"
        } else if (ch == ')') {
			//if the stack is empty then return false
            if (stack.empty()) {
                return false;
            }
			//remove the character on the of the stack
            stack.pop();
        }
    }
	//check if there is any character in the array. if the array is empty then it is balanced
	//otherwise it is not balanced.
    return stack.empty();
}

// Function that converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix)
{
	//intiallises a char type array based stack
	MyStack<char> stack;
	//intiallises a string called postfix
    string postfix = "";
	//loop through all the characters in the infix expression
    for (char ch : infix) {
		//if the scanned character is a operand
        if (isdigit(ch)) {
			//then add it to the postfix expression
            postfix += ch;
		//if the scanned character is an operator
		} else if (isOperator(ch)) {
			//loop while stack is not empty and the stack on top is not "(" and has higher 
			//or same precedence then the scanned operator
            while (!stack.empty() && stack.top() != '(' && isgeq(stack.top(), ch)) {
				//pop the stack and add it to the postfix expression
                postfix += stack.top();
                stack.pop();
            }
			//push the scanned operator into the stack
            stack.push(ch);
		//if the scanned character is "("
        } else if (ch == '(') {
		//then push it onto the stack
            stack.push(ch);
		//if the scanned character is ")"
        } else if (ch == ')') {
			//loops while stack is not empty and the stack on top is not "("
            while (!stack.empty() && stack.top() != '(') {
				//pop the stack and add it to the postfix expression
                postfix += stack.top();
                stack.pop();
            }
			//pop "(" from the top of the stack
            stack.pop(); 
		}
    }
	//lastly loop through the stack and pop all of the remaining operators from the stack 
	//and add them to the postfix expression
    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }
	//returns the postfix expression
    return postfix;
}
//Function that will evaluate a PostfixExpression and return the result
float evaluate(string postfix)		
{	
	//intiallises a float type array based stack
	MyStack<float> stack;
	//loop through each character of the postfix expression
    for (char ch : postfix) {
		//if the character is a operand
        if (isdigit(ch)) {
			//convert it into an "int" push it to the stack
            stack.push(ch - '0');
		//if it is a operator
        } else if (isOperator(ch)) {
			//pop 2 elements from the stack and and store its values
            float operand2 = stack.top(); stack.pop();
            float operand1 = stack.top(); stack.pop();
			//intiallise a float value called result
            float result;
			//uses the switch and case to apply which every operator that is scanned on the 
			//2 elements that was poped 
            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = pow(operand1, operand2); break;
				//validates that the operator is value or else throws an error
                default: throw invalid_argument("Invalid operator");
            }
			//push the result back into the stack
            stack.push(result);
        }
    }
	//the final value left in the stack is the final answer so return that value
    return stack.top();
}