// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundClassDescription.h"
#include "UObject/Object.h"
#include "GraphicProjectSettings.generated.h"

UCLASS(Config = Game, DefaultConfig)
class GRAPHICSETTINGS_API UGraphicProjectSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	TSoftObjectPtr<USoundClassDescription> SoundClassDescDataAsset;

	USoundClassDescription* GetSoundClassDescDataAsset();
};
