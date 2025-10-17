# SRPG-ToolBox — SRPG Unpacker

SRPG Unpacker is a small tool to unpack and repack SRPG Studio `.dts` archives, reconstruct `.srpgs` project files, and create as well as apply translation patches against project data.
It is primarily intended for the translation of SRPG Studio games.

SRPG Studio up to version 1.317 is supported.

## Features

- Unpack `.dts` archives into a reconstructed project folder (including `project.dat`, `project.srpgs`, and resources)
- Repack an unpacked folder back into a `.dts` archive
- Create and apply translation patches against `project.dat`

## Quick usage

For unpacking and repacking drag & drop behavior is supported, alternatively the tool can run from the command line, e.g.:

- Unpack a `.dts` file (default output folder: `output`):

  `SRPG_Unpacker.exe "C:\path\to\data.dts"`

- Pack a folder back into a `.dts` file (default output file: `output.dts`):

  `SRPG_Unpacker.exe "C:\path\to\extracted_folder"`

- Specify an output path:

  `SRPG_Unpacker.exe "C:\path\to\data.dts" -o "C:\out\my_project"`

- Create a translation patch from `project.dat`:

  `SRPG_Unpacker.exe "C:\path\to\project.dat" -c -o "C:\out\patch_folder"`

- Apply a translation patch to `project.dat`:

  `SRPG_Unpacker.exe "C:\path\to\project.dat" -a -o "C:\out\patch_folder"`

For all available options check the built-in help (`SRPG_Unpacker.exe --help`).

## Notes regarding the translation files

- When a translation patch is created the tool will extract all text data from the `project.dat` file and store it the form of several JSON files inside the patch folder.
- The structure of these files is highly inspired by the localization format used by SRPG Studio itself, with the exception that individual maps are not split into multiple files but rather stored in a single `map_<map_id>.json` file for easier management.
- Furthermore, event content is also not stored in txt files but directly inside the respective JSON files.
- Finally, the `speaker` field for messages is a custom addition for the sole purpose of making it easier to identify who is speaking in dialogues during translation; this field is ignored when applying the patch.

## Building from source

Requirements:

- Windows (tested on Windows 10/11)
- Visual Studio 2022

Steps:

1. Open `SRPG_Unpacker/SRPG_Unpacker.sln` in Visual Studio.
2. Select the desired Configuration and Platform, e.g., `Release` and `x64`.
3. Build the solution.

## Known issues / limitations

- Not all project classes and commands are currently implemented. Should you encounter an unimplemented feature, please open an issue with details, including the name of the game.
- Depending on the SRPG version used to create the original `.dts` file, the reconstructed `.srpgs` projects might not work (the editor crashes), currently there is no way to fix this unless I can get my hands on an older version of the editor
- This is an ongoing project; please open issues for bugs or missing features.
