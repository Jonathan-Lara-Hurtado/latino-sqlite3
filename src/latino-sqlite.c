/*
The MIT License (MIT)
Copyright (c) Latino - Lenguaje de Programacion
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <stdlib.h>

#define LATINO_LIB
//se agrega la cabecera de sqlite3
#include "sqlite3.h"
//se agrega la cabecera de latino
#include "latino.h"

//se define el nombre con el cual invocaremos en latino
#define LIB_NAME "sqlite"

char* minuscula(char *);
char* instrucionsql(char *);
int callback(void *,int,char **,char **);


lat_mv *tmpMV;


void conexion_sqlite(lat_mv *mv){
    lat_objeto *nombreBaseDatos = latC_desapilar(mv);
    sqlite3 *db;
    int resultado;

    resultado = sqlite3_open(latC_checar_cadena(mv,nombreBaseDatos),&db);
    if(resultado){
        fprintf(stderr,"No se puede abrir la base de datos: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        latC_apilar(mv,latO_nulo);
    }else{
        lat_objeto *tmpDB = latC_crear_cdato(mv,db);
        latC_apilar(mv,tmpDB);
    }
}


void ejecutar(lat_mv *mv){

    lat_objeto *sql = latC_desapilar(mv);
    lat_objeto *tmpDB = latC_desapilar(mv);
    
    char *consulta = latC_checar_cadena(mv,sql);

    char *instruccion = instrucionsql(consulta);

    char *mensaje_error = 0;

    int resultado = 0;

    sqlite3 *db = latC_checar_cptr(mv,tmpDB);

    lat_objeto *dic = latC_crear_dic(mv,latH_crear(mv));

    if(strcmp(instruccion,"select") == 0){
        
        lat_objeto *lista = latC_crear_lista(mv,latL_crear(mv));
        latC_apilar(mv,lista);
        tmpMV = mv;
        resultado = sqlite3_exec(db,consulta,callback,0,&mensaje_error);    
        mv = tmpMV;
        lat_objeto *tmplista = latC_desapilar(mv);
        if(resultado == SQLITE_OK){
            latH_asignar(mv, latC_checar_dic(mv, dic),"estado",latC_crear_logico(mv,1));
            latH_asignar(mv, latC_checar_dic(mv, dic),"respuesta",tmplista);
        }

    }else{
        resultado = sqlite3_exec(latC_checar_cptr(mv,tmpDB),consulta,0,0,&mensaje_error);
        if(resultado == SQLITE_OK){
            latH_asignar(mv, latC_checar_dic(mv, dic),"estado",latC_crear_logico(mv,1));
            latH_asignar(mv, latC_checar_dic(mv, dic),"respuesta",latC_crear_cadena(mv,"¡¡Ejecucion existosa!!"));
        }
    }

    if(resultado != SQLITE_OK){
        latH_asignar(mv, latC_checar_dic(mv, dic),"estado",latC_crear_logico(mv,0));
        latH_asignar(mv, latC_checar_dic(mv, dic),"respuesta",latC_crear_cadena(mv,mensaje_error));
        sqlite3_free(mensaje_error);
    }

    latC_apilar(mv,dic);  
}


int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;

    lat_objeto *o = latC_desapilar(tmpMV);
    lat_objeto *dic = latC_crear_dic(tmpMV,latH_crear(tmpMV));
    
    for (int i = 0; i < argc; i++) {
        latH_asignar(tmpMV, latC_checar_dic(tmpMV, dic),azColName[i],latC_crear_cadena(tmpMV,argv[i]));
       // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");    
    }

    latL_agregar(tmpMV,latC_checar_lista(tmpMV,o),dic);

    latC_apilar(tmpMV,o);
    return 0;
}


void desconectar_sqlite(lat_mv *mv){
    lat_objeto *tmpDB = latC_desapilar(mv);
    int resultado;

    resultado = sqlite3_close(latC_checar_cptr(mv,tmpDB));
    
    if(resultado != SQLITE_OK){
        latC_apilar(mv,latO_falso);
    }else{
        latC_apilar(mv,latO_verdadero);
    }
}

/*
funcion que retorna la operacion de consulta
(select,create,deleter,etc).
*/
void version_sqlite(lat_mv *mv){
    const char *version = sqlite3_libversion();
    latC_apilar(mv,latC_crear_cadena(mv,version));
}



static const lat_CReg libsqlite[] ={{"conexion_bd",conexion_sqlite,1},
                                    {"ejecutar_consulta",ejecutar,2},
                                    {"desconectar_bd",desconectar_sqlite,1},
                                    {"version",version_sqlite,0},
                                    {NULL,NULL}};



LATINO_API void latC_abrir_liblatino_sqlite(lat_mv *mv){
    latC_abrir_liblatino(mv, LIB_NAME, libsqlite);
}

/*
funcion que retorna un cadena en minusculas
*/
char* minuscula(char *cadena){
    char *nuevaCadena = malloc(sizeof(char)* strlen(cadena));
    int i=0;
    for (int i = 0; i < strlen(cadena); i++)
    {
    char letra =(char) tolower(cadena[i]);
    nuevaCadena[i] = letra; 
    }
    return nuevaCadena;    
}

/*
funcion que retorna la operacion de consulta
(select,create,deleter,etc).
*/
char* instrucionsql(char *cadena){
    char *nuevaCadena = malloc(sizeof(char)* 10);
    for (int i = 0; i < strlen(cadena); i++)
    {
        if(cadena[i] != ' '){
            char letra =(char) tolower(cadena[i]);
            nuevaCadena[i] = letra; 
        }else{
            break;
        }
    }
    return nuevaCadena;
}