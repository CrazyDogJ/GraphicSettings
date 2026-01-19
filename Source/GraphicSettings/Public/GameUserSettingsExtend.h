// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GameUserSettingsExtend.generated.h"

/**
 * A game user settings that extend some user settings like aa method and sound options and so on.
 */
UCLASS(BlueprintType)
class GRAPHICSETTINGS_API UGameUserSettingsExtend : public UGameUserSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(config)
	uint8 AntiAliasingMethod;

	UPROPERTY(config)
	TMap<FName, float> AudioMixSettings;
	
	UFUNCTION(BlueprintPure)
	EAntiAliasingMethod GetCurrentAntiAliasingMethod();
	
	UFUNCTION(BlueprintCallable)
	void SetAntiAliasingMethod(EAntiAliasingMethod Value);

	void InitSoundSettings(Audio::FDeviceId Id);
	
	virtual void ApplyNonResolutionSettings() override;

	UFUNCTION(BlueprintPure)
	float GetSoundClassVolume(FName SoundClassName);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	void SetSoundClassVolume(UObject* WorldContextObject, FName SoundClassName, float Value);
};
