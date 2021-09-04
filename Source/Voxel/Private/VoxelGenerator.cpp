#include "VoxelGenerator.h"

FastNoiseLite FVoxelGenerator::Noise = FastNoiseLite();

void FVoxelGenerator::Sculpt(FVoxel* Data, const int Size, UVoxelBrush* VoxelBrush)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				FVector Position = FVector(x, y, z);
				VoxelBrush->Sculpt(Data[Index], Position);
			}
		}
	}
}

void FVoxelGenerator::Paint(FVoxel* Data, const int Size, UVoxelBrush* VoxelBrush, const int MaterialId)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				FVector Position = FVector(x, y, z);
				VoxelBrush->Paint(Data[Index], Position, MaterialId);
			}
		}
	}
}

void FVoxelGenerator::Generate(const FVector Origin, const int Size, FVoxel* Data)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				Data[Index] = GetVoxel(Origin + FVector(x, y, z));
			}
		}
	}
}

FVoxel FVoxelGenerator::GetVoxel(const FVector Position)
{
	FVoxel VoxelData;
	const float Scale = 7;
	const float Height = Noise.GetNoise(Position.X * Scale, Position.Y * Scale) * 4.0 + 8;
	VoxelData.Density = Position.Z - Height;
	return VoxelData;
}
