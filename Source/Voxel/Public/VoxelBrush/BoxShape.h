#pragma once

#include "CoreMinimal.h"

#include "VoxelShape.h"
#include "UObject/Object.h"
#include "BoxShape.generated.h"

UCLASS(Blueprintable)
class VOXEL_API UBoxShape : public UVoxelShape
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(BlueprintReadWrite)
	FVector Size = FVector(2, 2, 2);
	virtual float SignedDistance(FVector& VoxelPosition, FVector& BrushPosition) override;
};
