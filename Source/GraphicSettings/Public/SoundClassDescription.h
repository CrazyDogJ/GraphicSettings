// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundClassDescription.generated.h"

USTRUCT(BlueprintType)
struct FSoundClassSettingDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundClass* SoundClass = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText DisplayDescription;
};

UCLASS()
class GRAPHICSETTINGS_API USoundClassDescription : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Project default sound mix class. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USoundMix* MasterSoundMix;

	/** Project default sound classes*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FName, FSoundClassSettingDescription> SoundClassDescriptions;
};
