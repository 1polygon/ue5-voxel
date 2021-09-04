#pragma once
#include "VoxelStats.generated.h"

USTRUCT(Blueprintable)
struct FVoxelStats
{
	GENERATED_BODY()
	
public:
	FVoxelStats();
	
	UPROPERTY(BlueprintReadOnly)
	int VertexCount = -1;
	UPROPERTY(BlueprintReadOnly)
	int TriangleCount = -1;
	UPROPERTY(BlueprintReadOnly)
	double GenerateTime = -1.0;
	UPROPERTY(BlueprintReadOnly)
	double UpdateTime = -1.0;
};