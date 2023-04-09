# Integrating with UE features

You can easily integrate EQS, Blackboards and other UE features to your Utility AI actions and considerations.
The following is a part of move to cover action of the sample.

```
FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EnvQuery, GetControlledActor());
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::AllMatching, this, &UWFAction_MoveToCover::MoveToQueryResult);
```

We did not integrate other features like preception and blackboards into the sample but nothing in Wise Feline takes the ability from you and you don't have to consider anything special or follow any specific rules to do so.