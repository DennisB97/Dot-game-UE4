// Copyright Dennis Bäckström (C) 2021


#include "CoinHolder.h"

// Sets default values
ACoinHolder::ACoinHolder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CoinHolder = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoinHolder"));
	SetRootComponent(CoinHolder);


	// Set correct skeletalmesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> CoinFrameMesh(TEXT("SkeletalMesh'/Game/Assets/Meshes/SK_CoinFrame.SK_CoinFrame'"));

	if (CoinFrameMesh.Succeeded())
	{
		CoinHolder->SetSkeletalMesh(CoinFrameMesh.Object);
	}

	CoinHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CoinHolder->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	CoinHolder->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CoinHolder->SetGenerateOverlapEvents(true);
	CoinHolder->SetCastShadow(false);
	
}

void ACoinHolder::SpawnCoin(const bool bGreen)
{
	bHasCoin = true;
	bIsGreen = bGreen;

}


void ACoinHolder::RemoveCoin()
{
	bHasCoin = false;
}

void ACoinHolder::SetHighlighted(const bool bNewHighlighted)
{

	if (bNewHighlighted)
	{
		if (!EmissiveFrameMaterial)
		{
			EmissiveFrameMaterial = CoinHolder->CreateDynamicMaterialInstance(0, nullptr);
			CoinHolder->SetMaterial(0, EmissiveFrameMaterial);
		}
		

		if (EmissiveFrameMaterial)
		{
			EmissiveFrameMaterial->SetScalarParameterValue("EmissiveValue", 100.0f);
		}
			
	}


	else
	{
		if (EmissiveFrameMaterial)
		{
			EmissiveFrameMaterial->SetScalarParameterValue("EmissiveValue", 0.0f);
		}
	}





}

const bool ACoinHolder::CheckIfCorrectCoin(const bool bGreenClick) const
{


	if ((!bIsGreen && bGreenClick) || (bIsGreen && !bGreenClick))
	{
		return false;
	}

	else
	{
		return true;
	}




}


const bool ACoinHolder::HasCoin() const
{
	return bHasCoin; 
}

// Called when the game starts or when spawned
void ACoinHolder::BeginPlay()
{
	Super::BeginPlay();

}



