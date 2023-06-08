/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <shayan.zamiri@gmail.com> */
/***************************************************************************************/

using UnrealBuildTool;
using System.Collections.Generic;

public class WFSampleTarget : TargetRules
{
	public WFSampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "WFSample" } );
	}
}