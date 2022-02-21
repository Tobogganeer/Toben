#include "OBJLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
//#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <filesystem>

HeapRef<Mesh> OBJLoader::Load(const char* path, float scale)
{
    if (!std::filesystem::exists(path))
    {
        std::cout << "Cannot load " << path << ", it doesn't exist!" << std::endl;
        return HeapRef<Mesh>();
    }

    std::cout << "Loading obj " << path << "..." << std::endl;

	std::ifstream stream(path);
	std::stringstream obj;
	obj << stream.rdbuf();

	std::string line;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

    std::vector<int> vIndices;
    std::vector<int> tIndices;
    std::vector<int> nIndices;
    //int face = 0;

	while (std::getline(obj, line))
	{
        // https://stackoverflow.com/questions/21120699/c-obj-file-parser
        // https://github.com/Tobogganeer/Tobengine-csharp/blob/main/TobEngine/Loading/Parsers/OBJParser.cs

        if (line.substr(0, 2) == "v ")
        {
            std::istringstream data(line.substr(2));
            glm::vec3 vert;
            float x, y, z;
            data >> x; data >> y; data >> z;
            vert = glm::vec3(x, y, z);
            vert *= scale;
            vertices.push_back(vert);
        }

        else if (line.substr(0, 3) == "vt ")
        {
            std::istringstream data(line.substr(3));
            glm::vec2 tex;
            float u, v;
            data >> u; data >> v;
            tex = glm::vec2(u, v);
            uvs.push_back(tex);
        }

        else if (line.substr(0, 3) == "vn ")
        {
            std::istringstream data(line.substr(3));
            glm::vec3 norm;
            float x, y, z;
            data >> x; data >> y; data >> z;
            norm = glm::vec3(x, y, z);
            normals.push_back(norm);
        }

        else if (line.substr(0, 2) == "f ")
        {
            int v1, v2, v3;
            int t1, t2, t3;
            int n1, n2, n3;

            const char* chh = line.c_str();
            sscanf_s(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

            // obj coords start at 1 not 0
            v1--; v2--; v3--;
            t1--; t2--; t3--;
            n1--; n2--; n3--;

            //face++;
            //std::cout << "Face " << face << std::endl;
            //std::cout << " -1 V: " << v1 << " T: " << t1 << " N: " << n1 << std::endl;
            //std::cout << " -2 V: " << v2 << " T: " << t2 << " N: " << n2 << std::endl;
            //std::cout << " -3 V: " << v3 << " T: " << t3 << " N: " << n3 << std::endl;
            vIndices.push_back(v1); vIndices.push_back(v2); vIndices.push_back(v3);
            tIndices.push_back(t1); tIndices.push_back(t2); tIndices.push_back(t3);
            nIndices.push_back(n1); nIndices.push_back(n2); nIndices.push_back(n3);
        }

    }

    //std::unordered_map<Vertex, unsigned int> existingVerts;
    //std::unordered_set<Vertex> existingVerts;
    std::vector<Vertex> existingVerts;
    HeapRef<std::vector<Vertex>> meshVerts(new std::vector<Vertex>());
    HeapRef<std::vector<unsigned int>> meshIndices(new std::vector<unsigned int>());

    for (int i = 0; i < vIndices.size(); i++)
    {
        Vertex v = Vertex(vertices[vIndices[i]], normals[nIndices[i]], uvs[tIndices[i]]);

        auto it = std::find(existingVerts.begin(), existingVerts.end(), v);
        if (it != existingVerts.end())
        {
            meshIndices->push_back((unsigned int)(it - existingVerts.begin()));
            //meshIndices->push_back(existingVerts.at(v));
        }
        else
        {
            //std::pair<Vertex, unsigned int> pair(v, (unsigned int)existingVerts.size());
            //existingVerts.insert(pair);
            existingVerts.push_back(v);
            meshVerts->push_back(v);
            meshIndices->push_back(existingVerts.size() - 1);
        }
        //glm::vec3 meshData;
        //glm::vec2 texData;
        //meshData = glm::vec3(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
        //texData = glm::vec2(texture[textureIndex[i]].x, texture[textureIndex[i]].y);
        //meshVertices.push_back(meshData);
        //texCoord.push_back(texData);
	}

    std::cout << "Finished loading " << path << std::endl;

    std::cout << "Num verts: " << meshVerts->size() << std::endl;

	return Mesh::Create(meshVerts, meshIndices);
}