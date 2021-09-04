#pragma once
#include "VoxelChunk.h"
#include "VoxelWorld.generated.h"

UCLASS()
class AVoxelWorld : public AActor
{
	GENERATED_BODY()
public:
	AVoxelWorld();
	UPROPERTY()
	TMap<FIntVector, UVoxelChunk*> Chunks;
};
