# Latino Sqlite3


## Sistemas Operativos Soportados:

*   Linux(ubuntu)

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

# Funciones
* Retorna un conector o nulo = conexion_bd(cadena);
* Retorna un dicionario{estado,resultado} = ejecutar_consulta(cadena)
* Retorna un logico = desconectar_bd(conector)
* retoran una cadena con la version de sqlite3 = version()

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
    escribir ("Conexion fallida")
fin
```
# Observaciones

* Todos los resultados de una consulta salen tipo cadena(Esto no deveria pero por el momento asi queda) Nota: Posible solucion a este problema es que haga una consulta de como esta compuesta la tabla(Pragma table_info) e ir comparando para saber el tipo de dato de estos.
* Es necesario que declares una variable antes del sqlite.ejecutar_consulta() aunque esta no sea usada como se puede apreciar en el ejemplo.


##### Cualquier aportacion o sugerencia es bienvenida.