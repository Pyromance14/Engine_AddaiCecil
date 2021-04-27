#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_)
: VAO(0), VBO(0), shaderProgram(0),
modelLoc(0), viewLoc(0), projectionLoc(0), diffMapLoc(0){
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_) {
	glUniform1i(diffMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);


	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(camPosLoc, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightsPosLoc, 1, glm::value_ptr(camera_->GetLightSource()[0]->getPosition()));
	 glUniform1f(lightsAmbValLoc, camera_->GetLightSource()[0]->getAmbVal());
	 glUniform1f(lightsDiffValLoc, camera_->GetLightSource()[0]->getDiffVal());
	 glUniform1f(lightsSpecValLoc, camera_->GetLightSource()[0]->getSpecVal());
     glUniform3fv(lightColVecLoc, 1, glm::value_ptr(camera_->GetLightSource()[0]->getLightColour()));
	 glUniform1f(matShineLoc, subMesh.material.shininess);
	 glUniform1f(matTranLoc, subMesh.material.transparency);
	 glUniform3fv(matAmbLoc, 1, glm::value_ptr(subMesh.material.ambient));
	 glUniform3fv(matDiffLoc, 1, glm::value_ptr(subMesh.material.diffuse));
	 glUniform3fv(matSpecLoc, 1, glm::value_ptr(subMesh.material.specular));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex),
		&subMesh.vertexList[0], GL_STATIC_DRAW);


	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, textureCoordinates));



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	diffMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	camPosLoc = glGetUniformLocation(shaderProgram, "camPos");
	lightsPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightsAmbValLoc = glGetUniformLocation(shaderProgram, "light.ambVal");
	lightsDiffValLoc = glGetUniformLocation(shaderProgram, "light.diffVal");
	lightsSpecValLoc = glGetUniformLocation(shaderProgram, "light.specVal");
	lightColVecLoc = glGetUniformLocation(shaderProgram, "light.lightColour");
	matShineLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	matTranLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecLoc = glGetUniformLocation(shaderProgram, "material.specular");
}
