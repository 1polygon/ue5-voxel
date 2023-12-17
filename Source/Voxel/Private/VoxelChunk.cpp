#include "VoxelChunk.h"

#include "VoxelGenerator.h"
#include "MarchingCubes/MeshBuilder.h"
#include "MarchingCubes/MeshData.h"
#include "VoxelStats.h"
#include "DynamicMesh/MeshAttributeUtil.h"

UVoxelChunk::UVoxelChunk()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent = NewObject<UDynamicMeshComponent>(GetOwner());
	MeshComponent->RegisterComponent();
	MeshComponent->SetMaterial(0, Material);
	MeshComponent->SetComplexAsSimpleCollisionEnabled(true, true);
	MeshComponent->bUseAsyncCooking = true;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
	const FMCMesh MeshData = MeshBuilder.Build(Data, Size - 1);
	StatsRef.VertexCount = MeshData.Vertices.Num();
	StatsRef.TriangleCount = MeshData.Triangles.Num();

	TArray<int32> Indices;
	FDynamicMesh3* Mesh = MeshComponent->GetMesh();
	Mesh->Clear();
	Mesh->EnableVertexNormals(FVector3f());
	Mesh->EnableVertexColors(FVector4f());

	Mesh->EnableAttributes();
	Mesh->Attributes()->EnablePrimaryColors();
	const auto ColorOverlay = Mesh->Attributes()->PrimaryColors();

	for (int i = 0; i < MeshData.Vertices.Num(); i++)
	{
		int Id = Mesh->AppendVertex(MeshData.Vertices[i]);
		Indices.Add(Id);
		Mesh->SetVertexNormal(Id, FVector3f(MeshData.Normals[i]));
		Mesh->SetVertexColor(Id, FVector4f(MeshData.Colors[i]));
		ColorOverlay->AppendElement(MeshData.Colors[i]);
	}

	for (int i = 0; i < MeshData.Triangles.Num(); i += 3)
	{
		const int T0 = Indices[MeshData.Triangles[i]];
		const int T1 = Indices[MeshData.Triangles[i + 1]];
		const int T2 = Indices[MeshData.Triangles[i + 2]];
		const int Id = Mesh->AppendTriangle(T0, T1, T2);
		ColorOverlay->SetTriangle(Id, UE::Geometry::FIndex3i(T0, T1, T2));
	}

	MeshComponent->NotifyMeshUpdated();
	MeshComponent->UpdateCollision(false);

	StatsRef.UpdateTime = (FPlatformTime::Seconds() - StartTime) * 1000;
}
