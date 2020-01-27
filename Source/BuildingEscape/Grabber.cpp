// Copyright Yuriy Levchuk 2020.


#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"))

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()))
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Player location: %s, rotation: %s."), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 2.0f);

	
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(HitActor->GetName()))
	}
}

