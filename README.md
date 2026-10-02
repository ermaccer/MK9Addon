# MK9Addon

A plugin for Mortal Kombat Komplete Edition to add features and patch stuff.

# Features

## Loose MKO loading

MK9 supports loading .mko files from MKScript folder, however unlike future games this won't work if archive has MKO bundled in. Behaviour is changed to check for loose .MKO in MKScript first and load it.

## Stage List editor

Hardcoded stage lists can be easily edited from text .cfg files stored in Data folder. Ladder pool and Select pool can be edited here, note that Select pool doesn't immediately mean the stage will be 100% recognized by select (PlayerSelect.mko has its own internal list). Ladder list also applies to attract mode.

## Kratos PC support

Removes multiple blacklists put in place to stop Kratos from loading or being accessible in game. Added support for ladder randomization, Nekropolis and Kratos specific fatalities. The fatalities are automatically picked as long as Kratos is the victim and `_Kratos` fatality archive exists.

## Misc.

Removes "Khameleon" locked characters entry.

# Installation

####  MK9Addon was only tested with latest Steam version!

You can download binary files from [Releases](https://github.com/ermaccer/MK9Addon/releases) page. Extract **mk9addon.zip**
to DiscContentPC folder of Mortal Kombat 9.

If you are not sure how to find your Mortal Kombat 9 folder, search for it in your Steam library then right click on the entry and select Manage->Browse local files.

Archive breakdown:

 - dinput8.dll - [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/)
 - MK9Addon.asi
 - ``data\*.cfg``- Editable lists
