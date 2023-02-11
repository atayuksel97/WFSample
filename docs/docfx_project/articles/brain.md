# Brain component

Brain is the main component in the Wise Feline system which allows you to direct a game object using your Agent Behavior assets.
You should attach this component to any game object which you want to control using utility AI.
The main parameter that the component takes is the Agent Behavior asset to use but there are additional parameters and methods which are discussed in the reference linked below.

Keep in mind that this component allows you to add and remove behaviors at runtime so you can add region specific behaviors or situation specific behaviors when an agent needs to consider them during gameplay.
This makes your job much easier when designing action scores with considerations.
If this feature did not exist you had to have lots of flag considerations with 0 and 1 responses for the times that action was possible or not but thanks to this feature you can simply add jungle specific behaviors to agents only when they enter the jungle zone and remove it when they exit.

The component allows you to choose how often decision making (i.e. action scoring) runs and how often the agent updates its list of targets to consider.
You see this by how often your actions and considerations are called to calculate their scores. However the `Update()`, `FixedUpdate()` and `LateUpdate()` callbacks of your current action with its current target (if applicable) will be called every `Update()`, `FixedUpdate()` and `LateUpdate()` no matter how low or high you set the frequency for thinking or updating targets.

For more information, see the API reference for the <xref:NoOpArmy.WiseFeline.Brain> class.