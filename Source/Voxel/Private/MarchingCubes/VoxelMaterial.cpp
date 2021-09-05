#include "MarchingCubes/VoxelMaterial.h"

FColor UVoxelMaterial::Encode(const int Id)
{
	switch (Id)
	{
	case 0:
		return FColor(255,0,0,0);
	case 1:
		return FColor(0,255,0,0);
	case 2:
		return FColor(0,0,255,0);
	case 3:
		return FColor(0,0,0,255);
	default:
		return FColor(255,0,0,0);
	}
}
