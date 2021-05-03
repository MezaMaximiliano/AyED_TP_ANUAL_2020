#include <iostream>
#include <string.h>
#include <fstream>
#include<stdlib.h>
#include <stdio.h>
#include<cstring>

using namespace std;

#define _UNALETRA 2
#define _NOMBRE 10 
#define _CANDIDATOS 25
#define _CANTBANCAS 13
#define _CANTLISTAS 7
#define _NOMBREAPELLIDO 40
#define _PISOBANCA 3
#define _NUMVOTOS 6000

typedef char str2[_UNALETRA];
typedef char str10[_NOMBRE];
typedef char str20[_NOMBREAPELLIDO];

struct tCand {
  str20 nombreApellido;
};

struct tVoto {
	int voto;
	str2 sexo;
	int edad;
};

typedef tVoto vVotosLista[_NUMVOTOS];
typedef tCand lCand[_CANDIDATOS];
typedef float bancas[_CANTBANCAS];

struct rLista {
  int numLista;
  str10 nombreLista;
  int cantVotos;
  float porcentaje;
  lCand candidatos;
  int hasta18;
  int hasta30;
  int hasta50;
  int mas50;
  bancas cocientesBancas;
  int bancasG;
  vVotosLista votos;
  int indiceVotos;
};

struct rGanador {
	str10 nombreLista;
	str20 nombre;
	int numLista;
	float cociente;
};

typedef rLista vListas[_CANTLISTAS];
typedef rGanador vGanadores[_CANTBANCAS];

struct rVotos {
  int totalVotos;
  int votosNulos;
  int votosBlanco;
  str2 sexo;
  int cantF;
  int cantM;
  int numVoto;
  int edad;
};

//--------------->ESTRUCTURAS TERCER ENTREGA<-----------------

struct datoPListas{
	int numLista;
	str10 nombreLista;
};

struct datoPVotos{
	int edad;
	str2 sexo;
	int numVoto;
};

struct pVotos{
	datoPVotos voto;
	pVotos *nodoSig;
};

struct pListas{
	datoPListas lista;
	pListas *nodoSig;
	pVotos *nodoSL;
};
//-------------------------------------------------------

void inicializarVotos(rVotos &);
void inicializarLista(rLista &);
void inicializarVecGanadores(vGanadores, int);
void inicializar(vListas, rVotos &);
void ordenarListasPorVotos (vListas);
void calcPorcentaje (vListas,rVotos &);
void calcCocientes (vListas l);
void grabarDatos (vListas,rVotos);//NUEVO
void mostrarDatos (vListas,rVotos &);
void cargarVotos (rVotos & , vListas, pListas *&);		//MODIFICADO TERCER ENTREGA
void procesarVoto(rVotos &, vListas);//MODIFICADO
void cargarListas(vListas);
void grabarVotos(vListas);//NUEVO
void grabarRangoEdad(vListas);//NUEVO
void mostrarRangoEdad(vListas);
void traerDeBancas(bancas, float &, int, int &, bool &);
void traerDeGanadores(vGanadores, float &, int, int &, bool &);
void pasar(vGanadores, int, int &, float, str10, str20, int, bool &);
void apareoInicial (vListas,int, int, int, vGanadores, int );
void apareoSecundario (vListas,int, vGanadores, int, vGanadores, int );
void apareoFinal (vListas,vGanadores,vGanadores, int, vGanadores, int );
void apareo(vListas,vGanadores);
void procesarGanadores(vListas, vGanadores);
void mostrarGanadores(vGanadores,int);
void grabarLista(vListas );
void grabarGanadores(vGanadores, int);
//----------->PROTOTIPOS FUNCIONES TERCER ENTREGA<---------------------------
void tercerEntrega(pListas *&, vListas);
void insertarOrd(pListas *&, datoPListas);
void procesarSubLista(rVotos,pListas *&);
void mostrarLista(pListas *);
pListas *buscar(pListas *, int);
void insertarOrdSL(pVotos *&, datoPVotos);



template <typename T,typename Q>
void fOrdenar (T vec,int , int (*criterio) (Q, Q));

template <typename T>
int criterioVotos(T,T);

template<typename TX>
int criterioNumLista(TX ,TX );

int main() {
  setlocale(LC_CTYPE, "Spanish");	
  int a=_CANTLISTAS;
  int b=_CANTBANCAS;
  rVotos votos;
  vListas listas;
  vGanadores ganadores;
  pListas *lista;
  lista=NULL;
  
  ifstream ar("Votos.txt");
  ifstream ar2("Candidatos.txt");
  if ((ar.fail())or(ar2.fail())){
     if (ar.fail()){
  		if((ar.fail())and(ar2.fail())){
  				cout<<"No se encontraron los archivos Votos.txt y Candidatos.txt\nFIN DEL PROGRAMA\n";
  				exit(0);
  	   	 } else {
  	   		 	cout<<"No se encontro el archivo Votos.txt\nFIN DEL PROGRAMA\n";	
  	     }
  				exit(0);
  	  }else if(ar2.fail()){
  	    		cout<<"No se encontro el archivo Candidatos.txt\nFIN DEL PROGRAMA\n";	
  	    		exit(0);
  	 }
  }else{
  
 	 cout<<" ___________ "<<endl;
  	 cout<<"|RESULTADOS |"<<endl;
	 cout<<"|___________|_________________________________________________________________________________________________________________________________________________________\n";
  	 inicializar(listas,votos);									
  	 inicializarVecGanadores(ganadores,b);
  	 cargarListas(listas);
	 tercerEntrega(lista,listas);						
  	 cargarVotos(votos,listas,lista);		//MODIFICADO TERCER ENTREGA									
  	 grabarVotos(listas);//NUEVO
  	 fOrdenar<vListas,rLista>(listas,a,criterioVotos);			
  	 mostrarDatos(listas,votos);									
  	 grabarDatos (listas,votos);//NUEVO
  	 procesarGanadores(listas,ganadores);						
   	 fOrdenar<vGanadores,rGanador>(ganadores,b,criterioNumLista);	
  	 fOrdenar<vListas,rLista>(listas,a,criterioNumLista);			
  	 cout<<"\n\n _______________________ \n";
  	 cout<<"|VOTOS POR RANGO DE EDAD|\n|_______________________|____________________________________________________________________ \n";
  	 grabarRangoEdad(listas);
  	 mostrarRangoEdad(listas);									
  	 cout<<"\n\n _________ \n";
  	 cout<<"|GANADORES|\n";
  	 cout<<"|_________|____________________________________________________________________________\n";
  	 mostrarGanadores(ganadores,b);									// Ver linea 153
  }
  
  grabarLista(listas);
  grabarGanadores(ganadores,b);
  mostrarLista(lista);
  
  ar.close();
  ar2.close();
  
  system("pause");
  return 0;
}

void grabarVotos(vListas v){//NUEVO
	ofstream fs("SalidaTPANUAL_votos.txt");
	fs<<"N° LISTA;SEXO;EDAD;\n";
	for (int i=0;i<_CANTLISTAS;i++){
		if (i<5){
			for (int j=0;j<v[i].indiceVotos;j++){
				fs<<v[i].votos[j].voto<<";"<<v[i].votos[j].sexo<<";"<<v[i].votos[j].edad<<";\n";
			}
		}
		else{
			if(i==5){
				fs<<"\n";
				for (int j=0;j<(v[i].indiceVotos-1);j++){
					fs<<v[i].votos[j].voto<<";"<<v[i].votos[j].sexo<<";"<<v[i].votos[j].edad<<";\n";
				}
			}
			else{
				fs<<"\n";
				for (int j=0;j<(v[i].indiceVotos);j++){
					fs<<v[i].votos[j].voto<<";"<<v[i].votos[j].sexo<<";"<<v[i].votos[j].edad<<";\n";
				}
			}
		}
	}
	fs.close();
}

void inicializarVecGanadores(vGanadores ganadores, int b){
	for (int i=0;i<b;i++){
		ganadores[i].numLista=0;
		ganadores[i].cociente=0.00;
		strcpy(ganadores[i].nombre,"");
		strcpy(ganadores[i].nombreLista,"");
	}
	
}

void mostrarGanadores(vGanadores a,int b){
	
	printf("|%-10s|%-10s|%-40s|%-17s|\n","NOMBRE DE LISTA","N° DE LISTA","NOMBRE DE CANDIDATO","COCIENTE DE BANCA");
	cout<<"|---------------|-----------|----------------------------------------|-----------------|\n";
	for (int i=0;i<b;i++){
		printf("|%-15s|%-11i|%-40s|%-17.2f|\n",a[i].nombreLista,a[i].numLista,a[i].nombre,a[i].cociente);
		cout<<"|---------------|-----------|----------------------------------------|-----------------|\n";
	}
	cout<<"|_______________|___________|________________________________________|_________________|\n\n";
	
}

void procesarGanadores(vListas listas, vGanadores ganadores){
	apareo(listas,ganadores);
/*	int k=0;
  for (int i=0;i<_CANTBANCAS-1;i++){
  		for (int j=0;((j<_CANTLISTAS)and (k<_CANTBANCAS));j++){
  			if ((listas[j].cocientesBancas[i]!=0)){
  				ganadores[k].numLista=listas[j].numLista;
  				strcpy(ganadores[k].nombre,listas[j].candidatos[i].nombreApellido);
  				strcpy(ganadores[k].nombreLista,listas[j].nombreLista);
  				ganadores[k].cociente=listas[j].cocientesBancas[i];
  				k++;
		   	}
 			
	 	}

  }
*/	
}

void traerDeBancas(bancas v, float & r, int cant, int & ptro, bool & fin) {
   if (ptro<cant) {
   	r = v[ptro];
   	ptro++;
   	fin = false ;
   } else fin = true;
}

void traerDeGanadores(vGanadores v, float & r, int cant, int & ptro, bool & fin) {
   if (ptro<cant) {
   	r = v[ptro].cociente;
   	ptro++;
   	fin = false ;
   } else fin = true;
}

void pasar(vGanadores v, int cant, int & ptro, float r, str10 nombreLista, str20 candidato, int numLista, bool & fin) {
	if (ptro<cant) {
		strcpy(v[ptro].nombreLista,nombreLista);
		v[ptro].numLista = numLista;
		v[ptro].cociente = r;
		strcpy(v[ptro].nombre,candidato);
		ptro ++;
		fin=false;
	}
	else{
		fin=true;
	}
}

void apareo(vListas vL,vGanadores ganadores){
	vGanadores aux1;
	vGanadores aux2;
	vGanadores aux3;
	inicializarVecGanadores(aux1,_CANTBANCAS);
	inicializarVecGanadores(aux2,_CANTBANCAS);
	int cantBancas=_CANTBANCAS;
	apareoInicial(vL,0,3,_CANDIDATOS,aux1,cantBancas);
	apareoInicial(vL,2,1,_CANDIDATOS,aux2,cantBancas);
	apareoSecundario(vL,4,aux1,_CANDIDATOS,aux3,cantBancas);
	apareoFinal(vL,aux2,aux3,_CANDIDATOS,ganadores,cantBancas);
}

void apareoInicial (vListas vL,int indice1, int indice2, int c, vGanadores v3, int c3) {
	int i1=0;
	int i2=0;
	int i3=0;
	bancas v1;
	bancas v2;
	for (int i=0;i<c3;i++){
		v1[i]=vL[indice1].cocientesBancas[i];
		v2[i]=vL[indice2].cocientesBancas[i];
	}
	int iCandidatos1=0;
	int iCandidatos2=0;
	float r1=0;
	float r2=0;
	bool fin1, fin2;
	bool fin3=false;
	traerDeBancas(v1, r1, c, i1, fin1) ;
	traerDeBancas(v2, r2, c, i2, fin2) ;
	while(!fin3){
		if (r1>=r2) {
			pasar(v3,c3,i3,r1,vL[indice1].nombreLista,vL[indice1].candidatos[iCandidatos1].nombreApellido,vL[indice1].numLista,fin3) ;
			iCandidatos1++;
			traerDeBancas(v1, r1, c, i1, fin1) ;
		} 
		else {
			pasar(v3,c3,i3,r2,vL[indice2].nombreLista,vL[indice2].candidatos[iCandidatos2].nombreApellido,vL[indice2].numLista,fin3) ;
			iCandidatos2++;
			traerDeBancas(v2, r2, c, i2, fin2) ;
		}
  	}	
}

void apareoFinal (vListas vL,vGanadores v1,vGanadores v2, int c, vGanadores v3, int c3) {
	int i1=0;
	int i2=0;
	int i3=0;
	float r1=0;
	float r2=0;
	bool fin1, fin2;
	bool fin3=false;
	traerDeGanadores(v1, r1, c, i1, fin1) ;
	traerDeGanadores(v2, r2, c, i2, fin2) ;
	while(!fin3){
		if (r1>=r2) {
		   pasar(v3,c3,i3,r1,v1[i1-1].nombreLista,v1[i1-1].nombre,v1[i1-1].numLista,fin3) ;
	       traerDeGanadores(v1, r1, c, i1, fin1) ;
		} 
		else {
			pasar(v3,c3,i3,r2,v2[i2-1].nombreLista,v2[i2-1].nombre,v2[i2-1].numLista,fin3) ;
			traerDeGanadores(v2, r2, c, i2, fin2) ;
		}
  	}
}

void apareoSecundario (vListas vL,int indice1,vGanadores v2, int c, vGanadores v3, int c3) {
	int i1=0;
	int i2=0;
	int i3=0;
	bancas v1;
	for (int i=0;i<c3;i++){
		v1[i]=vL[indice1].cocientesBancas[i];
	}
	int iCandidatos1=0;
	float r1=0;
	float r2=0;
	bool fin1, fin2;
	bool fin3=false;
	traerDeBancas(v1, r1, c, i1, fin1) ;
	traerDeGanadores(v2, r2, c, i2, fin2) ;
	while(!fin3){
		if (r1>=r2) {
		   pasar(v3,c3,i3,r1,vL[indice1].nombreLista,vL[indice1].candidatos[iCandidatos1].nombreApellido,vL[indice1].numLista,fin3) ;
		   iCandidatos1++;
	       traerDeBancas(v1, r1, c, i1, fin1) ;
		} 
		else {
			pasar(v3,c3,i3,r2,v2[i2-1].nombreLista,v2[i2-1].nombre,v2[i2-1].numLista,fin3) ;
			traerDeGanadores(v2, r2, c, i2, fin2) ;
		}
  	} 
}

void grabarRangoEdad(vListas a){//NUEVO
	ofstream fs("SalidaTPANUAL_rangodeedades.txt");
	fs<<"NOMBRE DE LISTA;N° DE LISTA;MENORES DE 18;ENTRE 18 y 30;ENTRE 31 y 50;MAYORES DE 50;\n";
	for (int i=0;i<_CANTLISTAS;i++){
		fs<<a[i].nombreLista<<";"<<a[i].numLista<<";"<<a[i].hasta18<<";"<<a[i].hasta30<<";"<<a[i].hasta50<<";"<<a[i].mas50<<";\n";
	}
}

void mostrarRangoEdad(vListas a){
	printf("|%-23s|%-12s|%-12s|%-12s|%-12s|%-12s|\n","NOMBRE DE LISTA","N° DE LISTA","MENORES DE 18","ENTRE 18 y 30","ENTRE 31 y 50","MAYORES DE 50");
	cout<<"|-----------------------|------------|-------------|-------------|-------------|-------------|\n";
	for (int i=6;i>=2;i--){
		printf("|%-23s|      %i     |%-13i|%-13i|%-13i|%-13i|\n",a[i].nombreLista,a[i].numLista,a[i].hasta18,a[i].hasta30,a[i].hasta50,a[i].mas50);
		cout<<"|-----------------------|------------|-------------|-------------|-------------|-------------|\n";
	}
	cout<<"|_______________________|____________|_____________|_____________|_____________|_____________|\n";
}


void cargarVotos(rVotos &a, vListas b, pListas *&lista){
	
	string cadena;
	int ultimo=0,primero=0;
	ifstream ar("Votos.txt");
	while (!ar.eof()){
	
		getline(ar,cadena);
	
		ultimo=cadena.find(";",primero);
		a.numVoto=atoi(cadena.substr(primero,ultimo-primero).c_str());
		primero=ultimo+1;
		
		ultimo=cadena.find(";",primero);
		strcpy(a.sexo,cadena.substr(primero,ultimo-primero).c_str());
		primero=ultimo+1;
		
		ultimo=cadena.find(";",primero);
		a.edad=atoi(cadena.substr(primero,ultimo-primero).c_str());
		primero=ultimo+1;	
		
		procesarVoto(a,b);
		procesarSubLista(a,lista);  //TERCER ENTREGA
	}
	
	a.totalVotos=a.totalVotos-a.votosNulos-a.votosBlanco;
	
}

void procesarVoto(rVotos &a, vListas b){//MODIFICADO
	
	a.totalVotos++;
	if (a.numVoto==0){
		a.votosBlanco++;
		//NUEVO
		b[5].votos[b[5].indiceVotos].voto=a.numVoto;
		b[5].votos[b[5].indiceVotos].edad=a.edad;
		strcpy(b[5].votos[b[5].indiceVotos].sexo,a.sexo);
		b[5].indiceVotos++;
		
	}else	if (a.numVoto==1){
		b[0].cantVotos++;
		//NUEVO
		b[0].votos[b[0].indiceVotos].voto=a.numVoto;
		b[0].votos[b[0].indiceVotos].edad=a.edad;
		strcpy(b[0].votos[b[0].indiceVotos].sexo,a.sexo);
		b[0].indiceVotos++;
		
		if (a.edad<=18){
			
			b[0].hasta18++;
		}else if (a.edad>18 and a.edad<=30 ){
			b[0].hasta30++;
		}else if(a.edad>30 and a.edad<=50){
			b[0].hasta50++;
		}else if (a.edad>50){
			b[0].mas50++;
		}
	}else	if (a.numVoto==2){
		b[1].cantVotos++;
		//NUEVO
		b[1].votos[b[1].indiceVotos].voto=a.numVoto;
		b[1].votos[b[1].indiceVotos].edad=a.edad;
		strcpy(b[1].votos[b[1].indiceVotos].sexo,a.sexo);
		b[1].indiceVotos++;
		
		if (a.edad<=18){
			
			b[1].hasta18++;
		}else if (a.edad>18 and a.edad<=30 ){
			b[1].hasta30++;
		}else if(a.edad>30 and a.edad<=50){
			b[1].hasta50++;
		}else if (a.edad>50){
			b[1].mas50++;
		}
	}else	if (a.numVoto==3){
		b[2].cantVotos++;
		//NUEVO
		b[2].votos[b[2].indiceVotos].voto=a.numVoto;
		b[2].votos[b[2].indiceVotos].edad=a.edad;
		strcpy(b[2].votos[b[2].indiceVotos].sexo,a.sexo);
		b[2].indiceVotos++;
		
		if (a.edad<=18){
			
			b[2].hasta18++;
		}else if (a.edad>18 and a.edad<=30 ){
			b[2].hasta30++;
		}else if(a.edad>30 and a.edad<=50){
			b[2].hasta50++;
		}else if (a.edad>50){
			b[2].mas50++;
		}
	}else	if (a.numVoto==4){
		b[3].cantVotos++;
		//NUEVO
		b[3].votos[b[3].indiceVotos].voto=a.numVoto;
		b[3].votos[b[3].indiceVotos].edad=a.edad;
		strcpy(b[3].votos[b[3].indiceVotos].sexo,a.sexo);
		b[3].indiceVotos++;
		
		if (a.edad<=18){
			
			b[3].hasta18++;
		}else if (a.edad>18 and a.edad<=30 ){
			b[3].hasta30++;
		}else if(a.edad>30 and a.edad<=50){
			b[3].hasta50++;
		}else if (a.edad>50){
			b[3].mas50++;
		}
	}else	if (a.numVoto==5){
		b[4].cantVotos++;
		//NUEVO
		b[4].votos[b[4].indiceVotos].voto=a.numVoto;
		b[4].votos[b[4].indiceVotos].edad=a.edad;
		strcpy(b[4].votos[b[4].indiceVotos].sexo,a.sexo);
		b[4].indiceVotos++;
		
		if (a.edad<=18){
			
			b[4].hasta18++;
		}else if (a.edad>18 and a.edad<=30 ){
			b[4].hasta30++;
		}else if(a.edad>30 and a.edad<=50){
			b[4].hasta50++;
		}else if (a.edad>50){
			b[4].mas50++;
		}
	}else	if (a.numVoto>=6){
		a.votosNulos++;
		//NUEVO
		b[6].votos[b[6].indiceVotos].voto=a.numVoto;
		b[6].votos[b[6].indiceVotos].edad=a.edad;
		strcpy(b[6].votos[b[6].indiceVotos].sexo,a.sexo);
		b[6].indiceVotos++;
	
	}
	
	
}

void cargarListas(vListas a){
	
	string cadena;
	str20 candidato;
	int ultimo=0,primero=0;
	int nLista=0;
	int nCand1=0,nCand2=0,nCand3=0,nCand4=0,nCand5=0;
	strcpy(a[0].nombreLista,"AZUL");
	a[0].numLista=1;
	strcpy(a[1].nombreLista,"ROSA");
	a[1].numLista=2;
	strcpy(a[2].nombreLista,"VERDE");
	a[2].numLista=3;
	strcpy(a[3].nombreLista,"BLANCO");
	a[3].numLista=4;
	strcpy(a[4].nombreLista,"NEGRO");
	a[4].numLista=5;
	ifstream ar2("Candidatos.txt");
	
	while (!ar2.eof()){
	
		getline(ar2,cadena);
		
		ultimo=cadena.find(";",primero);
		nLista=atoi(cadena.substr(primero,ultimo-primero).c_str());
		primero=ultimo+1;
		
		ultimo=cadena.find(";",primero);
		strcpy(candidato,cadena.substr(primero,ultimo-primero).c_str());
		primero=ultimo+1;
	
		if (nLista==1){
			strcpy(a[nLista-1].candidatos[nCand1].nombreApellido,candidato);
			nCand1++;
		}else if (nLista==2){
			strcpy(a[nLista-1].candidatos[nCand2].nombreApellido,candidato);
			nCand2++;
		}else if (nLista==3){
			strcpy(a[nLista-1].candidatos[nCand3].nombreApellido,candidato);
			nCand3++;
		}else	if (nLista==4){
			strcpy(a[nLista-1].candidatos[nCand4].nombreApellido,candidato);
			nCand4++;
		}else	if (nLista==5){
			strcpy(a[nLista-1].candidatos[nCand5].nombreApellido,candidato);
			nCand5++;
		}			
				
	}
	
	
	
}

void inicializar(vListas vec, rVotos & votos){
  for (int i=0;i<_CANTLISTAS;i++){
  	inicializarLista(vec[i]);
  }
  inicializarVotos(votos);
}

void inicializarVotos(rVotos & reg){
  reg.totalVotos=0;
  reg.votosBlanco=0;
  reg.votosNulos=0;
  reg.numVoto=0;
  strcpy(reg.sexo,"");
}

void inicializarLista(rLista & l){
	l.numLista=0;
	l.cantVotos=0;
	l.porcentaje=0;
	l.hasta18=0;
	l.hasta30=0;
	l.hasta50=0;
	l.mas50=0;
	l.bancasG=0;
	l.indiceVotos=0;
	strcpy(l.nombreLista,"");
	for(int j=0;j<_CANDIDATOS;j++){
    	strcpy(l.candidatos[j].nombreApellido,"");
	}
	for(int j=0;j<_CANTBANCAS;j++){
    	l.cocientesBancas[j]=0;
	}
	for(int j=0;j<_NUMVOTOS;j++){
		l.votos[j].edad=0;
		strcpy(l.votos[j].sexo,"");
		l.votos[j].voto=0;
	}
}


template <typename T,typename Q>
void fOrdenar (T vec,int a, int (*criterio) (Q, Q)){
	Q varAux;

	int i, j;
		
	for (i=0; i<a;i++){
		
		for (j=0;j<a-1;j++){ 
			
			if ((criterio(vec[j],vec[j+1])==1)){  
			
				varAux=vec[j];	
				vec[j]=vec[j+1];	
				vec[j+1]=varAux;	
				
			}
		}
			
			
	}
}

template<typename TX>
int criterioNumLista(TX a, TX b){
	int r=0;
	
	if (a.numLista>b.numLista){
		r=1;
		
	}else if(a.numLista<b.numLista){
		r=-1;
	}
	return r;
	

}

template <typename T>
int criterioVotos(T a, T b){
	int r=0;
	if (a.cantVotos<b.cantVotos){
		r=1;
	}else if (a.cantVotos>b.cantVotos){
		r=-1;
	}
	return r;	
	}

void grabarDatos (vListas vec, rVotos reg){//NUEVO
	ofstream fs("SalidaTPANUAL_datos.txt");
	fs<<"LISTAS;N° LISTA;Cant. Votos;% votos validos;1°Banca;2°Banca;3°Banca;4°Banca;5°Banca;6°Banca;7°Banca;8°Banca;9°Banca;10°Banca;11°Banca;12°Banca;13°Banca;\n";
	for (int i=0;i<_CANTLISTAS;i++){
		fs<<vec[i].nombreLista<<";"<<vec[i].numLista<<";"<<vec[i].cantVotos<<";"<<vec[i].porcentaje<<";";
		for(int j=0;j<_CANTBANCAS;j++){
			fs<<vec[i].cocientesBancas[j]<<";";
		}
		fs<<"\n";
	}
	fs<<"\nVoto Blanco:;"<<reg.votosBlanco<<";\n";
	fs<<"Voto nulo:;"<<reg.votosNulos<<";\n";
	fs.close();
}

void mostrarDatos (vListas vec,rVotos &reg){

	printf("|%-11s|%-7s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n","LISTAS","N° LISTA","Cant. Votos","% votos validos","1°Banca",
	"2°Banca","3°Banca","4°Banca","5°Banca","6°Banca","7°Banca","8°Banca","9°Banca","10°Banca","11°Banca","12°Banca","13°Banca");
	calcPorcentaje(vec,reg);
	calcCocientes(vec);
	cout<<"|-----------|--------|-----------|---------------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|\n";
		                   
	for(int i=0;i<5;i++){
		printf("|%-11s|%-8i|%-11i|%-15.2lf|",vec[i].nombreLista,vec[i].numLista,vec[i].cantVotos,vec[i].porcentaje);
		for(int j=0;j<5;j++){
			printf("%-8.2f|",vec[i].cocientesBancas[j]);
		}
		printf("\n");
	cout<<"|-----------|--------|-----------|---------------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|\n";
	}

	cout<<"|___________+________+___________+_______________+________+________+________+________+________+________+________+________+________+________+________+________+________|\n";
	printf("|%10s|%8i|\n","Voto Blanco",reg.votosBlanco);
	cout<<"|-----------|--------|\n";
	printf("|%-11s|%8i|\n","Voto nulo",reg.votosNulos);
	cout<<"|___________+________|\n";
	cout<<"\n\nTOTAL DE VOTOS VALIDOS: "<<reg.totalVotos<<endl<<endl;
	
}

void calcPorcentaje (vListas l,rVotos &votos){
	for (int i=0;i<_CANTLISTAS;i++){
		l[i].porcentaje=(l[i].cantVotos*100)*1.00/(votos.totalVotos*1.00);
	}
}

void calcCocientes (vListas l){
	for (int i=0;i<_CANTLISTAS;i++){
		if (l[i].porcentaje>=_PISOBANCA){
			for (int j=0;j<_CANTBANCAS;j++){
				l[i].cocientesBancas[j]=(l[i].cantVotos*1.00)/((j+1)*1.00);
			}
		}
	}
}

void grabarLista(vListas a){
	
	FILE *fLista;
	fLista=fopen("Listas.dat","rb+");
	for (int nLista=0;nLista<_CANTLISTAS;nLista++){
	
		for (int numCand=0;numCand<_CANDIDATOS;numCand++){
		
			if (fLista==NULL){
					fLista=fopen("Listas.dat","wb+");
					fwrite(&a[nLista].numLista,sizeof(int),1,fLista);
					fwrite(&a[nLista].nombreLista,sizeof(str10),1,fLista);
					fwrite(&a[nLista].candidatos[numCand].nombreApellido,sizeof(str20),1,fLista);
				
				}else{
					fwrite(&a[nLista].numLista,sizeof(int),1,fLista);
					fwrite(&a[nLista].nombreLista,sizeof(str10),1,fLista);
					fwrite(&a[nLista].candidatos[numCand].nombreApellido,sizeof(str20),1,fLista);
				
			}
		
		}
	}
	fseek(fLista ,0, SEEK_SET );
	fclose(fLista);
}


void grabarGanadores(vGanadores a, int b){
	FILE *fGanador;
	fGanador=fopen("Ganadores.dat","rb+");
	for (int i=0;i<b;i++){
		if (fGanador==NULL){
			fGanador=fopen("Ganadores.dat","wb+");
			fwrite(&a[i],sizeof(vGanadores),1,fGanador);
		
		}else{
			fwrite(&a[i],sizeof(vGanadores),1,fGanador);
		}
		
	}
	
	fseek(fGanador,0,SEEK_SET);
	fclose(fGanador);
	
}


//--------------------->FUNCIONES DE TERCER ENTREGA<-------------------------------------------

void tercerEntrega(pListas *&lista, vListas vecListas){
	datoPListas aux;
	for (int i=0;i<5;i++){
		aux.numLista=vecListas[i].numLista;
		strcpy(aux.nombreLista,vecListas[i].nombreLista);
		insertarOrd(lista,aux);
	}
	
	
}

void insertarOrd(pListas *&lista, datoPListas n){
	
	pListas *nuevo_nodo=new pListas ();
	pListas *aux1,*aux2;
	nuevo_nodo->lista=n;
	aux1=lista;
	
	while ((aux1!=NULL)and (aux1->lista.numLista<n.numLista)){
		aux2 = aux1;
		aux1=aux1->nodoSig;
	}
	if (lista==aux1){
		lista=nuevo_nodo;
	}else{
		aux2->nodoSig=nuevo_nodo;
	}
	nuevo_nodo->nodoSig=aux1;
}

void mostrarLista(pListas *lista){

	pListas *aux;
	pVotos *sub;
	sub=NULL;
	aux=lista;
	int cantM;
	int cantF;
	while (aux!=NULL){
	
		if (aux->nodoSL==NULL){
			aux=aux->nodoSig;
		}else{
		
		
			cantM=0;
			cantF=0;
			cout<<"\nNUMERO DE LISTA: "<<aux->lista.numLista<<"		"<<"NOMBRE DE LISTA: "<<aux->lista.nombreLista<<endl;
			cout<<"		  --->VOTOS<---"<<endl;
			sub=aux->nodoSL;
			cout<<"Edad				Sexo		Numero de voto"<<endl<<endl;
			while(sub!=NULL){
				cout<<sub->voto.edad<<" 			        "<<sub->voto.sexo<<"		"<<sub->voto.numVoto<<endl;
			
				if ((strcmp(sub->voto.sexo,"F"))==0)
					cantF++;
				else{
					cantM++;
				}
			sub=sub->nodoSig;
			}
			cout<<"\nCANTIDAD VOTO MASCULINO: "<<cantM<<endl;
			cout<<"CANTIDAD VOTO FEMENINO: "<<cantF<<endl;
			aux=aux->nodoSig;
			cout<<"\n";
		}
	}
}

void procesarSubLista(rVotos a,pListas *&lista){
	
	datoPVotos aux;
	pVotos *sub;
	pListas *nodoAux;
	nodoAux=NULL;
	sub=NULL;
	
	aux.edad=a.edad;
	aux.numVoto=a.numVoto;
	strcpy(aux.sexo,a.sexo);
	if ((aux.numVoto>=1)and(aux.numVoto<=5)){
		nodoAux=buscar(lista,aux.numVoto);
		insertarOrdSL(nodoAux->nodoSL,aux);
	}
}

void insertarOrdSL(pVotos *&sub, datoPVotos n){
	
	pVotos *nuevo_nodo=new pVotos ();
	pVotos *aux1,*aux2;
	nuevo_nodo->voto=n;
	aux1=sub;
	
	while ((aux1!=NULL)and (aux1->voto.edad<n.edad)){
		aux2 = aux1;
		aux1=aux1->nodoSig;
	
	}
	if (sub==aux1){
		sub=nuevo_nodo;
	}else{
		aux2->nodoSig=nuevo_nodo;
	}
	nuevo_nodo->nodoSig=aux1;
}

pListas *buscar(pListas *lista, int numVoto){
	pListas *aux;
	aux=lista;
	
	while ((aux!=NULL)){	
	
		if (aux->lista.numLista==numVoto){
			
			return aux;
			
		}
		aux=aux->nodoSig;
	}

	return NULL;
	
}





