#pragma once

#include "VoxelData.generated.h"

/*
 * Used for storing voxels since blueprints don't support 8 bit integer
 */
struct Voxel
{
	float Density;
	int8 Id;
};

USTRUCT(Blueprintable)
struct FVoxel
{
	GENERATED_BODY()
	FVoxel();
	FVoxel(const float Density, const int Id)
	{
		this->Density = Density;
		this->Id = Id;
	};
    
	UPROPERTY(BlueprintReadOnly)
	float Density;
	UPROPERTY(BlueprintReadOnly)
	int Id;
};
