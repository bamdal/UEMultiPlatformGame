// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_BlueprintFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Platform/JMS_PlatformGI.h"

// 게임 인스턴스에 캐신된 네트워크 오류가 있는지 체크 / 호스트와의 연결이 끊어지면 발생
bool UJMS_BlueprintFunctionLibrary::IsActiveError(const UObject* WorldContextObject)
{
	
	UJMS_PlatformGI* GI = Cast<UJMS_PlatformGI>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GI == nullptr)
	{
		return true;	// null이면 에러
	}
	
	if (!GI->JMSNetworkError.IsEmpty()&& !GI->JMSTravelError.IsEmpty())
	{
		return true;	// 둘중에 하나라도 뭔가 있다면 에러
	}
	//check(nullptr);

	return false;	// 이상 없음
}
