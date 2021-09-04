#include "VoxelBrush/VoxelBrush.h"

#include "VoxelBrush/SphereShape.h"
#include "VoxelBrush/VoxelShape.h"

UVoxelBrush::UVoxelBrush()
{
	this->Shape = NewObject<USphereShape>();
}

UVoxelBrush::UVoxelBrush(UVoxelShape* Shape)
{
	this->Shape = Shape;
}

void UVoxelBrush::Paint(FVoxel& Voxel, FVector& VoxelPosition, const int MaterialId)
{
	const float Dist = Shape->SignedDistance(VoxelPosition, Location);
	if(Dist < 1.0) Voxel.Id = MaterialId;
}

void UVoxelBrush::Sculpt(FVoxel& Voxel, FVector& VoxelPosition)
{
	Voxel.Density = Strength > 0 ?	FMath::Min(Voxel.Density, Shape->SignedDistance(VoxelPosition, Location) * Strength) :
									FMath::Max(Voxel.Density, Shape->SignedDistance(VoxelPosition, Location) * Strength);
}
