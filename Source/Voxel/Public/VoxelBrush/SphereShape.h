#pragma once

#include "CoreMinimal.h"

#include "VoxelShape.h"
#include "UObject/Object.h"
#include "SphereShape.generated.h"

UCLASS(Blueprintable)
class VOXEL_API USphereShape : public UVoxelShape
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Radius = 2.0;
	virtual float SignedDistance(FVector& VoxelPosition, FVector& BrushPosition) override;
};
