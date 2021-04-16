#include <glm/gtc/constants.hpp>

#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/rendering/ShaderProgram.hpp"
#include "CG/rendering/GLTrianglesBuilder.hpp"

static constexpr float kRadius = 0.5f;

void generateVertices(float *verts, float *norms, float *tex, GLuint *el, std::uint32_t slices, std::uint32_t stacks);

CG::ShapeRenderer CG::ShapeRenderer::Sphere(std::uint32_t slices, std::uint32_t stacks)
{
	GLTrianglesBuilder builder;

	std::uint32_t nVerts = (slices + 1) * (stacks + 1);
	std::uint32_t elements = (slices * 2 * (stacks - 1)) * 3;

	// Verts
	float *v = new float[3 * static_cast<std::uint64_t>(nVerts)];
	// Normals
	float *n = new float[3 * static_cast<std::uint64_t>(nVerts)];
	// Tex coords
	float *tex = new float[2 * static_cast<std::uint64_t>(nVerts)];
	// Index
	unsigned int *el = new unsigned int[elements];  //index

	generateVertices(v, n, tex, el, slices, stacks);

	std::vector<Vertex> vertices;
	builder.vertices.reserve(nVerts);

	for (unsigned i = 0; i < 3 * nVerts; i += 3) {
		builder.vertices.push_back(Vertex{
			.position = CG::Vector3{v[i], v[i + 1], v[i + 2]},
			.normal = CG::Vector3{n[i], n[i + 1], n[i + 2]},
			.color = CG::Color::White(),
			});
	}

	builder.indices.reserve(elements);

	for (unsigned i = 0; i < elements; ++i)
		builder.indices.push_back(el[i]);


	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	//registerVertices(vertices, indices);
	return CG::ShapeRenderer(std::move(builder.build()));
}


void generateVertices(float *verts, float *norms, float *tex, GLuint *el, std::uint32_t slices, std::uint32_t stacks)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / slices;
	GLfloat phiFac = glm::pi<float>() / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (GLuint j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = kRadius * nx; verts[idx + 1] = kRadius * ny; verts[idx + 2] = kRadius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < slices; i++) {
		GLuint stackStart = i * (stacks + 1);
		GLuint nextStackStart = (i + 1) * (stacks + 1);
		for (GLuint j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

//void registerVertices(const std::vector<Vertex> &vertices, const std::vector<std::uint32_t> &indices)
//{
//	GLuint vbo;
//	GLCall(glGenBuffers(1, &vbo));
//
//	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::remove_reference<decltype(vertices)>::type::value_type), vertices.data(), GL_STATIC_DRAW));
//
//	GLCall(glGenVertexArrays(1, &m_drawable.vao));
//	GLCall(glBindVertexArray(m_drawable.vao));
//	GLCall(glVertexAttribPointer(0,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		sizeof(Vertex),
//		(void *)offsetof(Vertex, position)));
//	GLCall(glEnableVertexAttribArray(0));
//	GLCall(glVertexAttribPointer(1,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		sizeof(Vertex),
//		(void *)offsetof(Vertex, normal)));
//	GLCall(glEnableVertexAttribArray(1));
//	GLCall(glVertexAttribPointer(2,
//		4,
//		GL_FLOAT,
//		GL_FALSE,
//		sizeof(Vertex),
//		(void *)offsetof(Vertex, color)));
//	GLCall(glEnableVertexAttribArray(2));
//
//	m_drawable.indices = indices;
//}
