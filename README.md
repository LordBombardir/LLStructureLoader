# StructureLoader

## Attention

The author of this mod is **not responsible** for issues caused by loading incorrect structures, including possible damage to the server map.

## Overview

**StructureLoader** is a mod for loading vanilla Minecraft: Bedrock Edition (`.mcstructure`) files into your server. It supports the following commands:
- `load-structure` — load structures into server memory.
- `remove-structure` — remove structures from server memory.

## Installation & Usage

1. Download and install the latest release from the [GitHub Releases page](https://github.com/LordBombardir/LLStructureLoader/releases) or install using `lip`.
2. Start your server. Once the mod is enabled, a `structures` folder will appear.
3. Place your `.mcstructure` files into the `structures` folder.
4. Use the `load-structure` command to load structures without restarting the server.
   - Once loaded, structure files will be renamed with a `.bak` extension.
5. Use the `remove-structure` command if needed.
   - Note: This may list structures even if the corresponding file has been removed.

## Configuration

Basic configuration format (`config.json`):
```json
{
    "version": 1,
    "defaultLocaleCode": "en_US",
    "logToConsoleIfStructureIsAlreadyLoaded": true,
    "backupRemovedStructure": true
}
```