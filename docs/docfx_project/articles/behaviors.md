# Wise Feline Behavior asset

An Agent Behavior asset defines a list of actions which are scored and executed when the behavior is attached to a `WFUtilityAIComponent`.
To modify the WF behavior asset you use the behavior editor window.
You can bring the window up by double clicking on a wise feline behavior asset.


To create a new behavior:

- right click in the content browser and go to the Wise Feline menu, then choose *Behavior*.
- Name the behavior whatever you want. Usually this is the name of the agent type or the name of set of behaviors. For example this can be enemy behaviors, forest behaviors or more specifically enemy at forest behaviors.
- Then double click on the the created asset to open the editor window.

Here you can add actions and for each action you can define a set of considerations which effects how the action is scored at each think operation.
Closing the window automatically serializes all changes and saves them to the disk.

# More details

You can attach behavior assets to `WFUtilityAIComponent` components at edit time or add/remove them dynamically at runtime.
Basically this is the data which is used at runtime to see what actions are available to an agent and how each action's score should be calculated.

The `WFUtilityAIComponent` has properties about what behavior assets to use for the actor and how often it should execute the AI and the behavior asset contains what actions are available to execute and how their scores should be calculated.

For more information, checkout the samples