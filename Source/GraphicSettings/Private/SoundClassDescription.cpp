// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundClassDescription.h"

#if WITH_EDITOR
void USoundClassDescription::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, bRefreshDisplayNameTextKey))
	{
		for (auto& Itr : SoundClassDescriptions)
		{
			Itr.Value.DisplayName = FText::ChangeKey(TEXT("SoundClassDescription"), Itr.Key.ToString() + "Name", Itr.Value.DisplayName);
		}

		bRefreshDisplayNameTextKey = false;
	}

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, bRefreshDisplayDescriptionTextKey))
	{
		for (auto& Itr : SoundClassDescriptions)
		{
			Itr.Value.DisplayDescription = FText::ChangeKey(TEXT("SoundClassDescription"), Itr.Key.ToString() + "Desc", Itr.Value.DisplayDescription);
		}

		bRefreshDisplayNameTextKey = false;
	}
}
#endif