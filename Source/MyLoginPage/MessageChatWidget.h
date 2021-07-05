// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API UMessageChatWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UserMessage;
	
};
