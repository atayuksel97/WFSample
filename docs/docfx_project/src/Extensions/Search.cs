using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace NoOpArmy.WiseFeline
{
    /// <summary>
    /// This is a utility class which you can use to find GameObjects in the scene. However this is not the most
    /// performant way to do so and you can use any mechanism which suits your game. 
    /// However these methods have the minimum like not allocating memory for colliders
    /// </summary>
    /// <remarks>
    /// We intend to release additional modules which makes it easier to work with different geo-spacial structures  and gameplay types
    /// and search for objects
    /// </remarks>
    public static class Search
    {
        /// <summary>
        /// Find the closes collider in a sphere without allocating a new array for the raycast results.
        /// </summary>
        /// <param name="center">The center of the sphere</param>
        /// <param name="radius">The radius of the sphere</param>
        /// <param name="layerMask">The layermask which we should do the cast against</param>
        /// <param name="colliders">The array of colliders to be used for the cast operation</param>
        /// <returns>The closes collider or null if no colliders can be found</returns>
        public static Collider FindClosestCollider(Vector3 center, float radius, LayerMask layerMask, ref Collider[] colliders)
        {
            Array.Clear(colliders, 0, colliders.Length);
            Physics.OverlapSphereNonAlloc(center, radius, colliders, layerMask);

            float minDistance = float.MaxValue;
            int index = -1;
            for (int i = 0; i < colliders.Length; i++)
            {
                if (colliders[i] == null)
                    break;
                float sqDistance = (colliders[i].transform.position - center).sqrMagnitude;
                if (sqDistance < minDistance)
                {
                    index = i;
                    minDistance = sqDistance;
                }
            }
            if (index != -1)
            {
                return colliders[index];
            }
            return null;
        }

        /// <summary>
        /// Gets the array of overlapping colliders with a sphere
        /// </summary>
        /// <param name="center">The center of the sphere</param>
        /// <param name="radius">The radius of the sphere</param>
        /// <param name="layerMask">The layer mask to do the cast against</param>
        /// <param name="colliders">The array of colliders to be filled by the cast operation</param>
        public static void GetOverlappingColliders(Vector3 center, float radius, LayerMask layerMask, ref Collider[] colliders)
        {
            Array.Clear(colliders, 0, colliders.Length);
            Physics.OverlapSphereNonAlloc(center, radius, colliders, layerMask);
        }


        /// <summary>
        /// Gets the list of colliders overlapping by a sphere sorted with their distance from the center.
        /// This is an expensive method only good for samples and quick prototyping because it uses a relatively expensive sort operation
        /// </summary>
        /// <param name="center">The center of the sphere</param>
        /// <param name="radius">The radius of the sphere</param>
        /// <param name="layerMask">The layer mask to cast against</param>
        /// <param name="colliders">The array of colliders to use for the casting</param>
        /// <param name="transforms">The transforms list to fill</param>
        /// <param name="size">The maximum size of the list</param>
        public static void GetSortedTransforms(Vector3 center, float radius, LayerMask layerMask, ref Collider[] colliders, ref List<Transform> transforms, int size = 0)
        {
            Array.Clear(colliders, 0, colliders.Length);
            transforms.Clear();
            Search.GetOverlappingColliders(center, radius, layerMask, ref colliders);
            foreach (var col in colliders)
            {
                if (col == null)
                    break;
                transforms.Add(col.transform);
            }
            transforms = transforms.OrderBy(t => (t.transform.position - center).sqrMagnitude).ToList();
            
            if (size > 0)
                if (transforms.Count > size)
                    transforms.RemoveRange(size, transforms.Count - size);
        }
    }
}
