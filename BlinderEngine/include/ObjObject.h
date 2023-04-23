#include "core.h"

#include "Model.h"

class ObjObject 
{
public:
	ObjObject(const std::string path, glm::vec3 scalingFactor = glm::vec3(1.0f, 1.0f, 1.0f));

	void draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3& translate,MShader &shader);
	void draw(const glm::mat4& projection, const glm::mat4& view, MShader& shader);

	void setTranslation(glm::vec3& translate);

	void update(glm::mat4 world);
	glm::mat4 getModel() { return mvp; };
	void spin(float deg);
	void move(float i);
private:

	Model* objModel;
	glm::vec3 scale;
	glm::mat4 mvp;
	glm::vec3 translate;
};