#include "VoxelWorld.h"

AVoxelWorld::AVoxelWorld()
{
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(DefaultSceneRoot);
}
