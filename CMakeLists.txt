cmake_minimum_required(VERSION 3.5)
project(HotelProblem)

# Configuração do diretório de saída dos executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Adiciona a pasta "include" ao caminho de inclusão
include_directories(include)

# Coleta todos os arquivos fonte (.cpp) na pasta "src"
file(GLOB SOURCES "src/*.cpp")

# Cria um executável a partir dos arquivos fonte
add_executable(HotelProblem ${SOURCES})