# How to Debug

You can debug your AI scoring by selecting a game object which has a [`Brain`](brain.md) component attached at runtime while the Wise Feline window is open.
The window then shows the list of all action sets and actions available to the agent and shows you what score each of the actions got.
You can also sort the list of actions by score.

The window looks like this 

![Debug Window](../images/debug.png)

As you can see the left most column are the action sets and then you got actions and then considerations.
The window updates whenever scores are updated.