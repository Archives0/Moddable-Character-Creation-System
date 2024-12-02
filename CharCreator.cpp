// Fill out your copyright notice in the Description page of Project Settings.


#include "CharCreator.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"

// Sets default values
ACharCreator::ACharCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACharCreator::BeginPlay()
{
	Super::BeginPlay();
	InitializeDataFiles();
	ReadRaces();
	ReadClasses();

	UE_LOG(LogTemp, Display, TEXT("Data directory created at: %s"), *dataDir);
}

// Called every frame
void ACharCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// TODO: Test, fix bugs, add variables for UI display. Create registry for quick access to structs via name.
//		 Choose either background or class and stick with it!!

void ACharCreator::InitializeDataFiles()
{
	// Initialize Data directory.

	FString launchDir = FPaths::LaunchDir();
	dataDir = launchDir / "Data";
	raceDir = dataDir / "Races";
	rStatsDir = raceDir / "Stats";
	classDir = dataDir / "Classes";
	classStatsDir = classDir / "Stats";

	CreateDirectory(dataDir);
	CreateDirectory(raceDir);
	CreateDirectory(classDir);
	CreateDirectory(rStatsDir);
	CreateDirectory(classStatsDir);


	PopulateRaceDefaults();
	PopulateClassDefaults();
	PopulateStatDefaults();
}

void ACharCreator::CreateDirectory(FString dirName)
{
	if (!FPaths::DirectoryExists(dirName))								// Check if directory does not exist.
	{
		if (IFileManager::Get().MakeDirectory(*dirName, true))			// Make new directory.
		{
			UE_LOG(LogTemp, Display, TEXT("%s directory created successfully."), *dirName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not create %s directory."), *dirName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s directory already exists."), *dirName);
	}
}

void ACharCreator::PopulateRaceDefaults()
{
	if (!FPaths::DirectoryExists(raceDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Races directory does not exist. Aborting."));
		return;
	}

	TArray<FString> fileNames{};
	IFileManager::Get().FindFiles(fileNames, *raceDir, TEXT("*.txt"));

	// If default file is not present, add it to Data/Races.

	if (!fileNames.Contains("Aktiin.txt"))
	{
		FString name = raceDir / "Aktiin.txt";
		FString description = "The predominant race of the continent Hla'Aktina. Their ingenuity has led to the rapid industrialization of the continent. Receive bonuses to Intelligence and Dexterity.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Aradiin.txt"))
	{
		FString name = raceDir / "Aradiin.txt";
		FString description = "Their durable nature has allowed them to survive many hardships and equips them with ample skill for nearly any situation. Receive bonuses to Dexterity and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Lunath.txt"))
	{
		FString name = raceDir / "Lunath.txt";
		FString description = "Lunathi tend to be unconcerned with life on the ground, with many living in ancient floating cities. Their skill in magic is beaten by none. Receive bonuses to Willpower and Intelligence.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Siron.txt"))
	{
		FString name = raceDir / "Siron.txt";
		FString description = "The predominant race of the eastern continent Enteril. They tend to lead virtuous lives and quest to prove themselves. Receive bonuses to Strength and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Zerath.txt"))
	{
		FString name = raceDir / "Zerath.txt";
		FString description = "Their subterranean lifestyle has made them a widespread race. Most serve as drones, and receive number designations as names. Receive bonuses to Strength and Willpower.";
		MakeTextFile(description, name);
	}
}

void ACharCreator::PopulateClassDefaults()
{
	if (!FPaths::DirectoryExists(classDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> fileNames{};
	IFileManager::Get().FindFiles(fileNames, *classDir, TEXT("*.txt"));

	// If default files not present, add it to Data/Classes

	if (!fileNames.Contains("Bandit.txt"))
	{
		FString name = classDir / "Bandit.txt";
		FString description = "You make your living from taking from others. A life of thuggery has improved your ability to impose yourself over others. Receives bonsues to Strength and Charisma.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Commoner.txt"))
	{
		FString name = classDir / "Commoner.txt";
		FString description = "You have thus led a simple and humble life. Only recently have you started on the path of the ashlander. Receives no bonuses or detriments.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Merchant.txt"))
	{
		FString name = classDir / "Merchant.txt";
		FString description = "You have made your living by selling goods to others, making you skilled in trade. Receives bonuses to Willpower and Charisma.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Noble.txt"))
	{
		FString name = classDir / "Noble.txt";
		FString description = "You have led your life through high society. Your upbringing has made you skilled in socializing and well studied. Receives bonuses to Charisma and Intelligence.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Priest.txt"))
	{
		FString name = classDir / "Priest.txt";
		FString description = "You have lived a pious life in worship of your gods. Their blessings have have taught you to be resistant to the will of others. Receives bonuses to Willpower and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Scholar.txt"))
	{
		FString name = classDir / "Scholar.txt";
		FString description = "You have dedicated much of your life to intellectual pursuits. Your studies have familiarized you with magic and its workings. Receives bonuses to Intelligence and Willpower.";
		MakeTextFile(description, name);
	}
}

void ACharCreator::PopulateStatDefaults()
{
	// Populate race stat bonuses.

	if (!FPaths::DirectoryExists(rStatsDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Race stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> rNames{};
	IFileManager::Get().FindFiles(rNames, *rStatsDir, TEXT("*.txt"));

	// If default file is not present, add it to Data/Races/Stats.

	if (!rNames.Contains("Aktiin.txt"))
	{
		FString name = rStatsDir / "Aktiin.txt";
		FString description = "0|0|+|+|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Aradiin.txt"))
	{
		FString name = rStatsDir / "Aradiin.txt";
		FString description = "0|+|+|0|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Lunath.txt"))
	{
		FString name = rStatsDir / "Lunath.txt";
		FString description = "0|0|0|+|+|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Siron.txt"))
	{
		FString name = rStatsDir / "Siron.txt";
		FString description = "+|+|0|0|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Zerath.txt"))
	{
		FString name = rStatsDir / "Zerath.txt";
		FString description = "+|0|0|0|+|0";
		MakeTextFile(description, name);
	}

	// Populate class stat bonuses.

	if (!FPaths::DirectoryExists(classStatsDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Background stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> cNames{};
	IFileManager::Get().FindFiles(cNames, *classStatsDir, TEXT("*.txt"));

	// If defualt file is not present, add it to Data/Classes/Stats

	if (!cNames.Contains("Bandit.txt"))
	{
		FString name = classStatsDir / "Bandit.txt";
		FString description = "0|0|+|0|0|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Commoner.txt"))
	{
		FString name = classStatsDir / "Commoner.txt";
		FString description = "0|0|0|0|0|0";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Merchant.txt"))
	{
		FString name = classStatsDir / "Merchant.txt";
		FString description = "0|0|0|0|+|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Noble.txt"))
	{
		FString name = classStatsDir / "Noble.txt";
		FString description = "0|0|0|+|0|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Priest.txt"))
	{
		FString name = classStatsDir / "Priest.txt";
		FString description = "0|0|0|0|+|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Scholar.txt"))
	{
		FString name = classStatsDir / "Scholar.txt";
		FString description = "0|0|0|+|+|0";
		MakeTextFile(description, name);
	}
}

void ACharCreator::ReadRaces()
{
	// Get all files, read to content, parse, add to array as names.

	// Get list of race file names and stat file names.

	TArray<FString> rNames{};
	IFileManager::Get().FindFiles(rNames, *raceDir, TEXT("*.txt"));

	// Remove extension, then add to race names array. Used for UI display purposes.

	for (FString name : rNames)
	{
		FString newName = name;
		newName.RemoveFromEnd(TEXT(".txt"));
		FName raceName = FName(*newName);
		raceNames.Add(raceName);
	}

	// Create FRace for each race in Data/Races and add to races array.

	TArray<FString> rStats{};
	IFileManager::Get().FindFiles(rStats, *rStatsDir, TEXT("*.txt"));

	for (FString raceFile : rNames)
	{
		for (FString statFile : rStats)
		{
			if (raceFile == statFile)
			{
				MakeRace(raceFile, statFile);
				break;
			}
		}

		// TODO: If no corresponding stat file is found, give race a default stat block.

		MakeRace(raceFile, "default");
	}
}

void ACharCreator::ReadClasses()
{
	// Get all files, read to content, parse, add to array as names.

	TArray<FString> cNames{};
	IFileManager::Get().FindFiles(cNames, *classDir, TEXT("*.txt"));

	for (FString name : cNames)
	{
		name.RemoveFromEnd(TEXT(".txt"));
		FName bgName = FName(*name);
		classNames.Add(bgName);
	}

	// Create FBackground for each class in Data/Classes and add to classes array.

	TArray<FString> cStats{};
	IFileManager::Get().FindFiles(cStats, *classStatsDir, TEXT("*.txt"));

	for (FString classFile : cNames)
	{
		for (FString statFile : cStats)
		{
			if (classFile == statFile)
			{
				MakeClass(classFile, statFile);
			}
		}

		// If no matching class stat bonus was found, make default class.
		MakeClass(classFile, "default");
	}
}

void ACharCreator::MakeTextFile(FString content, FString filePath)
{
	if (!FFileHelper::SaveStringToFile(content, *filePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create file at %s"), *filePath);
	}
}

FStatBlock ACharCreator::MakeStatBlock(FString content)
{
	TArray<TCHAR> mods{};
	TArray<FString> parsedFile{};

	// Split content on delimiter '|'. 

	content.ParseIntoArray(parsedFile, TEXT("|"));

	for (FString element : parsedFile)
	{
		// If element is recognized, add. If not, replace with 0.

		if (element == TEXT("0") || element == TEXT("+") || element == TEXT("-"))
		{
			mods.Add(element[0]);
		}
		else
		{
			mods.Add('0');
		}
	}

	// Create stat struct and return.
	
	FStatBlock statBlock = FStatBlock
	(
		modInt[mods[0]],
		modInt[mods[1]],
		modInt[mods[2]],
		modInt[mods[3]],
		modInt[mods[4]],
		modInt[mods[5]]
	);
	
	return statBlock;
}

void ACharCreator::MakeRace(FString raceFile, FString statsFile)
{
	// Create race name and load description.

	FString raceName = raceFile;
	FString raceDesc{};
	raceName.RemoveFromEnd(TEXT(".txt"));
	FFileHelper::LoadFileToString(raceDesc, *(raceDir / raceFile));

	//Check if stat directory exists. If true, load. If not, make default stat block.

	FStatBlock raceMod{};

	if (IFileManager::Get().DirectoryExists(*(rStatsDir / statsFile)))
	{
		FString stats{};
		FFileHelper::LoadFileToString(stats, *(rStatsDir / statsFile));
		raceMod = MakeStatBlock(stats);
	}
	else
	{
		raceMod = FStatBlock();
	}

	// Make struct and add to registry.

	FRace race = FRace(FName(raceName), FText::FromString(raceDesc), raceMod);
	raceRegistry.Add(race.name, race);
}

void ACharCreator::MakeClass(FString classFile, FString statsFile)
{
	FString className = classFile;
	FString classDesc{};
	className.RemoveFromEnd(TEXT("*.txt"));
	FFileHelper::LoadFileToString(classDesc, *(classDir / classFile));

	FStatBlock classMod{};

	if (IFileManager::Get().DirectoryExists(*(classStatsDir / classFile)))
	{
		FString stats{};
		FFileHelper::LoadFileToString(stats, *(classStatsDir / statsFile));
		classMod = MakeStatBlock(stats);
	}
	else
	{
		classMod = FStatBlock();
	}

	FBackground background = FBackground(FName(className), FText::FromString(classDesc), classMod);
	classRegistry.Add(background.name, background);
}

