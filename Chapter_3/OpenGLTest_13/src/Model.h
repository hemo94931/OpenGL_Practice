#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include "Mesh.h"
#include "Camera.h"

using namespace std;

class Model
{
public:
	/*  ����   */
	Model(char* path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
private:
	/*  ģ������  */
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	/*  ����   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
};