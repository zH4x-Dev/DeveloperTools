
### DeveloperTools

A collection of features that may be useful to plugin developers or organizations.

All information exported/dumped from this plugin can be found in the `bakkesmod\data\DeveloperTools` directory in CSV format.

### Features

- `Function Dumper` Dump all functions in the game that can be used for function hooks.
- `Texture Name Dumper` Dump all names of currently active/loaded textures the game is using.
- `Inventory Dumper` Dump information about the products in your inventory.
- `Product Dumper` Dump  information about the products in the game.
- `Slot Dumper` Dump information about slots in the game.
- `Map Dumper` Dump all user-available information about maps in the game.
- `Playlist Dumper` Dump all user-available information about playlists in the game.
- `Paint Dumper` Dump all information about painted attributes in the game.
- `Certification Dumper` Dump all information about certified attributes in the game.
- `Special Edition Dumper` Dump all information about special edition attributes in the game.

### Commands and Examples

All dump commands (excluding the Function and Texture Dumper) can be used with custom parameters in any order the user wants. The map and playlist dumper features will only dump what is available to the user via the UI, this is to prevent accidently exposing unreleased game modes/maps.

- **Function Dumper**

Command: `brank_dump_functions`

Usage Example: `brank_dump_functions`

Output Example: `Function Core.Object.RSmoothInterpTo`

- **Texture Name Dumper**

Command: `brank_dump_textures`

Usage Example: `brank_dump_textures`

Output Example: `Texture2D EngineResources.WhiteSquareTexture`

- **Inventory Dumper**

Command: `brank_dump_inventory {parameters}`

Usage Example: `	brank_dump_inventory {product_id} {online_instance_id} {product_long_label} {slot_index} {slot_online_label} {product_quality_id} {product_quality_label}`

Output Example:
`1334,117866551,Season 2 - Challenger,3,Rocket Boost,8,Limited`

- **Product Dumper**

Command: `brank_dump_products {parameters}`

Usage Example: `brank_dump_products {product_id} {product_long_label} {slot_online_label} {product_quality_label} {product_thumbnail_asset}`

Output Example: `1,8-Ball,Antenna,Uncommon,Antenna_8Ball_T`

- **Slot Dumper**
Command: `brank_dump_slots {parameters}`

Usage Example: `brank_dump_slots {slot_index} {slot_label} {slot_online_label} {slot_description}`

Output Example: `18,Player Anthem,Goal Stinger,None`

- **Map Dumper**

Command: `brank_dump_maps {parameters}`

Usage Example: `brank_dump_maps {map_base_name} {map_file_name} {map_weather_variant_id} {map_variant_name}`

Output Example: `DFH Stadium,stadium_day_p,2,Day`

- **Playlist Dumper**

Command: `brank_dump_playlists  {parameters}`

Usage Example: `brank_dump_playlists {playlist_id} {playlist_player_count} {playlist_title} {playlist_description} {playlist_bool_ranked}`

Output Example: `3,6,Standard,Classic team play,false`

- **Paint Dumper**

Command: `brank_dump_paints {parameters}`

Usage Example: `brank_dump_paints {database_paint_id} {database_paint_name} {database_paint_label} {database_paint_colors}`

Output Example: `1,Red_00,Crimson,#990000|#FF0B0B|#720000|#FF0000`

- **Certification Dumper**

Command: `brank_dump_certifications {parameters}`

Usage Example: `brank_dump_certifications {database_certified_id} {database_certified_name} {database_certified_label} {database_certified_description}`

Output Example: `1,AerialGoals,Aviator,When equipped in an online match, this item keeps track of how many aerial goals you score.`

- **Special Edition Dumper**

Command: `brank_dump_specialeditions {parameters}`

Usage Example: `brank_dump_specialeditions {database_special_id} {database_special_name} {database_special_label}`

Output Example: `1,Edition_Holographic,Holographic`

### Parameters
