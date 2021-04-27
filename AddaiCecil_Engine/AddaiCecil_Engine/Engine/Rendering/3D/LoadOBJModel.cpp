#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()),
normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}
LoadOBJModel::~LoadOBJModel() 
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
    normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox; 
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file:: " + filePath_,
			"LoadOBJModel.cpp", __LINE__);
		return;
	}
	
	std::string line;

	while (std::getline(in, line)) {
		//Vertex Data
		if (line.substr(0, 2) == "v ") {			
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >>  y >> z;
	
		 vertices.push_back(glm::vec3(x, y, z));

		 if (boundingBox.maxVert.x < x) {
		 
			 boundingBox.maxVert.x = x;
		 }
		 if (boundingBox.maxVert.y < y) {
			 boundingBox.maxVert.y = y;
		 }
		 if (boundingBox.maxVert.z < z) {
			 boundingBox.maxVert.z = z;
		 }
		 if (boundingBox.minVert.x > x) {
			 boundingBox.minVert.x = x;
		 }
		 if (boundingBox.minVert.y > y) {
			 boundingBox.minVert.y = y;
		 }
		 if (boundingBox.minVert.z > z) {
			 boundingBox.minVert.z = z;
		 }
		}


		//New Mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
		
		// Texture Data
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
		  textureCoords.push_back(glm::vec2(x, y));
		}
		
		// Normal Data
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
	
		// Face Data
		else if (line.substr(0, 2) == "f ") {
			 std::stringstream f(line.substr(2));
			 char dummy;
			 unsigned int aV, bV, cV, aT, bT, cT, aN, bN, cN;

			 f >> aV >> dummy >> aT >> dummy >> aN >>
				 bV >> dummy >> bT >> dummy >> bN >>
				 cV >> dummy >> cT >> dummy >> cN;

			 aV--; bV--; cV--;
			 aT--; bT--; cT--;
			 aN--; bN--; cN--;

			 indices.push_back(aV);
			 indices.push_back(bV);
			 indices.push_back(cV);

			 normalIndices.push_back(aN);
			 normalIndices.push_back(bN);
			 normalIndices.push_back(cN);

			 textureIndices.push_back(aT);
			 textureIndices.push_back(bT);
			 textureIndices.push_back(cT);
		}
		
	}
	PostProcessing();
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);
	
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}



void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);

}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);

}
