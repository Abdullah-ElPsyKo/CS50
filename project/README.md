# Language Assistant
#### Video Demo:  https://youtu.be/dDuZqCGz4Gk
#### Description:
## Introduction

As my final project for CS50 I decided to work on a translation app. This application is a Windows Forms app developed using C#. Users can manually enter words or sentences to be translated into various available languages. The user can also instead of manually typing the words or sentences, let the app extract the text from your clipboard and translate it which would spare you extra clicks. The app allows you also to save/remove your translations.

## Features

1. Manual translation: User can manually input words or sentences and select the desired language they want to translate it to.
2. Clipboard translation: Users can copy text from external sources to their clipboard and use the app by clicking on the "clipboard" button and translating it directly which saves the user a few clicks.
3. Language selection: The user can select from a wide range of languages for the translation. In this case I have chosen 23 most popular languages in the world.
4. Save translations: The app allows the user to save translations. This could be beneficial for users who frequently translate certain words or phrases or for users who would like to learn some languages.
5. Remove translations: The app also allows the user to remove translations. This could be useful for users who have succesfully managed to memorise the words or phrases.

## Classes

The app uses 3 essential classes, each serving a specific purpose.

1. FileClass.cs: This class creates two necessary .csv-files where the translations will be stored. It first checks if these files exist, and if not, then it automatically creates them. This class also allows the user to manage data in the 2 files where the translations are stored. It provides functionalities such as saving translations and removing them. Translation removal is implemented using a linear search algorithm.
2. Translator.cs: To achieve accurate translations, this application interacts through this class with the Microsoft Translator API which is hosted on Azure Cloud Platform. Users need to provide a valid Microsoft Translator API Key and the location of resource. This data can be retrieved by signing up on the Azure Cloud Platform and creating a free Translator resource.
3. GetClipContent.cs: This small class extracts the text content from your clipboard.
4. Form1.cs: Here we give all the buttons their functionalities and make them interact with the created classes. The empty functions within this class should not be removed, if removed the program wont run correctly

## Requirements

1. Microsoft Translator API Key: To use the app, you will need a valid microsoft Translator API Key. You can sign up for free on the Azure Cloud Platform and create a free Translator resource to obtain the required API key.
2. Location: The API requires you to specify the region or location of your resource.

## Conclusion

The Language Assistant application is a lightweight tool that can help users to memorize words or phrases. With its user-friendly interface users can learn and understand various languages more efficiently, making the learning proces even more efficient. The application is pretty minimalistic which makes the experience pretty enjoyable.