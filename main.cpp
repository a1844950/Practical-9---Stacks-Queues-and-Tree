#include <iostream> 
#include <stack> 
#include <string>

using namespace std;

class PreToIn
{
public:
	PreToIn();
    PreToIn(string str);
	~PreToIn();
    string ConvertPrefixToInfix(string prefixExpression);
    void display();
    void amend();
private:
    string prefixExpression;
    string ans;
};
PreToIn::PreToIn(string str)
{
    this->prefixExpression = str;
    this->ans = this->ConvertPrefixToInfix(prefixExpression);
}
PreToIn::PreToIn()
{
    prefixExpression = "";
    ans = "";
}

PreToIn::~PreToIn()
{
}

void PreToIn::display()
{
    amend();
    cout << this->ans << endl;
}

void PreToIn::amend()
{
    if (ans!="Error")
    {
        string temp = this->ans;
        temp.erase(1, 1);
        string target = "=";
        int pos = temp.find(target)-2;
        temp = temp.erase(pos, 1);

        target = "/";
        pos = temp.find(target);
        if (pos!=-1)
        {
            int r = 0, l = 0;
            for (int i = pos; i > 0; i--)
                if (temp[i] == '(')
                    l = i;
            for (int i = pos; i < temp.size(); i++)
                if (temp[i] == ')')
                    r = i;
            temp = temp.erase(l, 1);
            temp = temp.erase(r-1, 1);

        }

       this->ans = temp;
    }

}

string PreToIn::ConvertPrefixToInfix(string prefixExpression)
{
    stack<string> InfixStack;   
    stack<long> EvalStack;       
    char ch;
    string operand = "";
    long result = 0;
    int length = prefixExpression.size();

    for (int index = length - 1; index >= 0; index--)
    {
        ch = prefixExpression[index];
        if (ch == ' ' && !operand.empty())
        {
            InfixStack.push(operand);
            EvalStack.push(atol(operand.c_str()));
            operand = "";
            continue;
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {

            if (InfixStack.size() < 2)
                return "Error";

            string op1 = InfixStack.top();
            InfixStack.pop();

            string op2 = InfixStack.top();
            InfixStack.pop();

            string temp = "(" + op1 + prefixExpression[index] + op2 + ")";

            long op1Value = EvalStack.top();
            EvalStack.pop();

            long op2Value = EvalStack.top();
            EvalStack.pop();

            if (ch == '+')
                EvalStack.push(op1Value + op2Value);
            else if (ch == '-')
                EvalStack.push(op1Value - op2Value);
            else if (ch == '*')
                EvalStack.push(op1Value * op2Value);
            else if (ch == '/')
                EvalStack.push(op1Value / op2Value);
            InfixStack.push(temp);
        }
        else
            operand += string(1, prefixExpression[index]);
    }

    if (InfixStack.size() > 1)
        return "Error";

    return InfixStack.top() + " = " + to_string(EvalStack.top());
}


int main()
{

    string str;
    getline(cin, str);
    if (str.size() == 1 || str.size() == 2 || str.size() == 0)
    {
        cout << "Error";
            return 0;
    }

    PreToIn p(str);
    p.display();

    return 0;
}