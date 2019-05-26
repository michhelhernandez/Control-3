#include <iostream>
#include <string>
#include <stdio.h>

#include "Funciones.h"

using namespace std;

//pasa los numeros de la linea del txt a un arreglo de numeros
void LineaANum(char linea[30],int arreglo[9]){
    int c=0;
    string aux;
    for(int i=1;i<30;i++){ //parte del 2 lugar del arreglo que puede ser un numero o -
        if(linea[i]=='0' || linea[i]=='1' || linea[i]=='2' || linea[i]=='3' ||
           linea[i]=='4' || linea[i]=='5' || linea[i]=='6' || linea[i]=='7' ||
           linea[i]=='8' || linea[i]=='9'){
            if(linea[i-1]=='-'){
                aux = linea[i];
                arreglo[c]= stoi(aux)*-1; //deja los numeros en negativo
                c++;
            }
            else{
                aux = linea[i];
                arreglo[c]= stoi(aux);
                c++;
            } 
        }        
    }
}

//Crea la matriz del cuadrado magico
void ArregloMatriz(int arreglo[9],int matriz[3][3]){
    int cont = 0; //contador para el arreglo
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matriz[i][j]=arreglo[cont];
            cont ++;
        }
    }
}

//Devuelve 1 si es un cuadrado magico, 0 en caso contrario
int Magico(int matriz[3][3]){
    bool asignacion=false;
    int comprobacion=0 ; //0 si no son iguales, 1 si son iguales
    int sumaAux=0;
    int constante=0;
    
    //sumando filas
    for(int i=0;i<3;i++){
        sumaAux=0; //se reinicia la suma 
        for(int j=0;j<3;j++){
            sumaAux = sumaAux + matriz[i][j];
            
        }
        
        if(asignacion ==false){
            constante= sumaAux;
            asignacion =true;
        }
        else{
            if(sumaAux==constante){
                comprobacion=1;
            }else{
                comprobacion=0;
                break;
                return comprobacion;
            }
        
        }
        
    }
    
    //sumando columnas
    for(int i=0;i<3;i++){
        sumaAux=0; //se reinicia la suma 
        for(int j=0;j<3;j++){
            sumaAux = sumaAux + matriz[j][i]; 
            
        }
        
        if(sumaAux==constante){
            comprobacion=1;
        }
        else{
            comprobacion=0;
            break;
            return comprobacion;
        } 
    }
    
    
   //Diagonal Izquierda
    sumaAux=0;
    sumaAux = matriz[0][0] + matriz[1][1] + matriz[2][2];
    
    if(sumaAux==constante){
        comprobacion=1;
    }
    else{
        comprobacion=0;
        return comprobacion;
    } 
    
    //Diagonal Derecha
    sumaAux=0;
    sumaAux = matriz[2][0] + matriz[1][1] + matriz[0][2];
 
    if(sumaAux==constante){
        comprobacion=1;
    }
    else{
        comprobacion=0;
        return comprobacion;
    } 
    
    
   return comprobacion;
}
