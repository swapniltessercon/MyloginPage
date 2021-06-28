// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginWidget.h"
#include "LoginMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API ULoginMenuWidget : public ULoginWidget
{
	GENERATED_BODY()

public:
	ULoginMenuWidget();
	


private:
	TSubclassOf<UUserWidget> FriendListClass;
	
};
