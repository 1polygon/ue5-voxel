#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "VoxelStats.h"
#include "Components/DynamicMeshComponent.h"
#include "MarchingCubes/VoxelData.h"
#include "VoxelBrush/VoxelBrush.h"

#include "VoxelChunk.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOXEL_API UVoxelChunk : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FVoxelStats Stats = FVoxelStats();
	FVoxelStats& StatsRef = Stats;
	FVoxel* Data;
	UPROPERTY(BlueprintReadWrite)
	int Size = 64;
	
	UPROPERTY(BlueprintReadWrite)
	UDynamicMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Voxel Material")
	UMaterialInstance* Material;

	UVoxelChunk();
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetSize(int NewSize);
	UFUNCTION(BlueprintCallable)
	void Sculpt(UVoxelBrush* VoxelBrush);
	UFUNCTION(BlueprintCallable)
	void Paint(UVoxelBrush* VoxelBrush, int MaterialId);
	UFUNCTION(BlueprintCallable)
	void Generate() const;
	UFUNCTION(BlueprintCallable)
	void Update() const;	
};
