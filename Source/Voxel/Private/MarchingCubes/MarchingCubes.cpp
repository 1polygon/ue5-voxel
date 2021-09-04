#include "MarchingCubes/MarchingCubes.h"

void FMarchingCubes::InsertTrianglesOfCube(FVector* P, float* Val, TArray<FVector>& Triangles) const
{
	int CubeIndex = 0;
	if (Val[0] < IsoLevel) CubeIndex |= 1;
	if (Val[1] < IsoLevel) CubeIndex |= 2;
	if (Val[2] < IsoLevel) CubeIndex |= 4;
	if (Val[3] < IsoLevel) CubeIndex |= 8;
	if (Val[4] < IsoLevel) CubeIndex |= 16;
	if (Val[5] < IsoLevel) CubeIndex |= 32;
	if (Val[6] < IsoLevel) CubeIndex |= 64;
	if (Val[7] < IsoLevel) CubeIndex |= 128;

	if (EdgeTable[CubeIndex] == 0) return;

	FVector Vertices[12];
	if ((EdgeTable[CubeIndex] & 1) == 1)
		Vertices[0] = InterpolateVertex(IsoLevel, P[0], P[1], Val[0], Val[1]);
	if ((EdgeTable[CubeIndex] & 2) == 2)
		Vertices[1] = InterpolateVertex(IsoLevel, P[1], P[2], Val[1], Val[2]);
	if ((EdgeTable[CubeIndex] & 4) == 4)
		Vertices[2] = InterpolateVertex(IsoLevel, P[2], P[3], Val[2], Val[3]);
	if ((EdgeTable[CubeIndex] & 8) == 8)
		Vertices[3] = InterpolateVertex(IsoLevel, P[3], P[0], Val[3], Val[0]);
	if ((EdgeTable[CubeIndex] & 16) == 16)
		Vertices[4] = InterpolateVertex(IsoLevel, P[4], P[5], Val[4], Val[5]);
	if ((EdgeTable[CubeIndex] & 32) == 32)
		Vertices[5] = InterpolateVertex(IsoLevel, P[5], P[6], Val[5], Val[6]);
	if ((EdgeTable[CubeIndex] & 64) == 64)
		Vertices[6] = InterpolateVertex(IsoLevel, P[6], P[7], Val[6], Val[7]);
	if ((EdgeTable[CubeIndex] & 128) == 128)
		Vertices[7] = InterpolateVertex(IsoLevel, P[7], P[4], Val[7], Val[4]);
	if ((EdgeTable[CubeIndex] & 256) == 256)
		Vertices[8] = InterpolateVertex(IsoLevel, P[0], P[4], Val[0], Val[4]);
	if ((EdgeTable[CubeIndex] & 512) == 512)
		Vertices[9] = InterpolateVertex(IsoLevel, P[1], P[5], Val[1], Val[5]);
	if ((EdgeTable[CubeIndex] & 1024) == 1024)
		Vertices[10] = InterpolateVertex(IsoLevel, P[2], P[6], Val[2], Val[6]);
	if ((EdgeTable[CubeIndex] & 2048) == 2048)
		Vertices[11] = InterpolateVertex(IsoLevel, P[3], P[7], Val[3], Val[7]);

	for (int i = 0; TriTable[CubeIndex][i] != -1; i += 3) {
		Triangles.Add(Vertices[TriTable[CubeIndex][i]]);
		Triangles.Add(Vertices[TriTable[CubeIndex][i + 1]]);
		Triangles.Add(Vertices[TriTable[CubeIndex][i + 2]]);
	}
}

FVector FMarchingCubes::InterpolateVertex(const float Iso, const FVector P1, const FVector P2, const float ValP1, const float ValP2) const
{
	if (_CMATH_::abs(Iso - ValP1) < 0.00001) return (P1);
	if (_CMATH_::abs(Iso - ValP2) < 0.00001) return (P2);
	if (_CMATH_::abs(ValP1 - ValP2) < 0.00001) return (P1);

	const float Mu = (Iso - ValP1) / (ValP2 - ValP1);
	
	FVector p;
	p.X = P1.X + Mu * (P2.X - P1.X);
	p.Y = P1.Y + Mu * (P2.Y - P1.Y);
	p.Z = P1.Z + Mu * (P2.Z - P1.Z);

	return p;
}
