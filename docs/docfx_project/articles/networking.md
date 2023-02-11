# Networking

The networking features of Unreal work well with our Utility AI system.
No AI runs on any actor which has a role other than `ROLE_AUTHORITY`.
It means client only and server actors in multiplayer games and all actors in standalone games run their UtilityAI logic but simulated and autonomous proxies don't run utility AI and instead receive replicated properties and RPCs from the server version of the actor.

Since actions are `UObject`s and not components or actors, they cannot call RPCs and replicating their properties would become very inefficient.
Usually your actions call code in your main actor object or the components attached to it and those components/the actor can easily call RPCs and replicate properties from the server to the client.

If you have an actor which is only available in a client and not spawned on the server then this actor can have its own AI and its role is `ROLE_AUTHORITY` on the client which spawned it. This actor doesn't get spawned on other players machines or the server and cannot call RPCs/replicate properties but can do anything you need client side.
For example if you have a utility AI system for the lights in your level which doesn't need to be replicated from the server then you can use client only actors for it.