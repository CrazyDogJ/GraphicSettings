// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicSettingsUtil.h"

#include "GraphicProjectSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

EPerQualityLevels UGraphicSettingsBlueprintFunctionLibrary::GetGraphicSettingLevel(
	EGraphicScalabilityType GraphicType)
{
	const auto GameUserSettings = GEngine->GetGameUserSettings();
	int32 Quality;
	switch (GraphicType)
	{
	case EGraphicScalabilityType::GST_ViewDistanceQuality: Quality = GameUserSettings->GetViewDistanceQuality();
		break;
	case EGraphicScalabilityType::GST_AntiAliasingQuality: Quality = GameUserSettings->GetAntiAliasingQuality();
		break;
	case EGraphicScalabilityType::GST_ShadowQuality: Quality = GameUserSettings->GetShadowQuality();
		break;
	case EGraphicScalabilityType::GST_GlobalIlluminationQuality: Quality = GameUserSettings->GetGlobalIlluminationQuality();
		break;
	case EGraphicScalabilityType::GST_ReflectionQuality: Quality = GameUserSettings->GetReflectionQuality();
		break;
	case EGraphicScalabilityType::GST_PostProcessingQuality: Quality = GameUserSettings->GetPostProcessingQuality();
		break;
	case EGraphicScalabilityType::GST_TextureQuality: Quality = GameUserSettings->GetTextureQuality();
		break;
	case EGraphicScalabilityType::GST_EffectQuality: Quality = GameUserSettings->GetVisualEffectQuality();
		break;
	case EGraphicScalabilityType::GST_FoliageQuality: Quality = GameUserSettings->GetFoliageQuality();
		break;
	case EGraphicScalabilityType::GST_ShadingQuality: Quality = GameUserSettings->GetShadingQuality();
		break;
	default: Quality = 5;
	}
	
	return static_cast<EPerQualityLevels>(Quality);
}

void UGraphicSettingsBlueprintFunctionLibrary::SetGraphicSettingLevel(EGraphicScalabilityType GraphicType,
	EPerQualityLevels QualityLevel)
{
	const auto GameUserSettings = GEngine->GetGameUserSettings();
	switch (GraphicType)
	{
	case EGraphicScalabilityType::GST_ViewDistanceQuality: GameUserSettings->SetViewDistanceQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_AntiAliasingQuality: GameUserSettings->SetAntiAliasingQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_ShadowQuality: GameUserSettings->SetShadowQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_GlobalIlluminationQuality: GameUserSettings->SetGlobalIlluminationQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_ReflectionQuality: GameUserSettings->SetReflectionQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_PostProcessingQuality: GameUserSettings->SetPostProcessingQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_TextureQuality: GameUserSettings->SetTextureQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_EffectQuality: GameUserSettings->SetVisualEffectQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_FoliageQuality: GameUserSettings->SetFoliageQuality((int32)QualityLevel);
		break;
	case EGraphicScalabilityType::GST_ShadingQuality: GameUserSettings->SetShadingQuality((int32)QualityLevel);
		break;
	default: ;
	}
}

FText UGraphicSettingsBlueprintFunctionLibrary::GetGraphicScalabilityTypeText(EGraphicScalabilityType GraphicType)
{
	FText Result;
	switch (GraphicType) {
	case EGraphicScalabilityType::GST_ViewDistanceQuality: Result = NSLOCTEXT("Scalability", "ViewDistanceQuality", "View Distance Quality");
		break;
	case EGraphicScalabilityType::GST_AntiAliasingQuality: Result = NSLOCTEXT("Scalability", "AntiAliasingQuality", "Anti Aliasing Quality");
		break;
	case EGraphicScalabilityType::GST_ShadowQuality: Result = NSLOCTEXT("Scalability", "ShadowQuality", "Shadow Quality");
		break;
	case EGraphicScalabilityType::GST_GlobalIlluminationQuality: Result = NSLOCTEXT("Scalability", "GlobalIlluminationQuality", "Global Illumination Quality");
		break;
	case EGraphicScalabilityType::GST_ReflectionQuality: Result = NSLOCTEXT("Scalability", "ReflectionQuality", "Reflection Quality");
		break;
	case EGraphicScalabilityType::GST_PostProcessingQuality: Result = NSLOCTEXT("Scalability", "PostProcessQuality", "Post Process Quality");
		break;
	case EGraphicScalabilityType::GST_TextureQuality: Result = NSLOCTEXT("Scalability", "TextureQuality", "Texture Quality");
		break;
	case EGraphicScalabilityType::GST_EffectQuality: Result = NSLOCTEXT("Scalability", "EffectsQuality", "Effects Quality");
		break;
	case EGraphicScalabilityType::GST_FoliageQuality: Result = NSLOCTEXT("Scalability", "FoliageQuality", "Foliage Quality");
		break;
	case EGraphicScalabilityType::GST_ShadingQuality: Result = NSLOCTEXT("Scalability", "ShadingQuality", "Shading Quality");
		break;
	}

	return Result;
}

void UGraphicSettingsBlueprintFunctionLibrary::AssignCultureChangedEvent(FOnCultureChanged ChangedEvent)
{
	FInternationalization::Get().OnCultureChanged().AddLambda([ChangedEvent]()
	{
		// ReSharper disable once CppExpressionWithoutSideEffects
		ChangedEvent.ExecuteIfBound();
	});
}

void UGraphicSettingsBlueprintFunctionLibrary::GetSoundClasses(TMap<FName, FSoundClassSettingDescription>& Output)
{
	if (const auto Settings = GetMutableDefault<UGraphicProjectSettings>())
	{
		if (const auto DA = Settings->GetSoundClassDescDataAsset())
		{
			Output = DA->SoundClassDescriptions;
		}
	}
}

void UGraphicSettingsBlueprintFunctionLibrary::SetGraphicsRHI(EGraphicsRHI GraphicsRHI)
{
	FString TargetPlatform = UGameplayStatics::GetPlatformName();
	FString DefaultGraphicsRHI;
	FString RHI_DX11(TEXT("DefaultGraphicsRHI_DX11"));
	FString RHI_DX12(TEXT("DefaultGraphicsRHI_DX12"));
	FString RHI_VULKAN(TEXT("DefaultGraphicsRHI_Vulkan"));

	if (TargetPlatform == "Windows")
	{
		GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), DefaultGraphicsRHI, GEngineIni);
		switch (GraphicsRHI)
		{
		case EGraphicsRHI::RHI_DX11 :
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_DX11")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_DX11, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;

		case EGraphicsRHI::RHI_DX12 :
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_DX12")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_DX12, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;

		case EGraphicsRHI::RHI_VULKAN :
			if (DefaultGraphicsRHI != "DefaultGraphicsRHI_Vulkan")
			{
				GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), *RHI_VULKAN, GEngineIni);
				GConfig->Flush(true, GEngineIni);
				return;
			}
			return;
		}
	}
}

EGraphicsRHI UGraphicSettingsBlueprintFunctionLibrary::GetCurrentGraphicsRHI()
{
	FString TargetPlatform = UGameplayStatics::GetPlatformName();
    FString DefaultGraphicsRHI;
    
    GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), DefaultGraphicsRHI, GEngineIni);
    
    if (DefaultGraphicsRHI == "DefaultGraphicsRHI_DX11")
    {
    	return EGraphicsRHI::RHI_DX11;
    }
    else if (DefaultGraphicsRHI == "DefaultGraphicsRHI_DX12")
    {
    	return EGraphicsRHI::RHI_DX12;
    }
    return EGraphicsRHI::RHI_VULKAN;
}
