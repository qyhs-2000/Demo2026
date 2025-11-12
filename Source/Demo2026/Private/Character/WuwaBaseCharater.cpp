// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
// Sets default values
AWuwaBaseCharater::AWuwaBaseCharater()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WuwaAbilitySystemComponent = CreateDefaultSubobject<UWuwaAbilitySystemComponent>(TEXT("WuwaAbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AWuwaBaseCharater::BeginPlay()
{
	Super::BeginPlay();

}

void AWuwaBaseCharater::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(WuwaAbilitySystemComponent)
	{
		WuwaAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void AWuwaBaseCharater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWuwaBaseCharater::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

