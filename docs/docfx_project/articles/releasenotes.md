# Release Notes


## 1.1.0

- Added the `ScoreDeltaForMidActionSwitch` data member to the `WFBrainComponent` so you can specify how much score delta is good enough to switch from an action to a better one mid-execution. This doesn't affect score comparison for the times that the current action is finished. You can finish actions by calling `ActionBase::Finished()`.
- Added the ability to turn off automatically evaluating action targets and the next action to execute. If you set `WFBrainComponent::bManualExecution` to true then you have to call `WFBrainComponent::Think()` yourself in blueprint or code. This is useful for turn based games or other games which AI calculations are very heavy and are only needed at specific times.