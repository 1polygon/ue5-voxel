#include "VoxelChunk.h"

#include "VoxelGenerator.h"
#include "MarchingCubes/MeshBuilder.h"
#include "VoxelStats.h"

UVoxelChunk::UVoxelChunk()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	RealtimeMeshComponent = NewObject<URealtimeMeshComponent>(GetOwner());
	RealtimeMeshComponent->RegisterComponent();
	RealtimeMeshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	RealtimeMeshComponent->SetMaterial(0, Material);
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

void UVoxelChunk::Update()
{
	const double StartTime = FPlatformTime::Seconds();
	FMCMeshBuilder MeshBuilder;

	FRealtimeMeshSimpleMeshData MeshData;
	MeshBuilder.Build(Data, Size - 1, MeshData);
	StatsRef.VertexCount = MeshData.Positions.Num();
	StatsRef.TriangleCount = MeshData.Triangles.Num();

	if (!IsValid(RealtimeMesh))
	{
		RealtimeMesh = RealtimeMeshComponent->InitializeRealtimeMesh<URealtimeMeshSimple>();
		MeshSectionKey = RealtimeMesh->CreateMeshSection(0,
		                                                 FRealtimeMeshSectionConfig(
			                                                 ERealtimeMeshSectionDrawType::Dynamic, 0), MeshData, true);
	}
	else
	{
		RealtimeMesh->UpdateSectionMesh(MeshSectionKey, MeshData);
	}

	StatsRef.UpdateTime = (FPlatformTime::Seconds() - StartTime) * 1000;
}
