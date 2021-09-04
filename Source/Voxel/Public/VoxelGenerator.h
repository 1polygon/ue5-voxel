#pragma once

#include "CoreMinimal.h"

#include "Voxel/FastNoiseLite.h"
#include "MarchingCubes/VoxelData.h"
#include "VoxelBrush/VoxelBrush.h"

class FVoxelGenerator
{
private:
	static FastNoiseLite Noise;
public:
	static void Sculpt(FVoxel* Data, int Size, UVoxelBrush* VoxelBrush);
	static void Paint(FVoxel* Data, int Size, UVoxelBrush* VoxelBrush, int MaterialId);
	static void Generate(FVector Origin, int Size, FVoxel* Data);
	static FVoxel GetVoxel(FVector Position);
};
