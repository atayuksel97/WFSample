// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define WFSAMPLE_TRACE_FUNCTION() TRACE_CPUPROFILER_EVENT_SCOPE_STR(__FUNCSIG__)

#define COLLISION_WEAPON	ECC_GameTraceChannel1

DECLARE_STATS_GROUP(TEXT("WFSample"), STATGROUP_WFSample, STATCAT_Advanced);