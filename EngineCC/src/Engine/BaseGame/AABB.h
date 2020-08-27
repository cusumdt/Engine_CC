//#ifndef AABB_H
//#define AABB_H
//#define DLLEXPORT _declspec(dllexport)
//
//#include <glm/glm.hpp>
//
//#include <vector>
//
//#define	BOXVERTICES 8
//
//using namespace Graficos1;
//
//namespace Graficos2
//{
//
//	class DLLEXPORT AABB 
//	{
//		glm::vec3 vertex[BOXVERTICES];
//		unsigned int VAO, VBO, EBO;
//		std::vector<unsigned int> indices;
//		bool isVisible = true;
//		Shader boxShader;
//
//	public:
//		AABB();
//		void CalculateBoundingBox(Bounds bounds, glm::mat4 modelMat);
//		void CreateBuffers();
//		void Setup();
//		void Draw();
//		void SetVisibility(bool visibility) { isVisible = visibility; }
//		bool GetVisibility() const { return isVisible; }
//		glm::vec3 GetVertex(unsigned int index);
//	};
//}
//
//#endif //AABB_H