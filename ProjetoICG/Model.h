#pragma once

#include <stdio.h>
#include <GL/freeglut.h>

#include <fstream>
#include <stdlib.h>

//to map image filenames to textureIds
#include <string>
#include <map>
#include <iostream>

// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"

class Model
{
public:
	Model(const std::string fileName);
	~Model();
	void renderTheModel(double scale);
	bool importModel();
	
private:
	void recursive_render(const struct aiScene *sc, const struct aiNode* nd, float scale);
	void apply_material(const aiMaterial *mtl);
	void color4_to_float4(const aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void Color4f(const aiColor4D *color);

	// The default hard-coded path. Can be overridden by supplying a path through the command line.
	std::string modelpath;

	GLfloat		xrot;
	GLfloat		yrot;
	GLfloat		zrot;

	GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[4] = { 0.0f, 0.0f, 15.0f, 1.0f };
	
	// the global Assimp scene object
	const aiScene* scene = NULL;
	GLuint scene_list = 0;
	aiVector3D scene_min, scene_max, scene_center;

	// images / texture
	std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
	GLuint*		textureIds;							// pointer to texture Array
													// Create an instance of the Importer class
	Assimp::Importer importer;

};