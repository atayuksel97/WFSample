using System;
using System.Collections.Generic;
using UnityEngine;

namespace NoOpArmy.WiseFeline
{
    /// <summary>
    /// You should attach this component to any GameObject which wishes to be an AI agent controlled by a set of actions 
    /// </summary>
    public class Brain : MonoBehaviour
    {
        /// <summary>
        /// Fires when the list of behaviors available to this brain is modified by calling AddBehavior() or RemoveBehavior()
        /// </summary>
        public Action OnBehaviorListModified;

        /// <summary>
        /// The sets of behavior for an agent
        /// </summary>
        [SerializeField]
        private AgentBehavior _behavior;

        /// <summary>
        /// The wait period between calculations of action scores
        /// </summary>
        public float _thinkDuration = 2f;

        /// <summary>
        /// The wait period between calls to update target lists.
        /// Since updating this list is usually heavy, you should do this less often than score calculations and deal with null targets in your actions.
        /// </summary>
        public float _updateTargetsDuration = 5f;

        public AgentBehavior Behavior { get { if (_clonedBehavior == null) return _behavior; else return _clonedBehavior; } }
        private AgentBehavior _clonedBehavior;
        private List<ActionData> _actionDataList;
        private bool _pauseThinking = false;
        private bool _pauseAction = false;
        private float _thinkTimer = 0;
        private float _updateTimer = 0;
        private ActionBase _currentAction;

        private void Awake()
        {
            if (_behavior == null)
            {
                throw new NullReferenceException("The behavior cannot be null");
            }
            _clonedBehavior = _behavior.Clone();
            for (int i = 0; i < Behavior.ActionSets.Count; i++)
            {
                for (int j = 0; j < Behavior.ActionSets[i].Actions.Count; j++)
                {
                    ActionBase action = Behavior.ActionSets[i].Actions[j];
                    if (action != null)
                    {
                        action.Initialize(this);
                    }
                }
            }
            _actionDataList = new List<ActionData>();
        }

        private void Start()
        {
            if (Behavior == null)
                return;

            UpdateActionsTargets();
            Think();
        }

        private void Update()
        {
            if (Behavior == null)
                return;

            if (!_pauseThinking)
            {
                _updateTimer += Time.deltaTime;
                if (_updateTimer >= _updateTargetsDuration)
                {
                    _updateTimer = 0;
                    UpdateActionsTargets();
                }

                _thinkTimer += Time.deltaTime;
                if (_thinkTimer >= _thinkDuration)
                {
                    _thinkTimer = 0;
                    Think();
                }
            }

            if (!_pauseAction)
            {
                _currentAction?.Update();
            }
        }

        private void LateUpdate()
        {
            if (!_pauseAction)
            {
                _currentAction?.LateUpdate();
            }
        }

        private void FixedUpdate()
        {
            if (!_pauseAction)
            {
                _currentAction?.FixedUpdate();
            }
        }

        /// <summary>
        /// Puases/Resumes thinking which changes action scores
        /// </summary>
        /// <param name="pause">Pauses the thinking if true and resumes it if false.</param>
        public void PauseThinking(bool pause)
        {
            _pauseThinking = pause;
        }

        /// <summary>
        /// Pauses/Resumes executing the current action.
        /// </summary>
        /// <param name="pause">pauses ecution if true and resumes it if false</param>
        public void PauseExecutingActions(bool pause)
        {
            _pauseAction = pause;
        }

        private void UpdateActionsTargets()
        {
            for (int i = 0; i < Behavior.ActionSets.Count; i++)
            {
                ActionSet set = Behavior.ActionSets[i];
                for (int j = 0; j < set.Actions.Count; j++)
                {
                    ActionBase action = set.Actions[j];
                    action.UpdateTargetsDictionary();
                }
            }
        }

        private void Think()
        {
            _actionDataList.Clear();
            for (int i = 0; i < Behavior.ActionSets.Count; i++)
            {
                ActionSet set = Behavior.ActionSets[i];
                for (int j = 0; j < set.Actions.Count; j++)
                {
                    ActionBase action = set.Actions[j];
                    _actionDataList.Add(new ActionData(set, action, action.GetScore()));
                }
            }

            int maxIndex = GetMaxScoreIndex();
            if (maxIndex >= 0)
            {
                if (_currentAction != _actionDataList[maxIndex].Action)
                {
                    _currentAction?.Finish();
                    _currentAction = _actionDataList[maxIndex].Action;
                    _currentAction.Start();
                }
                Behavior.OnThinkDone?.Invoke(_actionDataList[maxIndex]);
            }
            else
            {
                Behavior.OnThinkDone?.Invoke(new ActionData());
            }
        }

        private int GetMaxScoreIndex()
        {
            int index = -1;
            float max = 0;
            for (int i = 0; i < _actionDataList.Count; i++)
            {
                if (_actionDataList[i].Score > max)
                {
                    max = _actionDataList[i].Score;
                    index = i;
                }
            }
            return index;
        }

        internal void ActionSucceed(ActionBase action)
        {
            if (_currentAction == action)
                _currentAction = null;
        }

        internal void ActionFailed(ActionBase action)
        {
            if (_currentAction == action)
                _currentAction = null;
        }

        /// <summary>
        /// Adds actions inside a behavior agent asset to the actions of this brain
        /// </summary>
        /// <param name="agentBehavior">The agent behavior asset to add</param>
        /// <remarks>
        /// Duplicate actions which already exist in the brain will be added again too. 
        /// You should design your behaviors so they don't have duplicate actions
        /// You usually do not need multiple instances of an action in the same brain
        /// </remarks>
        public void AddBehavior(AgentBehavior agentBehavior)
        {
            if (!Application.isPlaying) return;
            if (agentBehavior == null) return;
            if (_clonedBehavior == null)
                throw new Exception(String.Format("Can not combine behavior in {0} because cloned behavior is null.", gameObject.name));
            if (agentBehavior.ActionSets.Count == 0) return;
            
            foreach (var set in agentBehavior.ActionSets)
            {
                _clonedBehavior.AddRuntimeActionSet(set, this);
            }
            OnBehaviorListModified?.Invoke();
        }

        /// <summary>
        /// Adds an action set to the set of behaviors this brain has available to score and execute
        /// </summary>
        /// <param name="set">The action set to add</param>
        /// <remarks>
        /// Duplicat actions which already exist in the brain will be added again too so you should design your action sets acordingly. 
        /// You usually do not need multiple instances of an action in the same brain
        /// </remarks>
        public void AddActionSet(ActionSet set)
        {
            if (!Application.isPlaying) return;
            if (set == null) return;

            _clonedBehavior.AddRuntimeActionSet(set, this);
            OnBehaviorListModified?.Invoke();
        }

        /// <summary>
        /// Removes actions of a behavior from this brain
        /// </summary>
        /// <param name="agentBehavior"></param>
        public void RemoveBehavior(AgentBehavior agentBehavior)
        {
            if (!Application.isPlaying) return;
            if (agentBehavior == null) return;
            if (_clonedBehavior == null)
                throw new Exception(String.Format("Can not combine behavior in {0} because cloned behavior is null.", gameObject.name));
            if (agentBehavior.ActionSets.Count == 0) return;

            foreach (var set in agentBehavior.ActionSets)
            {
                _clonedBehavior.RemoveRuntimeActionSet(set);
            }
            OnBehaviorListModified?.Invoke();
        }

        /// <summary>
        /// Removes a specific action set from the list of behaviors of this brain
        /// </summary>
        /// <param name="set"></param>
        public void RemoveActionSet(ActionSet set)
        {
            if (!Application.isPlaying) return;
            if (set == null) return;

            _clonedBehavior.RemoveRuntimeActionSet(set);
            OnBehaviorListModified?.Invoke();
        }

        private void OnDestroy()
        {
            Destroy(Behavior);
        }
    }

    /// <summary>
    /// This struct represents the runtime info for a an action and its final score
    /// </summary>
    public struct ActionData
    {
        /// <summary>
        /// The action set this instance refers to.
        /// </summary>
        public ActionSet ActionSet;

        /// <summary>
        /// Which action this instance refers to.
        /// </summary>
        public ActionBase Action;

        /// <summary>
        /// The score of the action in the last think operation.
        /// </summary>
        public float Score;

        public ActionData(ActionSet set, ActionBase action, float score)
        {
            ActionSet = set;
            Action = action;
            Score = score;
        }
    }
}
