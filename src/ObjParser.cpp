#include "ObjParser.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, Colour> parseMtlFile(const std::string& filename) {
    std::unordered_map<std::string, Colour> mtls;

    // std::ifstream inputStream(filename); - FIXME: need full path
    std::ifstream inputStream("C:\\Users\\ADMIN\\Documents\\HUJI\\D Semester A\\Computer Graphics\\RedNoise\\src\\obj-src\\cornell-box.mtl");
    std::string line;

    std::string currentColor;

    while (true) {
        getline(inputStream, line);
        if (inputStream.fail()) break;
        // split line
        std::vector<std::string> splittedLine = split(line, ' ');
        if (splittedLine[0] == "newmtl") {
            currentColor = splittedLine[1];
        }
        else if (splittedLine[0] == "Kd") {
            float red = std::stof(splittedLine[1]) * 255;
            float green = std::stof(splittedLine[2]) * 255;
            float blue = std::stof(splittedLine[3]) * 255;
            Colour c = Colour(currentColor, red, green, blue);
            mtls[currentColor] = c;
        }
        else {
            // throw "Parser couldn't identify the line";
        }
    }

    return mtls;
}

std::vector<ModelTriangle> parseObjFile(const std::string& filename) {
	std::ifstream inputStream(filename);
	std::string line;

    std::vector<ModelTriangle> triangles;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> faces;
    std::unordered_map<std::string, Colour> colours;
    std::string currentColor;
    std::string mtlFileName;

    while (true) {
        getline(inputStream, line);
        if (inputStream.fail()) break;
        // split line
        std::vector<std::string> splittedLine = split(line, ' ');
        if (splittedLine[0] == "v") {
            float x = std::stof(splittedLine[1]) * 0.35;
            float y = std::stof(splittedLine[2]) * 0.35;
            float z = std::stof(splittedLine[3]) * 0.35;
            vertices.push_back(glm::vec3(x, y, z));
        }
        else if (splittedLine[0] == "f") {
            Colour triColour = colours[currentColor];
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
            colours = parseMtlFile(splittedLine[1]);
        }
        else {
            // throw "Parser couldn't identify the line";
        }
    }
    
    return triangles;
}
