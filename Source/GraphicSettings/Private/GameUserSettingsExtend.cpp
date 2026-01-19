// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserSettingsExtend.h"

#include "AudioDevice.h"
#include "GraphicProjectSettings.h"
#include "SoundClassDescription.h"

EAntiAliasingMethod UGameUserSettingsExtend::GetCurrentAntiAliasingMethod()
{
	static IConsoleVariable* GetAA = IConsoleManager::Get().FindConsoleVariable(TEXT("r.AntiAliasingMethod"));		
	if (ensure(GetAA))
	{
		AntiAliasingMethod = (uint8)GetAA->GetInt();
	}		
	return (EAntiAliasingMethod)AntiAliasingMethod;
}

void UGameUserSettingsExtend::SetAntiAliasingMethod(EAntiAliasingMethod Value)
{
	static IConsoleVariable* SetAA = IConsoleManager::Get().FindConsoleVariable(TEXT("r.AntiAliasingMethod"));
	if (ensure(SetAA))
	{
		// ECVF_SetByGameSetting , ECVF_SetByCode, ECVF_SetByProjectSetting
		SetAA->Set((uint8)Value, ECVF_SetByGameSetting);
		SetAA->Set((uint8)Value, ECVF_SetByProjectSetting);
	}
	
	static auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.AntiAliasingMethod"));
	CVar->Set(Value, ECVF_SetByGameSetting);
	
	AntiAliasingMethod = (uint8)Value;
}

void UGameUserSettingsExtend::InitSoundSettings(Audio::FDeviceId Id)
{
	if (const auto Settings = GetMutableDefault<UGraphicProjectSettings>())
	{
		if (const auto SoundClassDesc = Settings->GetSoundClassDescDataAsset())
		{
			if (const auto MasterSoundMix = SoundClassDesc->MasterSoundMix)
			{
				for (const auto Itr : AudioMixSettings)
				{
					if (const auto FoundSound = SoundClassDesc->SoundClassDescriptions.Find(Itr.Key))
					{
						for (auto AudioDevice : FAudioDeviceManager::Get()->GetAudioDevices())
						{
							AudioDevice->SetSoundMixClassOverride(MasterSoundMix, FoundSound->SoundClass, Itr.Value, 1.0, 0, true);
						}
					}
				}
			}
		}
	}
}

void UGameUserSettingsExtend::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();

	static auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.AntiAliasingMethod"));
	CVar->Set(AntiAliasingMethod, ECVF_SetByGameSetting);

#if WITH_SHIPPING
	if (FInternationalization::Get().IsInitialized())
	{
		FString Culture;
		GConfig->GetString(TEXT("Internationalization"), TEXT("Culture"), Culture, GGameUserSettingsIni);
		FInternationalization::Get().SetCurrentCulture(Culture);

		FString Language;
		GConfig->GetString(TEXT("Internationalization"), TEXT("Language"), Language, GGameUserSettingsIni);
		FInternationalization::Get().SetCurrentLanguage(Language);

		FString Locale;
		GConfig->GetString(TEXT("Internationalization"), TEXT("Locale"), Locale, GGameUserSettingsIni);
		FInternationalization::Get().SetCurrentLanguage(Locale);
	}

	FAudioDeviceManagerDelegates::OnAudioDeviceCreated.AddLambda([&](Audio::FDeviceId AudioDeviceId)
	{
		InitSoundSettings(AudioDeviceId);
	});
	FAudioDeviceWorldDelegates::OnWorldRegisteredToAudioDevice.AddLambda([&](const UWorld* World, Audio::FDeviceId AudioDeviceId)
	{
		InitSoundSettings(AudioDeviceId);
	});
#endif
}

float UGameUserSettingsExtend::GetSoundClassVolume(FName SoundClassName)
{
	if (const auto Settings = GetMutableDefault<UGraphicProjectSettings>())
	{
		if (const auto SoundClassDesc = Settings->GetSoundClassDescDataAsset())
		{
			if (const auto Found = AudioMixSettings.Find(SoundClassName))
			{
				return *Found;
			}
		}
	}

	// Default is full;
	return 1.0f;
}

void UGameUserSettingsExtend::SetSoundClassVolume(UObject* WorldContextObject, FName SoundClassName, float Value)
{
	if (!WorldContextObject || !WorldContextObject->GetWorld()) return;
	
	if (const auto Settings = GetMutableDefault<UGraphicProjectSettings>())
	{
		if (const auto SoundClassDesc = Settings->GetSoundClassDescDataAsset())
		{
			if (const auto Found = SoundClassDesc->SoundClassDescriptions.Find(SoundClassName))
			{
				if (SoundClassDesc->MasterSoundMix)
				{
					AudioMixSettings.Add(SoundClassName, Value);
					if (FAudioDeviceHandle AudioDevice = WorldContextObject->GetWorld()->AudioDeviceHandle)
					{
						AudioDevice->SetSoundMixClassOverride(SoundClassDesc->MasterSoundMix, Found->SoundClass, Value, 1.0, 1.0, true);
					}
				}
			}
		}
	}
}
