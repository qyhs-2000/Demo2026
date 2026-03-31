// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WuwaWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WuwaBlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "DebugHelper.h"

void AWuwaWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

AWuwaWeaponBase::AWuwaWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));

	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void AWuwaWeaponBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//UpdateCollisionBoxAttach();

	PrimaryActorTick.bCanEverTick = bDrawCollisionBox;
}

UMeshComponent* AWuwaWeaponBase::GetMesh()
{
	return nullptr;
}

void AWuwaWeaponBase::ToggleWeaponCollision(ECollisionEnabled::Type CollisionType)
{
	WeaponCollisionBox->SetCollisionEnabled(CollisionType);
}

void AWuwaWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bDrawCollisionBox )
	{
		// 获取碰撞盒的变换
		FTransform BoxTransform = WeaponCollisionBox->GetComponentTransform();
		FVector Extent = WeaponCollisionBox->GetScaledBoxExtent();

		FColor DrawColor = HasAuthority() ? FColor::Green : FColor::Red;
		// 绘制盒子
		DrawDebugBox(
			GetWorld(),
			BoxTransform.GetLocation(),
			Extent,
			BoxTransform.GetRotation(),
			DrawColor,
			false,  // 不持久
			-1.0f,  // 每帧绘制
			0,      // 深度优先级
			2.0f    // 线粗
		);

		if (HasAuthority())
		{
			//debug::Print(FString::Printf(TEXT("%s"), *WeaponCollisionBox->GetAttachParent()->GetName()));
			//debug::Print(FString::Printf(TEXT("%f  , %f   ,%f"), BoxTransform.GetLocation().X, BoxTransform.GetLocation().Y, BoxTransform.GetLocation().Z));
		}
	}
	
}

void AWuwaWeaponBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWuwaWeaponBase, bIsSkeletalMesh);
}

void AWuwaWeaponBase::HitActor(AActor* HitActor)
{
	APawn* HitPawn = Cast<APawn>(HitActor);
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	if (UWuwaBlueprintFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
	{
		if (WeaponOwningPawn != HitPawn)
		{

			OnWeaponHitTarget.ExecuteIfBound(HitActor);
			debug::Print(FString::Printf(TEXT("%s On Begin Overlap %s"), *GetActorNameOrLabel(), *HitActor->GetActorNameOrLabel()));

		}

	}
}

FVector AWuwaWeaponBase::GetSocketLocation(FName SocketName)
{
	return GetMesh()?GetMesh()->GetSocketLocation(SocketName):FVector::Zero();
}



void AWuwaWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APawn* HitPawn = Cast<APawn>(OtherActor);
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	if (UWuwaBlueprintFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
			//debug::Print(FString::Printf(TEXT("%s On Begin Overlap %s"), *GetActorNameOrLabel(), *OtherActor->GetActorNameOrLabel()));

		}

	}
}

void AWuwaWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* HitPawn = Cast<APawn>(OtherActor);
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	if (UWuwaBlueprintFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponPullFromTarget.ExecuteIfBound(OtherActor);
			//debug::Print(FString::Printf(TEXT("%s On End Overlap %s"), *GetActorNameOrLabel(), *OtherActor->GetActorNameOrLabel()));

		}

	}

}

void AWuwaWeaponBase::OnRep_IsSkeletalMesh()
{
	
}

