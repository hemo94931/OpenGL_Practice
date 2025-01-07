#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/types.h>

class Shader;

using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	string type;
	aiString path;
};

class Mesh {
public:
	/*  网格数据  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  函数  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);
private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh();
};