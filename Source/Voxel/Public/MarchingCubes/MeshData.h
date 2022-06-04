#pragma once
#include "CoreMinimal.h"

class FMCMesh
{
public:
	FMCMesh();
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FLinearColor> Colors;
	TArray<int> Triangles;
};
