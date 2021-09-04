#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VoxelShape.generated.h"

UCLASS(Blueprintable)
class VOXEL_API UVoxelShape : public UObject
{
	GENERATED_BODY()
public:
	virtual float SignedDistance(FVector& VoxelPosition, FVector& BrushPosition);
};
