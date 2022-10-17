#include "ObjParser.h"
#include "Utils.h"
#include <iostream>
#include <fstream>


std::vector<ModelTriangle> parseObjFile(const std::string& filename) {
    std::cout << "START" << std::endl;
	std::ifstream inputStream(filename);
	std::string line;

    std::vector<ModelTriangle> triangles;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> faces;
    std::string currentColor;
    std::string mtlFileName;

    while (true) {
        getline(inputStream, line);
        if (inputStream.fail()) break;
        std::cout << line << std::endl;
        // split line
        std::vector<std::string> splittedLine = split(line, ' ');
        if (splittedLine[0] == "v") {
            float x = std::stof(splittedLine[1]);
            float y = std::stof(splittedLine[2]);
            float z = std::stof(splittedLine[3]);
            vertices.push_back(glm::vec3(x, y, z));
        }
        else if (splittedLine[0] == "f") {
            Colour triColour = Colour(currentColor, 0, 0, 0);
            glm::vec3 first = vertices[std::stoi(splittedLine[1]) - 1];
            glm::vec3 second = vertices[std::stoi(splittedLine[2]) - 1];
            glm::vec3 third = vertices[std::stoi(splittedLine[3]) - 1];
            triangles.push_back(ModelTriangle(first, second, third, triColour));
        }
        else if (splittedLine[0] == "o") {
            // for now - do nothing with the name
        }
        else if (splittedLine[0] == "usemtl") {
            currentColor = splittedLine[1];
        }
        else if (splittedLine[0] == "#") {
            // that's a comment
        }
        else if (splittedLine[0] == "mtllib") {
            mtlFileName = splittedLine[1];
        }
        else {
            // throw "Parser couldn't identify the line";
        }
    }
    
    return triangles;
}