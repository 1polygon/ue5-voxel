#include "VoxelBrush/BoxShape.h"

float UBoxShape::SignedDistance(FVector& VoxelPosition, FVector& BrushPosition)
{
	const FVector q = (VoxelPosition - BrushPosition).GetAbs() - Size;
	return FVector::Max(q, FVector()).Size() + FMath::Min(FMath::Max(q.X, FMath::Max(q.Y, q.Z)), 0.0f);
}
