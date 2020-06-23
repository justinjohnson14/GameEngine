#pragma once

#include <string>

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(const std::string&);
	void ProcessNode(aiNode*, const aiScene*);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Mesh* GetMesh(int index) { return &meshes[index]; }
	std::vector<Mesh> GetMeshes() { return meshes; }
public:
	std::vector<Mesh> meshes;
	Texture* texture;
	std::string directory;
};

