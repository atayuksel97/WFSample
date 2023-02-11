using System.Collections.Generic;
using UnityEngine;

namespace NoOpArmy.WiseFeline
{
    /// <summary>
    /// AI actions should derive from this class to define a custom action which can be added to the set of actions for an agent
    /// </summary>
    public abstract class ActionBase : AIObject
    {
        /// <summary>
        /// The action's score will be multiplied by this value so you can increase/decrease the score of an action by moving this value away from 1.
        /// </summary>
        [Header("Generic")]
        ///The action's priority compared to others
        [SerializeField, Range(0, 1)]
        private float _weight = 1f;

        /// <summary>
        /// Maximum number of targets which this action should consider
        /// </summary>
        [SerializeField]
        protected int _maxTargetCount = 5;

        /// <summary>
        /// Should the action add a 25% score bonus to the current target to not change the target multiple times too quickly when scores are too close.
        /// </summary>
        [SerializeField]
        protected bool _useMomentumOnTarget;

        /// <summary>
        /// List of the considerations for the action.
        /// The score of the action is the result of multiplication of the scores of all of these considerations
        /// </summary>
        public List<ConsiderationBase> Considerations
        {
            get
            {
                if (_considerations == null)
                    _considerations = new List<ConsiderationBase>();
                return _considerations;
            }
        }

        /// <summary>
        /// List of all considerations
        /// </summary>
        [SerializeField, HideInInspector]
        private List<ConsiderationBase> _considerations;

        /// <summary>
        /// List of the considerations which work on the action's target
        /// </summary>
        private ConsiderationBase[] _targetedConsiderations;

        /// <summary>
        /// List of the considerations which work on the action's agent itself.
        /// </summary>
        private ConsiderationBase[] _selfConsiderations;

        /// <summary>
        /// The brain component which the action is executing for.
        /// </summary>
        protected Brain Brain { get; private set; }

        /// <summary>
        /// Is the action initialized?
        /// </summary>
        public bool IsInitialized { get; protected set; }

        /// <summary>
        /// The last calculated score of the action in the last think operation.
        /// </summary>
        public float Score { get { return _score; } }

        /// <summary>
        /// The wait of the action which is multiplied by the score to allow you to prioritize some actions
        /// </summary>
        public float Weight { get { return _weight; } }

        /// <summary>
        /// tracks all targets and their scores
        /// </summary>
        private Dictionary<Component, float> TargetsScoresDict;

        /// <summary>
        /// Used in calculation of the target scores
        /// </summary>
        private Dictionary<Component, float> _tempDict;

        /// <summary>
        /// The target with the best score.
        /// The type of this component depends on the type that you yourself store in the list in the UpdateTargets callback.
        /// If the action doesn't have any targets and target based considerations then this field doesn't matter and it value should be considered undefined.
        /// </summary>
        protected Component ChosenTarget;
        private float _score;
        private float _compensationFactor;
        private int _considerationCount;
        private float _momentom = 0.25f;

        /// <summary>
        /// Adds a component to the targets list of the action
        /// </summary>
        /// <param name="t"></param>
        protected void AddTarget(Component t)
        {
            TargetsScoresDict[t] = 1;
        }

        /// <summary>
        /// Adds an array of targets to the list of targets for the action
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="targets"></param>
        protected void AddTargets<T>(T[] targets) where T : Component
        {
            for (int i = 0; i < targets.Length; i++)
                TargetsScoresDict[targets[i]] = 1;
        }

        /// <summary>
        /// Adds an array of targets to the list of targets for the action
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="targets"></param>
        protected void AddTargets<T>(List<T> targets) where T : Component
        {
            for (int i = 0; i < targets.Count; i++)
                TargetsScoresDict[targets[i]] = 1;
        }

        /// <summary>
        /// Clears the list of targets for the action
        /// </summary>
        protected void ClearTargets()
        {
            TargetsScoresDict.Clear();
        }

        /// <summary>
        /// Removes a component from the list of targets for the action
        /// </summary>
        /// <param name="t"></param>
        protected void RemoveTarget(Component t)
        {
            TargetsScoresDict.Remove(t);
        }


        /// <summary>
        /// Clones the action for execution at runtime.
                /// </summary>
        /// <param name="set"></param>
        /// <returns></returns>
        internal ActionBase Clone(ActionSet set)
        {
            ActionBase action = Instantiate(this);
            for (int i = 0; i < action.Considerations.Count; i++)
            {
                action.Considerations[i] = action.Considerations[i].Clone();
            }
            return action;
        }

        /// <summary>
        /// Initializes the action.
        /// You don't need to call this. The Brain component does this automatically
        /// </summary>
        /// <param name="brain"></param>
        internal void Initialize(Brain brain)
        {
            Brain = brain;
            IsInitialized = true;

            TargetsScoresDict = new Dictionary<Component, float>();
            _tempDict = new Dictionary<Component, float>();

            InitializeConsiderations();
            OnInitialized();
        }

        /// <summary>
        /// Initializes the considerations of the action
        /// </summary>
        private void InitializeConsiderations()
        {
            List<ConsiderationBase> targetedCons = new List<ConsiderationBase>();
            List<ConsiderationBase> selfCons = new List<ConsiderationBase>();
            for (int i = 0; i < Considerations.Count; i++)
            {
                if (_considerations[i] != null)
                {
                    if (_considerations[i].NeedTarget)
                        targetedCons.Add(_considerations[i]);
                    else
                        selfCons.Add(_considerations[i]);
                }
            }
            _targetedConsiderations = targetedCons.ToArray();
            _selfConsiderations = selfCons.ToArray();


            for (int i = 0; i < _selfConsiderations.Length; i++)
            {
                _selfConsiderations[i].Initialize(Brain);
            }
            for (int i = 0; i < _targetedConsiderations.Length; i++)
            {
                _targetedConsiderations[i].Initialize(Brain);
            }
        }

        /// <summary>
        /// Called when the action is initialized
        /// </summary>
        protected virtual void OnInitialized()
        {

        }


        internal void Start() { OnStart(); }

        /// <summary>
        /// Should be used like MonoBehaviour's Start for the action
        /// </summary>
        protected virtual void OnStart() { }

        internal void Update() { OnUpdate(); }

        /// <summary>
        /// Should be used like MonoBehaviour's Update for the action
        /// </summary>
        protected virtual void OnUpdate() { }

        internal void LateUpdate() { OnLateUpdate(); }

        /// <summary>
        /// Should be used like MonoBehaviour's LateUpdate for the action
        /// </summary>
        protected virtual void OnLateUpdate() { }

        internal void FixedUpdate() { OnFixedUpdate(); }

        /// <summary>
        /// Should be used like MonoBehaviour's FixedUpdate for the action
        /// </summary>
        protected virtual void OnFixedUpdate() { }

        internal void Finish() { OnFinish(); }

        /// <summary>
        /// Called when the action is finished, either by failing or succeeding in achieving a desired behaviour
        /// </summary>
        protected virtual void OnFinish() { }

        protected void ActionSucceed()
        {
            Brain.ActionSucceed(this);
        }

        protected void ActionFailed()
        {
            Brain.ActionFailed(this);
        }

        internal void UpdateTargetsDictionary()
        {
            UpdateTargets();
        }

        /// <summary>
        /// Fires when you need to update the list of targets
        /// </summary>
        protected abstract void UpdateTargets();

        /// <summary>
        /// Calculates the score of the action
        /// </summary>
        /// <returns></returns>
        internal float GetScore()
        {
            _considerationCount = _selfConsiderations.Length + _targetedConsiderations.Length;

            if (_considerationCount == 0)
            {
                _score = 0;
                return 0;
            }

            _compensationFactor = 1f - (1f / _considerationCount);
            _score = 1;

            float selfScore = GetSelfScore();

            if (selfScore == 0)
            {
                _score = 0;
                return 0f;
            }

            // TODO: Remove destroyed targets

            if (TargetsScoresDict.Count > 0)
            {
                for (int i = 0; i < _targetedConsiderations.Length; i++)
                {
                    MultiplyConsiderationScore(_targetedConsiderations[i]);
                }

                ChosenTarget = GetBestTarget();
                _score = _score * selfScore * TargetsScoresDict[ChosenTarget];
            }
            else if (_targetedConsiderations.Length > 0)
                _score = 0;
            else
                _score = _score * selfScore;

            _score *= _weight;
            return _score;
        }

        /// <summary>
        /// Gets the score for self considerations
        /// </summary>
        /// <returns></returns>
        private float GetSelfScore()
        {
            float totalScore = 1;
            for (int i = 0; i < _selfConsiderations.Length; i++)
            {
                float score = _selfConsiderations[i].GetScore(Brain);
                score = ComputeCompensatedScore(score);
                totalScore *= score;
                if (totalScore == 0)
                    return 0;
            }
            return totalScore;
        }

        private void MultiplyConsiderationScore(ConsiderationBase consideration)
        {
            _tempDict.Clear();
            foreach (var pair in TargetsScoresDict)
            {
                if (pair.Key != null)
                    _tempDict.Add(pair.Key, pair.Value);
            }

            List<Component> keys = new List<Component>(_tempDict.Keys);
            foreach (var key in keys)
            {
                float score = consideration.GetScore(key);
                score = ComputeCompensatedScore(score);
                _tempDict[key] *= score;
            }
            TargetsScoresDict = new Dictionary<Component, float>(_tempDict);
            _tempDict.Clear();
        }

        private float ComputeCompensatedScore(float score)
        {
            float modification = (1f - score) * _compensationFactor;
            return score + (modification * score);
        }

        private Component GetBestTarget()
        {
            if (_useMomentumOnTarget)
            {
                if (ChosenTarget != null)
                {
                    if (TargetsScoresDict.ContainsKey(ChosenTarget))
                        TargetsScoresDict[ChosenTarget] += _momentom;
                }
            }

            Component target = null;
            float maxScore = 0;
            foreach (var targetPair in TargetsScoresDict)
            {
                if (targetPair.Value >= maxScore)
                {
                    target = targetPair.Key;
                    maxScore = targetPair.Value;
                }
            }
            return target;
        }
    }
}
