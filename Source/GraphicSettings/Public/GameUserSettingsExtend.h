// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GameUserSettingsExtend.generated.h"

UENUM(BlueprintType)
enum class EGlobalQualityLevels : uint8
{
	Low,
	Medium,
	High,
	Epic,
	Cinematic,
	Custom,
	Num
};

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

	UPROPERTY(config)
	float MotionBlurAmount = 1.0f;

	UPROPERTY(config)
	EGlobalQualityLevels GlobalGraphicQuality = EGlobalQualityLevels::Custom;

	UFUNCTION(BlueprintPure)
	EGlobalQualityLevels GetCurrentGlobalGraphicQuality();

	UFUNCTION(BlueprintPure)
	float GetMotionBlurAmount() const;

	UFUNCTION(BlueprintCallable)
	void SetMotionBlurAmount(float Value);
	
	UFUNCTION(BlueprintCallable)
	void SetGlobalGraphicQuality(EGlobalQualityLevels Value);
	
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
