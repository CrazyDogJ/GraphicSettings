// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoundClassDescription.h"
#include "UObject/Object.h"
#include "GraphicSettingsUtil.generated.h"

UENUM(BlueprintType)
enum class EGraphicsRHI : uint8
{
	RHI_DX11	UMETA(DisplayName="Direct-X 11"),
	RHI_DX12	UMETA(DisplayName="Direct-X 12"),
	RHI_VULKAN	UMETA(DisplayName="Vulkan")
};

UENUM(BlueprintType)
enum class EGraphicScalabilityType : uint8
{
	GST_ViewDistanceQuality			UMETA(DisplayName="View Distance Quality"),
	GST_AntiAliasingQuality			UMETA(DisplayName="Anti Aliasing Quality"),
	GST_ShadowQuality				UMETA(DisplayName="Shadow Quality"),
	GST_GlobalIlluminationQuality	UMETA(DisplayName="Global Illumination Quality"),
	GST_ReflectionQuality			UMETA(DisplayName="Reflection Quality"),
	GST_PostProcessingQuality		UMETA(DisplayName="Post Processing Quality"),
	GST_TextureQuality				UMETA(DisplayName="Texture Quality"),
	GST_EffectQuality				UMETA(DisplayName="Effect Quality"),
	GST_FoliageQuality				UMETA(DisplayName="Foliage Quality"),
	GST_ShadingQuality				UMETA(DisplayName="Shading Quality")
};

DECLARE_DYNAMIC_DELEGATE(FOnCultureChanged);

UCLASS()
class GRAPHICSETTINGS_API UGraphicSettingsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "User Settings")
	static EPerQualityLevels GetGraphicSettingLevel(EGraphicScalabilityType GraphicType);

	UFUNCTION(BlueprintCallable, Category = "User Settings")
	static void SetGraphicSettingLevel(EGraphicScalabilityType GraphicType, EPerQualityLevels QualityLevel);

	UFUNCTION(BlueprintPure, Category = "User Settings")
	static FText GetGraphicScalabilityTypeText(EGraphicScalabilityType GraphicType);
	
	UFUNCTION(BlueprintCallable, Category = "User Settings")
	static void AssignCultureChangedEvent(FOnCultureChanged ChangedEvent);

	UFUNCTION(BlueprintPure, Category = "User Settings")
	static void GetSoundClasses(TMap<FName, FSoundClassSettingDescription>& Output);

	UFUNCTION(BlueprintCallable, Category = "User Settings")
	static void SetGraphicsRHI(EGraphicsRHI GraphicsRHI);

	UFUNCTION(BlueprintPure, BlueprintPure, Category = "User Settings")
	static EGraphicsRHI GetCurrentGraphicsRHI();
};
