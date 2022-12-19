#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include <utility>
#include <vector>
 
 
using namespace std;
 
template<class T>
class Node
{
    public:
        int m_row;
        int m_column;
        Node<T>* m_pNext_row;
        Node<T>* m_pNext_column;
        T m_Data;
    public:
        Node(T data, int row, int column)
        {
            m_Data = data;
            m_row = row;
            m_column = column;
            m_pNext_row =m_pNext_column = 0;
        }
        ~Node(){}
 
};
 
 
template<class T, int row_size=11, int column_size=11>
class Matrix{
    private:
        Node<T>* m_Row[row_size];
        Node<T>* m_Column[column_size];
    public:
        Matrix(){
            for(int i=0;i<row_size;i++)
                m_Row[i]=0;
            for(int i=0;i<column_size;i++)
                m_Column[i]=0;
 
        };
        void Insert(T data, int row, int column)
        {
            Node<T> ** var1,**var2;
            bool byr =  find_row(row, column, var1);
            bool byc =  find_column(row, column, var2);
            if(!byr && !byc){
                Node<T> * pNew = new Node<T>(data,row,column);
                pNew->m_pNext_row = *var1;
                (*var1) = pNew;
                pNew->m_pNext_column = *var2;
                (*var2) = pNew;
            }
 
            (*var1)->m_Data = data;
        }
 
 
 
        void delete_matrix(int row, int column){
            Node<T> ** var1,**var2;
            bool byr =  find_row(row, column, var1);
            bool byc =  find_column(row, column, var2);;
            if(byr && byc){
                Node<T> * tmp = *var2;
                *var1 = tmp->m_pNext_column;
                *var2 = tmp->m_pNext_row;
                delete tmp;
            }
        }
 
 
        bool find_row(int row, int column, Node<T> ** & aux){
            aux = &m_Column[column];
            while(*aux ){
                if((*aux )->m_row == row) return true;
                if((*aux )->m_row < row) return false;
                aux  = &((*aux)->m_pNext_row);
            }
            return false;
        }
 
 
 
        bool find_column(int row, int column, Node<T> ** & aux){
            aux = &m_Row[row];
            while(*aux){
                if((*aux)->m_column == column) return true;
                if((*aux)->m_column < column) return false;
                aux = &((*aux)->m_pNext_column);
            }
            return false;
        }
 
 
        void Delete(int row, int column);
        void change(int row, int column);
        void Sum(int row);
        void Sum(int row, int begin, int end);
        void Print(){
            cout<<"    ";
            for(int j=0;j<column_size;j++)
                cout<<"C"<<j<<": ";
            cout<<endl;
            for(int i=0;i<row_size;i++){
                cout<<"F"<<i<<": ";
                for(int j=0;j<column_size;j++){
                    Node<T> **aux;
                    if(find_column(i,j,aux))
                        cout<<(*aux)->m_Data<<"   ";
                    else
                        cout<<"0   ";
                }
                cout<<endl;
            }
        }
 
        void generar_dot(){
            string dot = "digraph Matriz{\n"
            "\t node [shape=box]\n"
            "\t bgcolor=white\n";
            record(dot);
            dot+="}";
            //cout<<dot<<endl;
            ofstream fs("me.dot");
            fs<<dot<<endl;
            fs.close();
            string comando = "dot -Tjpeg me.dot  -o me.png";
            system(comando.c_str());
        }
 
        void record(string &dot){
            dot+="\tMt[ label = \"Matrix\", width = 1.5, style = filled, fillcolor = yellow , group = 1 ];\n";
            dot+="\t e0[ shape = point, width = 0 ];\n\t e1[ shape = point, width = 0 ];\n";
 
            //Filas
            dot+="\nF0 [label = \"Fila 0\" pos = \"5.3,3.5!\" width = 1.5 style = filled, fillcolor = lightgray, group = 1 ];";
            for(int j=1;j<row_size;j++){
                dot+="\tF"+to_string(j)+"[label=\"Fila "+to_string(j)+"\" width = 1.5 style=filled, fillcolor=lightgray, group = 1];\n";
            }
            for(int j=0;j<row_size;j++){
                if(j+1 < row_size)
                    dot+="\nF"+to_string(j)+"-> F"+to_string(j+1)+";";
            }
 
            //Columnas
            int cont = 2;
            for(int j=0;j<column_size;j++){
                dot+="\nC"+to_string(j)+"[label=\"Columna "+to_string(j)+"\" width = 1.5 style=filled, fillcolor=lightgray, group = "+to_string(cont)+"];\n";
                cont++;
            }
 
            for(int j=0;j<column_size;j++){
                if(j+1 < column_size)
                    dot+="C"+to_string(j)+" -> C"+to_string(j+1)+";";
            }
 
            dot+="Mt -> C0;Mt -> F0;\n\t{ rank = same; Mt;";
            for(int i = 0; i<column_size;i++){
                dot+="C"+to_string(i)+";";
            }
            dot+="}\n";
 
            //CONTENIDO
            for(int i=0;i<row_size;i++){
                for(int j=0;j<column_size;j++){
                    Node<T> **p;
                    if(find_column(i,j,p))
                        dot+="\nF"+to_string(i)+"_C"+to_string(j)+"[label=\""+to_string((*p)->m_Data)+"\"width = 1.5, group = "+to_string(j+2)+"];";
                    else
                        dot+="\nF"+to_string(i)+"_C"+to_string(j)+"[label=\"0\"width = 1.5, group = "+to_string(j+2)+"];";
                }
            }
 
            for(int i=0;i<row_size;i++)
                dot+="F"+to_string(i)+" -> F"+to_string(i)+"_C0"+";\n";
            for(int i=0;i<column_size;i++)
                dot+="C"+to_string(i)+" -> F0_C"+to_string(i)+";\n";
            for(int i=0;i<row_size;i++){
                for(int j=0;j<column_size;j++){
                    if(j+1 < column_size){
                        dot+="F"+to_string(i)+"_C"+to_string(j)+" -> F"+to_string(i)+"_C"+to_string(j+1)+";\n";
                        dot+="F"+to_string(i)+"_C"+to_string(j+1)+" -> F"+to_string(i)+"_C"+to_string(j)+";\n";
                    }
                }
            }
            for(int i=0;i<column_size;i++){
                for(int j=0;j<row_size;j++){
                    if(j+1 < column_size){
                        dot+="F"+to_string(j)+"_C"+to_string(i)+" -> F"+to_string(j+1)+"_C"+to_string(i)+";\n";
                        dot+="F"+to_string(j+1)+"_C"+to_string(i)+" -> F"+to_string(j)+"_C"+to_string(i)+";\n";
                    }
                }
            }
            for(int i=0;i<row_size;i++){
                dot+="{ rank = same; F"+to_string(i)+";";
                for(int j=0;j<column_size;j++){
                    dot+="F"+to_string(i)+"_C"+to_string(j)+";";
                }
                dot+="}\n";
            }
        }
 
 
};
 
string OrderString(string word){
    sort(word.begin(), word.end());
    return word;
}
 
bool compare(vector<pair<int, string>> &vec,pair<int, string>& pa){
    for(int i =0;i<vec.size();i++){
        if(vec[i].first != pa.first){
            if(OrderString(vec[i].second) == OrderString(pa.second)){
                return true;
            }
        }
    }
    return false;
 
}
 
 
void Insert_pair(vector<pair<int, string>> &vec){
    const int size = 11;
    Matrix<int,size,size> A;
    for(int j =0;j<vec.size();j++){
        for(int i =0;i<vec.size();i++){
            A.Insert(1,vec[j].first,vec[i].first);
            if(vec[j].first != vec[i].first){
                if(OrderString(vec[j].second) == OrderString(vec[i].second)){
                    A.Insert(0,vec[j].first,vec[i].first);
                }
            }
        }
    }
 
    A.Print();
    A.generar_dot();
}
 
 
 
int main(){
    vector<pair<int, string>> vec;
    vec.push_back(make_pair(0,"words"));
    vec.push_back(make_pair(1,"cords"));
    vec.push_back(make_pair(2,"corps"));
    vec.push_back(make_pair(3,"coops"));
    vec.push_back(make_pair(4,"crops"));
    vec.push_back(make_pair(5,"drops"));
    vec.push_back(make_pair(6,"drips"));
    vec.push_back(make_pair(7,"grips"));
    vec.push_back(make_pair(8,"gripe"));
    vec.push_back(make_pair(9,"grape"));
    vec.push_back(make_pair(10,"graph"));
    Insert_pair(vec);
 
 
    return 0;
   
 
}
