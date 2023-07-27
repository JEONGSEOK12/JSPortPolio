// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage_Select/Stage_Plane.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AStage_Plane::AStage_Plane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStage_Plane::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> Findid = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Stage_Plane_1"));
	UCapsuleComponent* FindScene = Cast<UCapsuleComponent>(Findid[0]);
	
	FindScene->OnComponentBeginOverlap.AddDynamic(this, &AStage_Plane::BeginOverlap);
	FindScene->OnComponentEndOverlap.AddDynamic(this, &AStage_Plane::EndOverlap);

	
}

// Called every frame
void AStage_Plane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void AStage_Plane::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if(OtherActor->ActorHasTag(TEXT("Player")))
	{
		
		//UObject* cls = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Game/Stage_Select_Map/BP_Enter_Text.BP_Enter_Text"));
		//UBlueprint* bp = Cast<UBlueprint>(cls);
		//TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;
		//GetWorld()->SpawnActor<AActor>(blockBP, FVector::ZeroVector, FRotator::ZeroRotator);




	}

}

void AStage_Plane::EndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		
	}
}


void AStage_Plane::Hit_Ground()
{
	SetActorLocation(GetActorLocation());
	
}