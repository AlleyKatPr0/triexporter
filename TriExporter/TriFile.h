#pragma once

#include "SharedCache.h"

#pragma pack(push, 1)

struct Header
{
	byte versionHi;
	byte versionLo;
	dword unknown1[3];
	dword sizeVertex; 
	dword numVertices;
	dword numSurfaces;
	dword numTriangles;
	dword unknown2[4];
	float minBox[3];
	float maxBox[3];
	dword unknown3[2];
	dword sizeHeader;
	dword unknown4;
};

struct Vertex
{
	float vertexPosition[3];
	float vertexNormal[3];
	float vertexUV[2];
};

struct VertexTB
{
	float vertexPosition[3];
	float vertexNormal[3];
	float vertexTangent[3];
	float vertexBinormal[3];
	float vertexUV[2];
};

//static const word vmaxsize = 128;
template<int size> struct CVertex: Vertex
{
	float unused[(size-32)/4];
};

struct Surface
{
	dword surfaceType;
	dword unknown[3];
	dword startIndex;
	dword numTriangles;
};

//struct Triangle
//{
//	word vertices[3];
//};

#pragma pack()

class TriFile
{
	public:
		bool hasTangentsBinormals = false;
		Header header{};
		std::unique_ptr<Vertex[]> m_vertices;
		std::vector<Surface> surfaces;
		std::vector<std::vector<std::vector<dword>>> triangles;
		std::vector<std::string> textures;
		dword numTriangles = 0;

		TriFile() = default;
		void Clear();
		virtual ~TriFile() = default;
		virtual bool LoadFile(CacheEntry &sce);
		virtual bool LoadFile(const std::string& filename);
		virtual bool LoadFile(std::ifstream &is);
		void ExportX(float size, const std::string& file, const std::string& dir);
		void ExportObj(float size, const std::string& file, const std::string& dir);
		void Export3ds(float size, const std::string& file, const std::string& dir);
		void ExportMy(float size, const std::string& file, const std::string& dir);
		void ExportVbo(float size, const std::string& file, const std::string& dir);
		void ExportA3D(float size, const std::string& file, const std::string& dir);
		void ExportFBX(float size, const std::string& file, const std::string& dir);

		inline const Vertex* verticesc(int i) const
		{
			return reinterpret_cast<const Vertex*>(reinterpret_cast<const char*>(m_vertices.get()) + i * header.sizeVertex);
		}

		inline const VertexTB* verticestb(int i) const
		{
			return reinterpret_cast<const VertexTB*>(reinterpret_cast<const char*>(m_vertices.get()) + i * header.sizeVertex);
		}
};
