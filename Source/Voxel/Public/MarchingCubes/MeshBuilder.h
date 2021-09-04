#pragma once
#include "MarchingCubes.h"
#include "MeshData.h"
#include "VoxelData.h"

class FMCMeshBuilder
{
private:
	FMarchingCubes MarchingCubes;
	TMap<int, FVector> IndexToVertex;
	TMap<int, FVector> IndexToNormal;
	TMap<FVector, int> VertexToIndex;
	TArray<int32> Triangles;
	FVector Pos[8];
	float W[8] = {};

	static void SetVectors(FVector* V, float X, float Y, float Z);
	void AddTriangle(FVector V1, FVector V2, FVector V3);
	int InsertVertex(FVector V, FVector Normal);
	static FVector ComputeNormal(FVector V1, FVector V2, FVector V3);
	static int GetIndex(int X, int Y, int Z, int Size);
public:
	FMCMesh Build(FVoxel* Data, int Size);
};

