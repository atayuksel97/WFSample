# Agent Behavior asset

An Agent Behavior asset defines a list of actions which are scored and executed when the behavior is attached to a `Brain` component.
To modify the agent behavior asset you use the Wise Feline window.

To create a new agent behavior:

- right click in the project view and go to the Create menu, then choose *NooPArmy>Wise Feline>Agent Behavior*.
- Name the behavior whatever you want. Usually this is the name of the agent type or the name of set of behaviors. For example this can be enemy behaviors, forest behaviors or more specifically enemy at forest behaviors.
- Then select the created asset and go to the *Window>NoOpArmy>Wise Feline* window.

Now here you can add action sets which behave as folders for organizing your actions.
In each action set you can add actions and for each action you can define a set of considerations which effects how the action is scored at each think operation.
Closing the window automatically serializes all changes and saves them to the disk.

# More details

You can attach agent behavior assets to `Brain` components at edit time or add/remove them dynamically to a `Brain` at runtime.
Basically this is the data which is used at runtime to see what actions are available to an agent and how each action's score should be calculated.

The `Brain` component has properties about what agent behavior assets to use for the game object and how often it should execute the AI and the agent behavior asset contains what actions are available to execute and how their scores should be calculated.

For more information, see the API reference for the <xref:NoOpArmy.WiseFeline.AgentBehavior> class.