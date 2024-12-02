// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spire.h"
#include "SpirePlayer.h"
#include "CharCreator.generated.h"

USTRUCT(BlueprintType)
struct FPortraits
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<UTexture2D*> portraits{};
};

UCLASS()
class THESPIRE_API ACharCreator : public AActor
{
	GENERATED_BODY()

protected:

	// Main directories.

	FString dataDir{};
	FString raceDir{};
	FString rStatsDir{};
	FString classDir{};
	FString classStatsDir{};

	TMap<TCHAR, int> modInt
	{
		{'+', 2},
		{'0', 0},
		{'-', -2}
	};

	virtual void BeginPlay() override;

	// Defaults.

	void PopulateRaceDefaults();
	void PopulateClassDefaults();
	void PopulateStatDefaults();

	// Data

	void ReadRaces();
	void ReadClasses();

	// Utility.

	void CreateDirectory(FString dirName);
	void MakeTextFile(FString content, FString filePath);
	FStatBlock MakeStatBlock(FString content);
	void MakeRace(FString raceFile, FString statsFile);
	void MakeClass(FString classFile, FString statsFile);
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FPortraits> portraitList{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FName> raceNames{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FName> classNames{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FRace> raceRegistry{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FBackground> classRegistry{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FStatBlock bonus{};

	ACharCreator();
	virtual void Tick(float DeltaTime) override;
	void InitializeDataFiles();
};
