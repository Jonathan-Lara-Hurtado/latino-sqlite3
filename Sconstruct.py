import platform
import os

sistema = platform.system()
ruta_Absoluta = GetLaunchDir()


ruta_include_latino = "C:\\Program Files\\Latino\\include"
ruta_librerias = "C:\\Program Files\\Latino\\bin"
ruta_regex = "C:\\Users\\Asus\\git\\latino-Core\\src\\latino-regex\\src"
ruta_sqlite = os.path.join(ruta_Absoluta,"sqlite/")
ruta_sqlite_construccion = os.path.join(ruta_Absoluta,"sqlite/build/")


CambioArquitectura = False

if CambioArquitectura:
    arquitectura = 'x86_64'
else:
    arquitectura = 'x86'


#Se crea el entorno scons
entorno = Environment(TARGET_ARCH=arquitectura)



entorno.Append(CPPPATH=[ruta_include_latino,ruta_regex,ruta_sqlite])

Export('entorno')
SConscript(['sqlite/Sconscript'])


entorno.Append(LIBPATH=[ruta_librerias,ruta_sqlite_construccion])


entorno.Append(LIBS = ['latino','sqlite'])

#s
entorno.SharedLibrary(target = "build/latino-sqlite", source = "src/latino-sqlite.c")
