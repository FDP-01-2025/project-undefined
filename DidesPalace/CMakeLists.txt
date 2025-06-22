cmake_minimum_required(VERSION 3.10)
project(DidesPalace)

# Configuración básica
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorio de salida para los ejecutables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Incluir directorios
# Carpeta include (Estan todos los archivos .h)
include_directories(src/include)

# Archivos fuente
# Agregar aqui los archivos nuevos que se vayan creando
set(SOURCES
    "src/main.cpp"
    "src/maze.cpp"
    "src/menu.cpp"
    "src/player.cpp"
    "src/miniGames/1_riddles.cpp"
    "src/miniGames/2_spotDifference.cpp"
    "src/miniGames/3_numberSort.cpp"
    "src/miniGames/4_keySmash.cpp"
    "src/levels/level1.cpp"
    "src/levels/level2.cpp"
    "src/levels/level3.cpp"
    "src/levels/level4.cpp"
)

# Crear el ejecutable principal
add_executable(DidesPalace ${SOURCES})
# Se especifica que es aplicacion de consola
target_link_libraries(DidesPalace PRIVATE mingw32) 

#Copia carpeta data al directorio de salida
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${EXECUTABLE_OUTPUT_PATH})


#Configuraciones específicas para Windows
if(WIN32)
# Esta vacio
endif()

message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "Output will be in: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "Data files will be copied to: ${EXECUTABLE_OUTPUT_PATH}/data")