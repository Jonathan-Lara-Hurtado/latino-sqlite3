#Establece la versión mínima requerida de cmake para un proyecto.
cmake_minimum_required (VERSION 3.0.2)

#Nombre del proyecto
project(latino_sqlite)

include_directories(sqlite)

#target latino
add_library(latino-sqlite SHARED src/latino-sqlite.c)


target_link_libraries(latino-sqlite sqlite3 latino)

set(CMAKE_INSTALL_PREFIX "/usr")

install(FILES build/liblatino-sqlite.so DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES build/liblatino-sqlite.so DESTINATION ${CMAKE_INSTALL_PREFIX}/local/lib/)
