#include <iostream>
#include <vector>
using namespace std;
 
bool is(char a, char b){
    if(a == '{' && b == '}'){
        return true;
    } else if(a == '[' && b == ']'){
        return true;
    } else if(a == '(' && b == ')'){
        return true;
    } else {
        return false;
    }
}
 
string isBalanced(string a){
    vector<char> v(a.begin(), a.end());
    int j = v.size()/2;
    int cont=0;
    for (size_t i = 0; i < j; ++i) {
        if(is(v[i], v[((2*j)-1)-i]) == true){
            cont++;
        }
 
    }
   
    if(cont == j){
        return "Si";
    }else{
        return "NO";
    }
   
 
 
 
}
int main(){
    string a1 = "{[()]}";
    string a2 = "[(])";
    string a3 = "[[(())]]";
 
    cout << isBalanced(a1) << endl;
    cout << isBalanced(a2) << endl;
    cout << isBalanced(a3) << endl;
 
    return 0;
}
