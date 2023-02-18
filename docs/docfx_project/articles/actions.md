# Actions

Actions are the most important part of a utility AI system alongside considerations.
An action is a concrete and most of the time atomic unit of work which an agent can do. Shoot, Find health pack, Find cover, Take cover in the found cover, eat food and Choose the best camera to shot the scene with are all examples of actions.
However action doesn't have to be low level and can be pretty high level, you can have a hierarchy of them in your game and for example have a set of actions for groups of NPCs which can be attack the target, spread members in the room, defend sensitive points, find weak spots by bombing every place and then some NPC actions which take command from the group so when the group chooses to attack the target, a member NPC might execute its shoot action or move toward target action or even cover the attackers action.

To create an action and add it to an action set in an agent behavior asset:

- Create a class derived from [ActionBase](xref:NoOpArmy.WiseFeline.ActionBase).
- Name the action class and its file the same.
- Select an agent behavior asset and open the *Window>NoOpArmy>WiseFeline* window.
- Select an action set and then click add action and choose the action you created.

Here is an example action for going toward a food which should be saved at `GoTowardFood.cs`

```
public class GoTowardFood : ActionBase
{
    private CatBehavior behavior;

    protected override void OnInitialized()
    {
        base.OnInitialized();
        behavior = Brain.GetComponent<CatBehavior>();
    }

    protected override void OnStart()
    {
        base.OnStart();
        behavior.GetComponent<MeshRenderer>().material.color = Color.cyan;//for visualization purposes only
    }

    protected override void UpdateTargets()
    {
        ClearTargets();
        AddTargets(FoodManager.instance.foods);//FoodManager has the list of all foods in the world
    }

    protected override void OnUpdate()
    {
        base.OnUpdate();
        behavior.IncreaseHunger(0.01f * Time.deltaTime);
        behavior.IncreasePlayfulness(0.05f * Time.deltaTime);
        var foodPos = ChosenTarget.transform.position;//chosenTarget is the best food target found by scoring
        behavior.MoveTowardPosition(foodPos);
    }
}
```

There are several things to note:

First of all there are two types of actions, targeted and none-targeted. Targeted ones are those which work on a target like shoot and eat pack. This action is targeted.
None-targeted ones are those which don't have a target like idle or useHealthPackFromInventory. 

Second there are a set of callbacks in an action which you can override. `Initialize()` is called as soon as the action is added to the brain or in the first frame if the behavior is in the brain when the game object is created.
Update, LateUpdate, FixedUpdate, Start and .. are called in the same `MonoBehaviour` callbacks from the brain. 
If the action is targeted then the `chosenTarget` field has the best target in it which you should shoot at, eat or move toward or whatever which is right for your action.
An action becomes a targeted one if at least one of its [considerations](considerations.md) are targeted and have the has target checkbox checked inthe Wise Feline window.
A targeted action means all considerations are calculated for all targets which you gave to the action in the `UpdateTargets()` callback and the one with the highest score is in the `chosenTarget` field.
`UpdateTargets()` is called once per update target operation which its frequency is chosen in the `brain` component.
The scores are calculated once per think operation which is again their frequency is chosen in the brain component.
Here you just define how the action will execute and that's it.

As you can see, to access the component attached to your game object, you can get them from the `brain` component of your game object which is passed to you in `OnInitialize()`.
When filling the list of targets, you can fill it with whatever component type and you can find them using any method you want.
We have a set of utility methods in the [Search](xref:NoOpArmy.WiseFeline.Search) class but you don't have to use them and are not encouraged to do so either.
They are simple wrappers on top of unity's raycasting functionality which work fine for simpler games and samples but for games with huge worlds and lots of agents, you should probably use custom data structures.
We will probably release helper modules for these later on.
You don't have to clear and rebuild the list of targets every time either but in that case you should be careful to not add something multiple times and also to remove objects which are not good target candidates as well.
Also if your action does not need any targets, You don't need to add any targets in `UpdateTargets()`.

For more information, see the API reference for the <xref:NoOpArmy.WiseFeline.ActionBase> class.