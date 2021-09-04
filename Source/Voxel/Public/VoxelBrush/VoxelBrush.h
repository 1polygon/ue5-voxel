#pragma once

#include "CoreMinimal.h"

#include "VoxelShape.h"
#include "MarchingCubes/VoxelData.h"
#include "UObject/Object.h"
#include "VoxelBrush.generated.h"

UCLASS(Blueprintable)
class VOXEL_API UVoxelBrush : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FVector Location;
	UPROPERTY(BlueprintReadWrite)
	UVoxelShape* Shape;
	UPROPERTY(BlueprintReadWrite)
	float Strength = 1.0;
	
	UVoxelBrush();
	UVoxelBrush(UVoxelShape* Shape);
	
	void Paint(FVoxel& Voxel, FVector& VoxelPosition, int MaterialId);
	void Sculpt(FVoxel& Voxel, FVector& VoxelPosition);
};
