#include<iostream>
using namespace std;
int suma(int a,int b){return a+b;}//calcula la suma de dos numeros
int resta(int a,int b){return suma(a,(-1*b));}//calcula la resta de dos numeros
int mayor(int a,int b){if(a>b)return a;return b;}//calcula el menor de dos numeros
int menor(int a,int b){return suma(a,b)-mayor(a,b);}//es el menor de dos numeros
int promedio(int a,int b){return suma(a,b)/2;}//es la semisuma de dos numeros
void basicas(int **A,int **B,int **C,int a,int b,char d,int i=0,int j=0){//reconoce las operaciones
  if(i!=a){
    int (*f)(int,int);
    if(d=='>')f=mayor;
    else if(d=='<')f=menor;
    else if(d=='+')f=suma;
    else if(d=='-')f=resta;
    else if(d=='p')f=promedio;
    *(*(C+i)+j)=(*f)(*(*(A+i)+j),*(*(B+i)+j));
    if((++j)==b){j=0;i++;}
    basicas(A,B,C,a,b,d,i,j);
  }
}
int multi(int **A,int **B,int **C,int a,int b,int i=0,int j=0,int k=0){//multi de matrices
  if(i!=a){
    if(k==0)*(*(C+i)+j)=0;
    if(k!=b)*(*(C+i)+j)+=(*(*(A+i)+k))*(*(*(B+(k++))+j));
    if(k==b){k=0;j++;}
    if(j==a){j=0;i++;}
    multi(A,B,C,a,b,i,j,k);
  }
}
void complejos(int **A,int **B,int **C,int a,int b,char d){//reconoce si es multiplicaciom
  if(d=='*'){multi(A,B,C,a,b);}
  else{basicas(A,B,C,a,b,d);}
}
void create(int **A,int a,int b,int i=0){//crea una matriz
	if(i!=a){
	  *(A+(i++))=new int[b];
	  create(A,a,b,i);
  }
}
void entrada(int **A,int a,int b,int i=0,int j=0){//entrada de datos de matriz
  if(i!=a){
    cin>>*(*(A+i)+j);
    if((++j)==b){j=0;i++;}
    entrada(A,a,b,i,j);
  }
}
void imprimir(int **A,int a,int b,int i=0,int j=0){//salida de datos de matriz
  if(i!=a){
    cout<<*(*(A+i)+j)<<" ";
    if((++j)==b){j=0;i++;cout<<endl;}
    imprimir(A,a,b,i,j);
  }
}
void borrar(int **A,int a,int i=0){//eliminar una matriz bidimensional
	if(i!=a){
		delete[]*(A+(i++));
		borrar(A,a,i);
	}
	else delete []A;
}
int main(){
	int a,b;
	cout<<" Ingrese las dimensiones de las matrices"<<endl;
	cin>>a>>b;
	int** A=new int*[a];
	int** B=new int*[b];
	int** C=new int*[a];
	create(A,a,b);
	create(B,b,a);
	create(C,a,a);
	cout<<"Ingrese la primera matriz"<<endl;
	entrada(A,a,b);
	cout<<"Ingrese la segunda matriz"<<endl;
	entrada(B,b,a);
	char d;
	cout<<"Ingrese la operacion a realizar entre matrices siendo:"<<endl;
	cout<<" < es la comparacion menor"<<endl;
	cout<<" > es la comparacion del mayor"<<endl;
	cout<<" p es el promedio"<<endl;
	cout<<" + es la suma de matrices"<<endl;
	cout<<" - es la resta de matrices"<<endl;
	cout<<" * es la multiplicacion de matrices"<<endl;
	cin>>d;
	if(a!=b and d!='*'){cout<<"las matrices no tienen las mismas dimensiones no se puede calcular lo pedido";return 0;}
	complejos(A,B,C,a,b,d);
	cout<<"el resultado de la operacion de matrices es"<<endl;
	if(d=='*')imprimir(C,a,a);
	else imprimir(C,a,b);
	borrar(A,a);
	borrar(B,b);
	borrar(C,a);
}
