// Copyright Epic Games, Inc. All Rights Reserved.

#include "GraphicSettings.h"

#include "GraphicProjectSettings.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif

#define LOCTEXT_NAMESPACE "FGraphicSettingsModule"

void FGraphicSettingsModule::StartupModule()
{
#if WITH_EDITOR
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "GraphicSettings",
			LOCTEXT("GraphicSettingsName", "Graphic Settings"),
			LOCTEXT("GraphicSettingsDescription", "Configure the Graphic Settings settings."),
			GetMutableDefault<UGraphicProjectSettings>()
		);
	}
#endif
}

void FGraphicSettingsModule::ShutdownModule()
{
#if WITH_EDITOR
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "GraphicSettings");
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGraphicSettingsModule, GraphicSettings)