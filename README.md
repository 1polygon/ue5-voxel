# Marching Cubes in Unreal Engine 5
![Demo Image](https://i.imgur.com/W8lIxHx.png)
A small voxel sandbox using the [marching cubes](http://paulbourke.net/geometry/polygonise/) algorithm.

Uses [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) to generate the initial voxel data and the [DynamicMeshComponent](https://docs.unrealengine.com/5.3/en-US/BlueprintAPI/DynamicMeshComponent) to create the procedural mesh.
Voxel materials are encoded in the vertex colors and blended together in the VoxelMaterial.
