# Latino Sqlite3


## Sistemas Operativos Soportados:

*   Linux(ubuntu)
*   Windows(32 bits)

## Dependencias

### Linux(Ubuntu):
 * sudo apt-get install -y libsqlite3-dev
 * Latino




# ¿Como instalarlo?
Antes de ejecutar lo siguien, verifique que cuente con la depencias necesarias.
### Linux(Ubuntu):

```
sudo ./instalar.sh
```

### Windows:
 * Descargar la libreria del siguiente enlace:
 https://github.com/Jonathan-Lara-Hurtado/latino-sqlite3/releases/download/1/latino_sqlite_x86.zip
 * Descomprimir el archivo
 * Copiar los siguientes archivos en el directorio donde se encuentra instalado latino en mi caso “C:\Program Files\Latino\bin”:
    *   “latino-sqlite.dll”
    *   “latino-sqlite.exp”
    *   “latino-sqlite.lib”
 * Pruebe la librería usando algun ejemplo que se encuentra en el repositorio de sqlite-latino:
 https://github.com/Jonathan-Lara-Hurtado/latino-sqlite3/blob/master/ejemplos/




# Funciones
* Retorna un conector o nulo = conexion_bd(cadena);
* Retorna un diccionario{estado,resultado} = ejecutar_consulta(cadena)
* Retorna un lógico = desconectar_bd(conector)
* Retorna una cadena con la versión de sqlite3 = version()

# Como funciona
```
incluir("sqlite")

bd = sqlite.conexion_bd("Prueba.db")


si (bd != nulo)

    consulta = "create table empleados(id integer,nombre text,apellidos text,ganancias real)"

    resultado = sqlite.ejecutar_consulta(bd,consulta)

    consulta = "insert into empleados(id,nombre,apellidos,ganancias) values (1,'pedro','parra',30.2)"
    resultado = sqlite.ejecutar_consulta(bd,consulta)

    consulta = "insert into empleados(id,nombre,apellidos,ganancias) values (1,'josue','lopez',30.2)"
    resultado = sqlite.ejecutar_consulta(bd,consulta)
    

    consulta = "select * from empleados where apellidos='parra' "
    
    resultado = sqlite.ejecutar_consulta(bd,consulta)
    
    si(resultado.estado)
        si(tipo(resultado.respuesta) == "lista")
            desde (i=0;i<lista.longitud(resultado.respuesta); i++)
                escribir (resultado.respuesta[i])
            fin
        sino
            escribir (resultado.respuesta)
        fin
    sino
        escribir ("Error :"..resultado.respuesta)
    fin
    

    si (sqlite.desconectar_bd(bd))
        escribir ("Se cerro la base de datos correctamente")
    fin

sino
    escribir ("Conexión fallida")
fin
```
# Observaciones

* Todos los resultados de una consulta salen tipo cadena(Esto no debe suceder pero por el momento así queda). Nota:La posible solución a este problema es que se haga una consulta de como esta compuesta la tabla (Pragma table_info) e ir comparando para saber el tipo de dato son estos.
* Es necesario que declares una variable antes del sqlite.ejecutar_consulta() aunque esta no sea usada, como se puede apreciar en el ejemplo anterior.


##### Cualquier aportación o sugerencia es bienvenida.