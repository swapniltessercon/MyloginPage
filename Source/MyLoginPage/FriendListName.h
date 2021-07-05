// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FriendListName.generated.h"

/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API UFriendListName : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(class ULoginMenuWidget* Parent, uint32 Index);
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FriendName;

	UPROPERTY(meta = (BindWidget))
	class UImage* FriendImage;

	UFUNCTION()
	void OnSetImage(UTexture2DDynamic* Texture);

private:
	uint32 Index;
	UPROPERTY(meta = (BindWidget))
	class UButton* FriendButton;

	UPROPERTY()
	class ULoginMenuWidget* Parent;

	UFUNCTION()
	void OnFriendButtonClicked();

};
