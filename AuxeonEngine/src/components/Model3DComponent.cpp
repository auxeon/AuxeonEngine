#include "../inc/components/Model3DComponent.h"

// comOwner is not available here 

Model3DComponent::Model3DComponent(String _modTexPath) : modTexPath(_modTexPath) {

	modShader = new Shader("shaders/vertex/triangle.vertex", "shaders/fragment/triangle.fragment");
	modGraphicsManager = GraphicsManager::gfxCreate();

	modWidth = modHeight = 0;
	mode = 0;

	// matrices
	modScale = modRotate = modTranslate = glm::mat4(1.0f);
	std::cout << "Model3DComponent : created \n";
}

Model3DComponent::~Model3DComponent() {
	delete modShader;
	std::cout << "Model3DComponent : destructed \n";
}

float sH = 0.3f;
float sW = 0.3f;

// comOwner Available here on 
void Model3DComponent::comInit() {

	modTranslate = glm::translate(glm::mat4(1.0f), comOwner->gaxGetComponent<TransformComponent>().txfPosition);

	if (comOwner->gaxComponentExists<TransformComponent>()) {

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(modTexPath.c_str(), &modWidth, &modHeight, &modChannels, 0);

		glGenTextures(1, &modTexID);
		glBindTexture(GL_TEXTURE_2D, modTexID);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, modWidth, modHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Model3DComponent : failed to load texture : " << modTexPath << std::endl;
		}

		modShader->use();
		glUniform1i(glGetUniformLocation(modShader->ID, "modTexID"), 0);
	}

}

void Model3DComponent::comUpdate() {

	vertices[0] = (0.0f + sW / 2.0f); vertices[1] = (0.0f + sH / 2.0f); vertices[2] = 0.0f; vertices[3] = 0.0f; vertices[4] = 1.0f; vertices[5] = 0.0f; vertices[6] = 1.0f; vertices[7] = 1.0f;// top right
	vertices[8] = (0.0f + sW / 2.0f); vertices[9] = (0.0f - sH / 2.0f); vertices[10] = 0.0f; vertices[11] = 0.0f; vertices[12] = 1.0f; vertices[13] = 0.0f; vertices[14] = 1.0f; vertices[15] = 0.0f;// bottom right
	vertices[16] = (0.0f - sW / 2.0f); vertices[17] = (0.0f - sH / 2.0f); vertices[18] = 0.0f; vertices[19] = 0.0f; vertices[20] = 1.0f; vertices[21] = 0.0f; vertices[22] = 0.0f; vertices[23] = 0.0f;// bottom left
	vertices[24] = (0.0f - sW / 2.0f); vertices[25] = (0.0f + sH / 2.0f); vertices[26] = 0.0f; vertices[27] = 0.0f; vertices[28] = 1.0f; vertices[29] = 0.0f; vertices[30] = 0.0f; vertices[31] = 1.0f;// top left 

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// A mult B
	// B*A
	// real order : T mult R mult S : left to right normal math mode
	// OpenGL order : T * (S*R) : right to left pairwise
	modTransform = comOwner->gaxGetComponent<Model3DComponent>().modTranslate *
		comOwner->gaxGetComponent<Model3DComponent>().modScale *
		comOwner->gaxGetComponent<Model3DComponent>().modRotate;

	//for (int c = 0; c < 4; ++c) {
	//	for (int d = 0; d < 4; ++d) {
	//		std::cout << modTransform[c][d] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << "\n";

}

void Model3DComponent::comDraw() {

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);



	if (mode == 0) {

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, modTexID);

		// render the triangle
		modShader->use();


		int loc = glGetUniformLocation(modShader->ID, "Model3DTr");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &modTransform[0][0]);

		loc = glGetUniformLocation(modShader->ID, "mode");
		glUniform1i(loc, mode);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		modShader->unuse();
	}

	if (mode == 1) {

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, modTexID);

		// render the triangle
		modShader->use();

		int loc = glGetUniformLocation(modShader->ID, "Model3DTr");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &modTransform[0][0]);

		loc = glGetUniformLocation(modShader->ID, "mode");
		glUniform1i(loc, 0);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		loc = glGetUniformLocation(modShader->ID, "Model3DTr");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &modTransform[0][0]);

		loc = glGetUniformLocation(modShader->ID, "mode");
		glUniform1i(loc, mode);

		glBindVertexArray(VAO);

		glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

		modShader->unuse();
	}


}

void Model3DComponent::comHandleEvents() {

}
