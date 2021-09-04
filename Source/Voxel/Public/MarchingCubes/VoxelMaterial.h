#pragma once

#include "VoxelMaterial.generated.h"

UCLASS(Blueprintable)
class UVoxelMaterial : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int32 Id;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Texture;
	
	static FColor Encode(const int Id);
};
