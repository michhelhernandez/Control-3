#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include </usr/include/mpi/mpi.h>

#include "Funciones.h"

using namespace std;

int main(int argc, char** argv) {
    FILE *archivo,*cuadrado;
    
    
    string ArgumentoUno = argv[0];           // ./programa
    string ArgumentoF=argv[1];               // -f
    const char *ArchivoEntrada = argv[2];    // direccion del archivo con todas las matrices
    string ArgumentoO=argv[3];               // -o
    const char *ArchivoSalida = argv[4];     // direccion del archivo con los cuadrados magicos 
        
    
 if((ArgumentoF == "-f") && (ArgumentoO=="-o") ){   
        archivo = fopen(ArchivoEntrada,"r");//abre archivo para lectura, el fichero debe existir.
        if(archivo == NULL)
        {
            printf("Error al abrir archivo\n");
            return 1; //si hay error se cierra el programa.
        }
        
        cuadrado = fopen(ArchivoSalida,"a");//abre archivo para escritura al final del contenido, si no existe se crea.
        if(cuadrado == NULL)
        {
            printf("Error al abrir archivo\n");
            return 1; //si hay error se cierra el programa.
        }
        
       
        char linea[30];    
        int arregloNum[9];
        int resultado;
        int matriz[3][3]={ {0,0,0},  {0,0,0}, {0,0,0} };    
        int mi_rango; /* rango del proceso    */
        int p; /* numero de procesos   */
        int tag = 0; /* etiqueta del mensaje */
        
        
        /* devuelve estado al recibir*/
        MPI_Status estado; 

        /* Comienza las llamadas a MPI */
        MPI_Init(&argc, &argv);

        /* Averiguamos el rango de nuestro proceso */
        MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

        /* Averiguamos el número de procesos que estan ejecutando nuestro porgrama */
        MPI_Comm_size(MPI_COMM_WORLD, &p);


        if(mi_rango!=0)
        {
            /**
            si  nodo es diferente de 0:
                recive la linea
                transforma la linea en arreglo
                transforma arreglo en matriz
                comprueba si es cuadrado magico
                si el resultado es un cuadrado magico (1) guarda la linea en el txt
            */

            /*RECV*/
            MPI_Recv(linea, 30, MPI_CHAR, 0,tag, MPI_COMM_WORLD, &estado);//el nodo actual recive la linea desde el nodo 0
            //cout<<"recibido desde el nodo 0: "<<linea<<endl;
                
            LineaANum(linea,arregloNum);//transforma la linea en arreglo de int
            ArregloMatriz(arregloNum,matriz);//transforma arreglo en matriz
            resultado=Magico(matriz);//comprueba si la matriz es cuadrado magico
            
            
            if(resultado == 1){   
                //cout<<"El nodo "<<mi_rango<<" ha determinado que la matriz es cuadrado magico."<<endl;    
                fputs(linea,cuadrado);
            }
           
        }
        
        
        
        else //mi_rango=0
        {  
        /**
        si es nodo cero: 
        
            while para recorrer el archivo
            envia la linea a un nodo 
        */
            //int cont=1;
            while( !feof(archivo) ){ //feof devuelve 0 si se llega al final
                for(int i=1;i<=(p-1);i++){
                    fgets(linea,30,archivo);//se obtiene la linea desde el archivo origen
                   
                    if(strcmp(linea,"\n"))
                    {
                        /*SEND*/
                        MPI_Send(linea, 30, MPI_CHAR,i, tag, MPI_COMM_WORLD);//el nodo 0 envia la linea a un nodo disponible 
                        //cout<<cont<<")  P = "<<i<<"  "<<linea<<endl;
                        //cont++;
                    }
                }
            }
        }
        
        MPI_Finalize();
        
        fclose(archivo); //cierra archivo 
        fclose(cuadrado); //cierra archivo
        
        return 0;
    }
    else{
        cout<<"Error en los argumentos"<<endl;
        return 0;
    }

}