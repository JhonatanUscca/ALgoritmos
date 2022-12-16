#include<iostream>
#include<list>
#include<fstream>


using namespace std;

int intent = 0;
template<class Obj, int (*fun)(string, int) , int size = 11>
class Hash{
    private:
       list<Obj> table[size];
    public:
	    Hash(){};  
		
	    void I_encadenamiento(string key, Obj obj){
	        int position =fun(key,size);
	        cout<<"Lugar de insercion : "<<position<<endl; 
	        table[position].push_back(obj);
	    }
		
		void I_sondeoL(string key, Obj obj){
			bool occupied = false;
			while(occupied == false){
				int position= fun(key, size);
				if(table[position].empty()== true){
					occupied = true;
					cout<<"Lugar de insercion : "<<position<<endl; 
					table[position].push_back(obj);
				} else {
					intent++;
				}

			}

		}
	    void Print(){
	    	typedef typename list<Obj>::iterator ITERADOR;
	      	for (int  i = 0; i < size ; i++){
	        	ITERADOR iter = table[i].begin();
	         	cout<<"["<<i<<"]" ;
	         	for(;iter!=table[i].end();++iter)
	           		cout<<*iter<<"-->";
	         	cout<<endl;
			}
	    }

	    void generar_dot(){
			string dot="digraph structs {\nrankdir = LR;\nnode[shape=record];\nhashTable[label=\"<f0>0|<f1>1|<f2>2|<f3>3|<f4>4|<f5>5|<f6>6|<f7>7|<f8>8|<f9>9|<f10>10\"];\n";
			record(dot);
			dot+="\n}";
			ofstream fs("Hash.dot");
	    	fs<<dot<<endl;
	    	fs.close();
	    	string comando = "dot -Tjpeg Hash.dot  -o Hash.png";
	    	system(comando.c_str());
		}
		void record(string &dot){
			typedef typename list<Obj>::iterator ITERADOR;
			for (int  i = 0; i < size ; i++){
	        	ITERADOR iter = table[i].begin();
	         	if(*iter){
		         	dot+="hashTable:f"+to_string(i)+" -> ";
		         	int aux=0;
		         	for(;iter!=table[i].end();++iter){
						if(aux>0){
							--iter;
							dot += to_string(*iter) + " -> ";
							++iter;
						}
						dot+= to_string(*iter)+";\n";
						aux++;
		           }
		        }
			}
		}
};



int Funcion1(string key, int size){
	char *ASHII = (char*)key.c_str();
    int cont = 0;
    while(*ASHII){
      cont+=*ASHII;
      ASHII++;
    }
    return cont%size;
    
}


int Funcion2(string key, int size){
    int sizeKey = key.size();
    return  (sizeKey+intent)%size;

} 



void print(){
	string comando = "Hash.png";
	system(comando.c_str());
}


int main(){
	
	Hash<int,Funcion1>  A;

	cout << "Sondeo Lineal:" << endl;

	A.I_encadenamiento("Rodrigo",28);
	A.I_encadenamiento("Luis",23);
	A.I_encadenamiento("Luis",45);
	A.I_encadenamiento("Luis",33);
	A.I_encadenamiento("Roberto",34);
	A.I_encadenamiento("Esteban",22);
	A.I_encadenamiento("Elias",44);
	A.Print();
   	A.generar_dot();
	print();


   	return 0;
}
