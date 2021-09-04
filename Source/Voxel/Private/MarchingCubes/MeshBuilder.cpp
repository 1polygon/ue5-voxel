#include "MeshBuilder.h"

#include "MarchingCubes/MeshBuilder.h"
#include "MarchingCubes/MeshData.h"
#include "MarchingCubes/VoxelMaterial.h"

FMCMesh FMCMeshBuilder::Build(FVoxel* Data, int Size)
{
	FMCMesh Mesh;
	TArray<FVector> NewTriangles;

	const float VoxelSize = 100.0;
	const int DataOffset = 0;
	const int DataPadding = 1;
	const int Steps = 1;
	
	for (int z = 0; z < Size; z += Steps) {
		for (int y = 0; y < Size; y += Steps) {
			for (int x = 0; x < Size; x += Steps) {
				W[0] = Data[GetIndex(DataOffset+x,		DataOffset+y,		DataOffset+z,		Size + DataPadding)].Density;
				W[1] = Data[GetIndex(DataOffset+x,		DataOffset+y,		DataOffset+z + Steps,	Size + DataPadding)].Density;
				W[2] = Data[GetIndex(DataOffset+x + Steps,	DataOffset+y,		DataOffset+z + Steps,	Size + DataPadding)].Density;
				W[3] = Data[GetIndex(DataOffset+x + Steps,	DataOffset+y,		DataOffset+z,		Size + DataPadding)].Density;
				W[4] = Data[GetIndex(DataOffset+x,		DataOffset+y + Steps,DataOffset+	z,		Size + DataPadding)].Density;
				W[5] = Data[GetIndex(DataOffset+x,		DataOffset+y + Steps,DataOffset+	z + Steps,	Size + DataPadding)].Density;
				W[6] = Data[GetIndex(DataOffset+x + Steps,	DataOffset+y + Steps,	DataOffset+z + Steps,	Size + DataPadding)].Density;
				W[7] = Data[GetIndex(DataOffset+x + Steps,	DataOffset+y + Steps,	DataOffset+z,		Size + DataPadding)].Density;

				SetVectors(Pos, x / Steps, y / Steps, z / Steps);
				MarchingCubes.InsertTrianglesOfCube(Pos, W, NewTriangles);
			}
		}
	}

	for (int i = 0; i < NewTriangles.Num(); i += 3) AddTriangle(NewTriangles[i], NewTriangles[i + 1], NewTriangles[i + 2]);

	for (int i = 0; i < IndexToVertex.Num(); i++) {
		const FVector* v = IndexToVertex.Find(i);

		// Voxel Index
		const int x = DataOffset + FMath::RoundToInt(v->X * Steps), y = DataOffset + FMath::RoundToInt(v->Y * Steps), z = DataOffset + FMath::RoundToInt(v->Z * Steps);

		// Material
		const FVoxel Voxel = Data[GetIndex(x, y, z, Size + DataPadding)];
		Mesh.Colors.Add(UVoxelMaterial::Encode(Voxel.Id));

		// Normal
		FVector Grad;
		Grad.X = Data[GetIndex(x - 1, y, z, Size + DataPadding)].Density - Data[GetIndex(x + 1, y, z, Size + DataPadding)].Density;
		Grad.Y = Data[GetIndex(x, y - 1, z, Size + DataPadding)].Density - Data[GetIndex(x, y + 1, z, Size + DataPadding)].Density;
		Grad.Z = Data[GetIndex(x, y, z - 1, Size + DataPadding)].Density - Data[GetIndex(x, y, z + 1, Size + DataPadding)].Density;
		Grad.Normalize();
		Mesh.Normals.Add(-Grad);
		
		// Vertex
		Mesh.Vertices.Add(FVector(v->X * VoxelSize, v->Y * VoxelSize, v->Z * VoxelSize));
	}
	
	for (int i = 0; i < Triangles.Num(); i++) Mesh.Triangles.Add(Triangles[i]);

	return Mesh;
}

void FMCMeshBuilder::SetVectors(FVector* V, const float X, const float Y, const float Z)
{
	V[4].X = V[5].X = V[0].X = V[1].X = X;
	V[7].X = V[6].X = V[3].X = V[2].X = X + 1;

	V[0].Y = V[1].Y = V[2].Y = V[3].Y = Y;
	V[4].Y = V[5].Y = V[6].Y = V[7].Y = Y + 1;

	V[0].Z = V[3].Z = V[4].Z = V[7].Z = Z;
	V[1].Z = V[2].Z = V[5].Z = V[6].Z = Z + 1;
}

void FMCMeshBuilder::AddTriangle(const FVector V1, const FVector V2, const FVector V3)
{
	const FVector Normal = ComputeNormal(V1, V2, V3);

	Triangles.Add(InsertVertex(V1, Normal));
	Triangles.Add(InsertVertex(V2, Normal));
	Triangles.Add(InsertVertex(V3, Normal));
}

int FMCMeshBuilder::InsertVertex(const FVector V, const FVector Normal)
{
	int i = 0;
	if (!VertexToIndex.Contains(V)) {
		i = IndexToVertex.Num();
		IndexToVertex.Add(i, V);
		VertexToIndex.Add(V, i);
		IndexToNormal.Add(i, FVector());
	}
	else {
		i = *VertexToIndex.Find(V);
	}

	IndexToNormal.Add(i, *IndexToNormal.Find(i) + Normal);

	return i;
}

FVector FMCMeshBuilder::ComputeNormal(const FVector V1, const FVector V2, const FVector V3)
{
	FVector E1 = FVector(V2.X, V2.Y, V2.Z);
	FVector E2 = FVector(V3.X, V3.Y, V3.Z);
	E1 = E1 - V1;
	E2 = E2 - V1;
	return FVector::CrossProduct(E1, E2).GetSafeNormal();
}

int FMCMeshBuilder::GetIndex(const int X, const int Y, const int Z, const int Size) {
	return ((Z * Size * Size) + (Y * Size) + X);
}