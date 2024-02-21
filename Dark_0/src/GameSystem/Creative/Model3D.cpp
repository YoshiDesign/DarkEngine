#include "Model3D.h"
#include <iostream>
#include <functional>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>


namespace std {
	// Template specialization for std::hash
	template<>
	struct hash<dark::Model3D::Vertex> {
		size_t operator()(dark::Model3D::Vertex const& vertex) const {

			// for final hash value
			size_t seed = 0;
			dark::hashCombine(seed, vertex.position, vertex.color, vertex.normal); //, vertex.texCoord);
			return seed;

		}
	};
}

namespace dark {


	Model3D::Model3D(std::vector<Model3D::Vertex> _vertices, std::vector<unsigned int> _indices)
		: vertices(_vertices), indices(_indices)
	{

	}
	Model3D::~Model3D()
	{

	}

	std::unique_ptr<Model3D> Model3D::createModelFromFile(const std::string& filepath)
	{
		Builder builder{};
		builder.loadModel(filepath);
		return std::make_unique<Model3D>(builder.vertices, builder.indices);
	}

	void Model3D::Builder::loadModel(const std::string& filepath)
	{
		tinyobj::attrib_t attrib;				// This stores the position, color, normal and texture coord
		std::vector<tinyobj::shape_t> shapes;	// Index values for each face element
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str()))
		{
			throw std::runtime_error(warn + err);
		}

		vertices.clear();
		indices.clear();

		// Will track which vertices have been added to the Builder.vertices vector and store the position at which the vertex was originally added
		std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		// For every face of our mesh
		for (const auto& shape : shapes)
		{
			// For every vertex of the face
			for (const auto& index : shape.mesh.indices)
			{
				Vertex vertex{};
				if (index.vertex_index >= 0)
				{
					vertex.position = {
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],	// The calculations here just mean we're always looking at values in groups of 3
						attrib.vertices[3 * index.vertex_index + 2],
					};

					vertex.color = {
						attrib.colors[3 * index.vertex_index + 0],
						attrib.colors[3 * index.vertex_index + 1],
						attrib.colors[3 * index.vertex_index + 2],
					};

				}

				if (index.normal_index >= 0)
				{

					vertex.normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2],
					};
				}

				//if (index.texcoord_index >= 0)
				//{

				//	vertex.texCoord = {
				//		attrib.texcoords[2 * index.texcoord_index + 0],
				//		attrib.texcoords[2 * index.texcoord_index + 1],
				//	};
				//}

				// If the vertex is new, we add it to the unique vertices map
				if (uniqueVertices.count(vertex) == 0)
				{
					// The vertex's position in the Builder.vertices vector is given by the vertices vector's current size
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					// Add it to the unique vertices map
					vertices.push_back(vertex);
				}

				// Add the position of the vertex to the Builder's indices vector
				indices.push_back(uniqueVertices[vertex]);

			}
		}

	}

}