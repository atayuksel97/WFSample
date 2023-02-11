# Considerations

Each action's score is calculated by calculating scores of all of its considerations and then multiplying them with each other.
Considerations are defined in code by deriving from `ConsiderationBase` class. Like components each consideration should be in a file which shares the same name with the consideration class.

After defining a consideration in code, you can add it to actions of a Agent Behavior asset in the wise feline window.

To add considerations to actions

- Implement a consideration in a class. For example create a HungerConsideration.cs file and implement `HungerConsideration` inside it like this. The example code is posted below.
- Select the desired agent behavior asset and open the Wise Feline window at *Window>NoOpArmy>Wise Feline*.
- Select the action which you want to add the consideration to by clicking on it. You might need to select the appropriate action set first.
- Now in the considerations list for the action click Add Consideration and from the context menu choose `HungerConsideration`
- Set the curve and the parameters of the consideration as you desire.

The consideration can be defined like this:

```
public class HungerConsideration : ConsiderationBase
{
    private CatBehavior behavior;

    protected override void OnInitialized()
    {
        base.OnInitialized();
        behavior = Brain.GetComponent<CatBehavior>();
    }

    protected override float GetValue(Component target)
    {
        return behavior.Hunger;
    }
}
```

`OnInitialized()` is called when the consideration is initialized after the `Brain` component is created or the agent behavior asset is added to a brain at runtime.

`GetValue()` is called whenever the action wants to calculate its score.

What you return in GetValue should be a number between 0 and 1 (both inclusive) which will be fed to the curve of the consideration as the value for x axis and the y axis value at that point is the score of the consideration used in score calculations.

For more information, see the API reference for the <xref:NoOpArmy.WiseFeline.ConsiderationBase> class.