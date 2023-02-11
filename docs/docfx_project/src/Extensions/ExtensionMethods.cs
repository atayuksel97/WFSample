using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace NoOpArmy.WiseFeline
{
    /// <summary>
    /// These are different methods extending types with methods we needed to make the code more readable.
    /// </summary>
    public static class ExtensionMethods
    {
        /// <summary>
        /// Gets the index of the item with the highest value in the array.
        /// </summary>
        /// <param name="array"></param>
        /// <returns></returns>
        public static int MaxIndex(this float[] array)
        {
            int index = -1;
            float max = float.NegativeInfinity;
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] > max)
                {
                    max = array[i];
                    index = i;
                }
            }
            return index;
        }

        /// <summary>
        /// Returns the indices of all items with the maximum value in the array.
        /// </summary>
        /// <param name="array"></param>
        /// <returns></returns>
        public static int[] MaxIndices(this float[] array)
        {
            int index = array.MaxIndex();
            List<int> indices = new List<int>();
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] == array[index])
                {
                    indices.Add(i);
                }
            }
            return indices.ToArray();
        }
    }
}
