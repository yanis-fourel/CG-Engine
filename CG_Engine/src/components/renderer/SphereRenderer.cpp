#include <glm/gtc/constants.hpp>

#include "CG/components/renderer/SphereRenderer.hpp"
#include "CG/internal/ShaderProgram.hpp"
#include "CG/internal/GlError.hpp"

CG::SphereRenderer::SphereRenderer(std::uint32_t slices, std::uint32_t stacks) noexcept : m_stacks(stacks), m_slices(slices)
{
	generateVertices();
}

void CG::SphereRenderer::generateVertices()
{
	std::uint32_t nVerts = (m_slices + 1) * (m_stacks + 1);
	std::uint32_t elements = (m_slices * 2 * (m_stacks - 1)) * 3;

	// Verts
	float *v = new float[3 * static_cast<std::uint64_t>(nVerts)];
	// Normals
	float *n = new float[3 * static_cast<std::uint64_t>(nVerts)];
	// Tex coords
	float *tex = new float[2 * static_cast<std::uint64_t>(nVerts)];    //we don't use it now
	// Index
	unsigned int *el = new unsigned int[elements];  //index

	_generateVertices(v, n, tex, el);

	std::vector<Vertex> vertices;
	vertices.reserve(nVerts);

	for (unsigned i = 0; i < 3 * nVerts; i += 3) {
		vertices.push_back(Vertex{
			CG::Vector3{v[i], v[i + 1], v[i + 2]},
			CG::Vector3{n[i], n[i + 1], n[i + 2]},
			CG::Color::White()
			});
	}

	std::vector<std::uint32_t> indices;
	m_drawable.indices.reserve(elements);

	for (unsigned i = 0; i < elements; ++i)
		indices.push_back(el[i]);


	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	registerVertices(vertices, indices);
}

void CG::SphereRenderer::_generateVertices(float *verts, float *norms, float *tex, GLuint *el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / m_slices;
	GLfloat phiFac = glm::pi<float>() / m_stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= m_slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / m_slices;
		for (GLuint j = 0; j <= m_stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / m_stacks;
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
	for (GLuint i = 0; i < m_slices; i++) {
		GLuint stackStart = i * (m_stacks + 1);
		GLuint nextStackStart = (i + 1) * (m_stacks + 1);
		for (GLuint j = 0; j < m_stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == m_stacks - 1) {
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

void CG::SphereRenderer::registerVertices(const std::vector<Vertex> &vertices, const std::vector<std::uint32_t> &indices)
{
	GLuint vbo;
	GLCall(glGenBuffers(1, &vbo));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::remove_reference<decltype(vertices)>::type::value_type), vertices.data(), GL_STATIC_DRAW));

	GLCall(glGenVertexArrays(1, &m_drawable.vao));
	GLCall(glBindVertexArray(m_drawable.vao));
	GLCall(glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, position)));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, normal)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, color)));
	GLCall(glEnableVertexAttribArray(2));

	m_drawable.indices = indices;
}


void CG::SphereRenderer::draw(ShaderProgram &sm) const noexcept { m_drawable.draw(sm); }
