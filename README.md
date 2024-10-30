# SRPG-ToolBox

Work in process toolbox to unpack and repack `.dts` files, recreate `.srpgs` project files, and in place modification of project files (currently under development).
SRPG Studio, up to version 1.292, is supported.

## Usage:
Drag and drop a `.dts` file onto `SRPG_Unpacker.exe` to extract the file into a folder called `output`.<br>
Drag and drop the `output` folder onto `SRPG_Unpacker.exe` to repack the folder into a `.dts` file.

## Known Problems:
 - Not all classes and commands are implemented; please open an issue if an unimplemented component is encountered
 - Extracted scripts sometimes have to wrong file encoding
 - Resources (graphics, music, videos, etc.) included in the `.dts` archive are not properly linked in the reconstructed `.srpgs` project
