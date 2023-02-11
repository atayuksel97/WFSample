using UnityEngine;

namespace NoOpArmy.WiseFeline
{
    /// <summary>
    /// This is the base class of Wise Feline AI assets. 
    /// You never need to use this directly.
    /// </summary>
    public class AIObject : ScriptableObject
    {
        /// <summary>
        /// The unique id of the asset.
        /// </summary>
        [HideInInspector]
        public string guid;

        /// <summary>
        /// The name of the asset
        /// </summary>
        public string Name;
    }
}
