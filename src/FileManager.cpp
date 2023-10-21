#include "FileManager.h"


FileManager::FileManager() {

}

FileManager::~FileManager() {

}

Problem* FileManager::getFromFile(std::string path) {
    std::ifstream inputFile(path);  // Replace "file.txt" with the name of your file

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
    }


    std::string firstLine;
    std::getline(inputFile, firstLine);
    std::istringstream iss(firstLine);
    int val1, val2, val3;
    if (!(iss >> val1 >> val2 >> val3)) {
        std::cerr << "Erro ao ler os três valores inteiros da primeira linha." << std::endl;
    }

    std::cout << val1 << ":" << val2 << ":" << val3 << std::endl;

    // Lê a segunda linha e converte para um inteiro
    std::string secondLine;
    std::getline(inputFile, secondLine);
    int singleValue;
    std::istringstream iss2(secondLine);
    if (!(iss2 >> singleValue)) {
        std::cerr << "Erro ao ler o valor inteiro da segunda linha." << std::endl;
    }

    std::cout << singleValue << std::endl;

    std::string thirdLine;

    std::getline(inputFile, thirdLine);

    std::istringstream thirdLineStream(thirdLine);

    // Exibe os valores lidos
    Problem* problem = new Problem(val1, val2, val3, singleValue);

    float value;  // Alterado para float
    while (thirdLineStream >> value) {
        problem->addTripLength(value);
    }

    std::string firstAndFinalHotel;
    std::vector<float> data;
    std::string tmp;
    std::getline(inputFile, tmp);
    data.reserve(12);
    for (int i = 0; i < 2 && std::getline(inputFile, firstAndFinalHotel); ++i) {
        std::istringstream iss(firstAndFinalHotel);
        //std::string token;
        //iss >> token;  // Ignorar o primeiro valor (H0, H1, etc.)
        float value;
        while (iss >> value) {
            data.push_back(value);
        }
    }

    problem->setFirstHotel(data[0], data[1], data[2]);
    problem->setFinalHotel(data[3], data[4], data[5]);

    

    std::string hotelsStr;
    for (int i = 0; i < val2 && std::getline(inputFile, hotelsStr); ++i) {
        std::istringstream iss(hotelsStr);
        //std::string token;
        //iss >> token;  // Ignorar o primeiro valor (H0, H1, etc.)
        float value;
        std::vector<float> hData;
        
        while (iss >> value) {
            hData.push_back(value);
        }
        
        problem->addHotel(hData[0], hData[1], hData[2]);
    }
    

    std::string customerStr;
    while (std::getline(inputFile, customerStr)) {
        std::istringstream iss(customerStr);
        //std::string token;
        //iss >> token;  // Ignorar o primeiro valor (H0, H1, etc.)
        float value;
        std::vector<float> cData;
        
        while (iss >> value) {
            cData.push_back(value);
        }
        
        problem->addCustomer(cData[0], cData[1], cData[2]);
    }

    inputFile.close();

    return problem;
}