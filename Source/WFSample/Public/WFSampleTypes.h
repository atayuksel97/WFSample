/***************************************************************************************/
/* Copyright (c) 2023 NoOp Army. All rights reserved. */
/* Written by Shayan Zamiri <support@nooparmygames.com> */
/* Author's twitter: @Shayan_Zamiri */
/***************************************************************************************/

#pragma once

#define WFSAMPLE_TRACE_FUNCTION() TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCSIG__)

#define COLLISION_WEAPON	ECC_GameTraceChannel1

DECLARE_STATS_GROUP(TEXT("WFSample"), STATGROUP_WFSample, STATCAT_Advanced);