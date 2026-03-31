// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO2026_API UPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnExtensionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	template<typename T>
	T* GetOwningPawn()
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template paramter must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn()
	{
		return GetOwningPawn<APawn>();
	}

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
