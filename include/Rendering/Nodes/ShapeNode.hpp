#pragma once
#include "NodeBase.hpp"
namespace bogong {
	namespace node {
		class ShapeNode : public NodeBase {
			std::shared_ptr<Mesh> mesh;
		public:
			ShapeNode(std::string name);
			ShapeNode() = delete;
			ShapeNode(const ShapeNode & shnode);
			~ShapeNode();

			void Draw();//I guess

		};
	}
}