// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicProjectSettings.h"

USoundClassDescription* UGraphicProjectSettings::GetSoundClassDescDataAsset()
{
	return SoundClassDescDataAsset.LoadSynchronous();
}
