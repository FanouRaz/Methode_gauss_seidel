#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;

const float EPSILON = pow(10,-6);
/*
    Factorisation de Cholesky d'une matrice A symétrique définie positive.
    ie décomposer A sous forme A = B*(B)t
    où B est une matrice triangulaire supérieure
*/

void afficher(vector<vector<float> > matrice); 
void lireData(int &n,vector<vector<float>> &A, vector <float> &b);
vector<float> remplirLigne(string ligne, int n);
void afficherVect(vector<float>tab);
void afficheEquation(vector<vector<float>> A,vector<float> B, int dim);
void gaussSeidel(vector<vector<float>> A,vector<float> b);
bool testResidu(float r[],int n);
void initialisationResidu(float r[],float x[],vector<vector<float>> A,vector<float>b,int n);

int main(){
    int n = 0;
    vector<vector<float>> A({});
    vector<float> b({});
    lireData(n,A,b);
    cout<<"Ce programme permet de résoudre un système d'equation "
    <<"sous forme d'équation matricielle Ax = B par la méthode de Gauss-Seidel. L'utilisateur inserera les matrices A et B dans le fichier data.txt et le programme"
    <<" affichera les solutions"<<endl;
    cout<<"_________________________________________________________________________________________________________________"<<endl<<endl;
    cout<<"Le système entré par l'utilisateur est:"<<endl;
    afficheEquation(A,b,n);
    gaussSeidel(A,b);
    return 0;
}


void lireData(int &n,vector<vector<float>> &A, vector <float> &b){
    fstream donnee;    
    string line;
    int taille(0);
    int tailleA=0;
    int tailleB=0;
    //ouverture du fichier en mode lecture
    donnee.open("data.txt", ios::in);                                
    if(!donnee){
        cout<<"Erreur lors du chargement des données. Veuillez placer le fichier data.txt dans le répertoire courant."<<endl;
        exit(-1);                                                                                       
    }
    
    while(getline(donnee,line)){
        if(taille==0)  n=stoi("0"+line);
        else if(tailleA < n){
            A.push_back(remplirLigne(line , n));
            tailleA++;
        }
        else{
            b.push_back(stof(line));
            tailleB++;
        }
        taille++;
    }

    donnee.close();
    if(tailleA!= n){
        cout<<"La dimension de la matrice A dans le fichier 'data.txt' n'est pas valide"<<endl;
        exit(-1);
    }
    if(tailleA != tailleB){
        cout<<"La dimension du vecteur B dans le fichier 'data.txt' n'est pas valide"<<endl;
        exit(-1);
        }
    }

//Construire les matrices A et b à partir des données recupérées dans le fichier data.txt 
vector<float> remplirLigne(string ligne, int n){
    vector <float> row;
    int i=0;
    int colonne=0;
    ligne+=" 0";
    int len =ligne.length();
    string valeurString="";
    while(i<len){
        if((ligne.at(i)>='0'&& ligne.at(i)<='9')||(ligne.at(i)=='.')||(ligne.at(i)=='+')||(ligne.at(i)=='-')){
            valeurString+=ligne.at(i);
        }
        else{
            if(valeurString.length()){
                row.push_back(stof(valeurString));
                colonne++;
            }
            valeurString="";
        }
            i++;
    }
    if(colonne != n){
        cout<<"La dimension de la matrice dans le fichier 'data.txt' n'est pas valide"<<endl;
        exit(-1);
    }
    return row;
}


void afficheEquation(vector<vector<float>> A,vector<float> B, int n){
	
	for(int i=0; i< n ; i++){
		for(int j=0 ; j < n ; j++){
		
			cout << setw(10)<< A[i][j] << " x" << j << "\t+";
		}
		cout << setw(10)<<"= \t" << B[i] <<setw(2) << endl << endl;
	}
		
}

void gaussSeidel(vector<vector<float>> A,vector<float> b){
    int n(A.size());
    float x[n]={1};
    float r[n]={0};
    float s(0);
    
    initialisationResidu(r,x,A,b,n);
    while(!testResidu(r,n)){
        for(int i(0);i<n;i++){
            for(int k=0;k<n;k++){
                s+=A[i][k]*x[k];
            }
            r[i] = b[i] - s;
            x[i] += r[i]/A[i][i];
            s=0;
        }
    }

    cout<<endl<<"Ainsi, les solutions de cette équation sont:"<<endl;

    for(int i(0);i<n;i++){
        cout<<"x"<<i<<" = "<<x[i]<<endl;
    }
}

void initialisationResidu(float r[],float x[],vector<vector<float>> A,vector<float>b,int n){
    float s(0);
    for(int i(0);i<n;i++){
        for(int k=0;k<n;k++){
            s+=A[i][k]*x[k];
        }
        r[i] = b[i] - s;
        s=0;
        }
}

bool testResidu(float r[],int n){
    float s(0);

    for(int i(0);i<n;i++){
        s += fabs(r[i]);
    }

    return s<EPSILON;
}

//Afficher une matrice n x n
void afficher(vector<vector<float>> matrice){
    int size = matrice.size();
    cout<<setw(10); 
    for(int i=0;i<size;i++){ 
        for(float ligne: matrice[i]){
            cout << ligne << setw(10);
        }
        cout<< endl;
    }
}

//Fonction pour afficher un vecteur colonne
void afficherVect(vector<float> tab){
    for(float elt : tab){
        cout<<elt<<endl;
    }
    cout<<endl;
}
