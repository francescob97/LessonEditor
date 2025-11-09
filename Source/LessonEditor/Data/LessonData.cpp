// Fill out your copyright notice in the Description page of Project Settings.


#include "LessonData.h"
#include "XmlFile.h"
#include "XmlNode.h"

bool ULessonData::LoadFromXML(const FString& FilePath)
{
    FString XMLContent;

    if (!FFileHelper::LoadFileToString(XMLContent, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Impossibile caricare il file: %s"), *FilePath);
        return false;
    }

    FXmlFile XmlFile(XMLContent, EConstructMethod::ConstructFromBuffer);

    if (!XmlFile.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("XML non valido!"));
        return false;
    }

    FXmlNode* RootNode = XmlFile.GetRootNode();
    if (!RootNode || RootNode->GetTag() != TEXT("Lesson"))
    {
        UE_LOG(LogTemp, Error, TEXT("Nodo root <Lesson> non trovato!"));
        return false;
    }

    // Parse dei nodi figli
    const TArray<FXmlNode*>& ChildNodes = RootNode->GetChildrenNodes();
    for (FXmlNode* ChildNode : ChildNodes)
    {
        const FString& Tag = ChildNode->GetTag();

        if (Tag == TEXT("ID"))
        {
            LessonID = FCString::Atoi(*ChildNode->GetContent());
        }
        else if (Tag == TEXT("Name"))
        {
            LessonName = ChildNode->GetContent();
        }
        else if (Tag == TEXT("Mode"))
        {
            LessonMode = ChildNode->GetContent();
        }
        else if (Tag == TEXT("Properties"))
        {
            const TArray<FXmlNode*>& PropNodes = ChildNode->GetChildrenNodes();
            for (FXmlNode* PropNode : PropNodes)
            {
                const FString& PropTag = PropNode->GetTag();

                if (PropTag == TEXT("Author"))
                {
                    Properties.Author = PropNode->GetContent();
                }
                else if (PropTag == TEXT("Description"))
                {
                    Properties.Description = PropNode->GetContent();
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Lezione caricata: ID=%d, Nome=%s, Modalità=%s"),
        LessonID, *LessonName, *LessonMode);

    return true;
}

bool ULessonData::SaveToXML(const FString& FilePath)
{
    FString XMLContent = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    XMLContent += TEXT("<Lesson>\n");
    XMLContent += FString::Printf(TEXT("    <ID>%d</ID>\n"), LessonID);
    XMLContent += FString::Printf(TEXT("    <Name>%s</Name>\n"), *LessonName);
    XMLContent += FString::Printf(TEXT("    <Mode>%s</Mode>\n"), *LessonMode);
    XMLContent += TEXT("    <Properties>\n");
    XMLContent += FString::Printf(TEXT("        <Author>%s</Author>\n"), *Properties.Author);
    XMLContent += FString::Printf(TEXT("        <Description>%s</Description>\n"), *Properties.Description);
    XMLContent += TEXT("    </Properties>\n");
    XMLContent += TEXT("</Lesson>\n");

    if (FFileHelper::SaveStringToFile(XMLContent, *FilePath))
    {
        UE_LOG(LogTemp, Log, TEXT("Lezione salvata in: %s"), *FilePath);
        return true;
    }

    UE_LOG(LogTemp, Error, TEXT("Impossibile salvare il file: %s"), *FilePath);
    return false;
}
