#include "VoxelChunk.h"

#include "VoxelGenerator.h"
#include "MarchingCubes/MeshBuilder.h"
#include "MarchingCubes/MeshData.h"
#include "VoxelStats.h"

UVoxelChunk::UVoxelChunk()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	Mesh = NewObject<URuntimeMeshComponentStatic>(GetOwner());
	Mesh->RegisterComponent();
	Mesh->SetMaterial(0, Material);
	Data = new FVoxel[Size * Size * Size];
	Generate();
	Update();
}

void UVoxelChunk::BeginDestroy()
{
	Super::BeginDestroy();
	delete Data;
	Data = nullptr;
}

void UVoxelChunk::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UVoxelChunk::SetSize(int NewSize)
{
	Size = NewSize;
	delete Data;
	Data = new FVoxel[Size * Size * Size];
}

void UVoxelChunk::Sculpt(UVoxelBrush* VoxelBrush)
{
	FVoxelGenerator::Sculpt(Data, Size, VoxelBrush);
}

void UVoxelChunk::Paint(UVoxelBrush* VoxelBrush, int MaterialId)
{
	FVoxelGenerator::Paint(Data, Size, VoxelBrush, MaterialId);
}

void UVoxelChunk::Generate() const
{
	const double StartTime = FPlatformTime::Seconds();
	FVoxelGenerator::Generate(GetOwner()->GetActorLocation(), Size, Data);
	StatsRef.GenerateTime = (FPlatformTime::Seconds() - StartTime) * 1000;
}

void UVoxelChunk::Update() const
{
	const double StartTime = FPlatformTime::Seconds();
	FMCMeshBuilder MeshBuilder;
	const FMCMesh MCMesh = MeshBuilder.Build(Data, Size - 1);
	StatsRef.VertexCount = MCMesh.Vertices.Num();
	StatsRef.TriangleCount = MCMesh.Triangles.Num();

	if (Mesh->GetSectionIds(0).Num() == 0)
	{
		Mesh->CreateSectionFromComponents(0, 0, 0,
		                                  MCMesh.Vertices,
		                                  MCMesh.Triangles,
		                                  MCMesh.Normals,
		                                  TArray<FVector2D>(),
		                                  MCMesh.Colors,
		                                  TArray<FRuntimeMeshTangent>(),
		                                  ERuntimeMeshUpdateFrequency::Infrequent,
		                                  true);
	}
	else
	{
		Mesh->UpdateSectionFromComponents(0, 0,
		                                  MCMesh.Vertices,
		                                  MCMesh.Triangles,
		                                  MCMesh.Normals,
		                                  TArray<FVector2D>(),
		                                  MCMesh.Colors,
		                                  TArray<FRuntimeMeshTangent>());
	}

	StatsRef.UpdateTime = (FPlatformTime::Seconds() - StartTime) * 1000;
}
