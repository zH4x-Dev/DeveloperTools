

# DeveloperTools

A collection of features for plugin developers and organizations.

All information exported/dumped from this plugin can be found in the `bakkesmod\data\DeveloperTools` directory in CSV format.

## Features

- `Texture Browser/Drawer` Browse through all textures that are currently loaded in the scene, as well as draw specific ones by name.
- `Texture Name Dumper` Dump all names of currently active/loaded textures the game is using.
- `Function Dumper` Dump all functions in the game that can be used for function hooks.
- `Inventory Dumper` Dump information about the products in your inventory.
- `Product Dumper` Dump  information about the products in the game.
- `Slot Dumper` Dump information about slots in the game.
- `Map Dumper` Dump all user-available information about maps in the game.
- `Playlist Dumper` Dump all user-available information about playlists in the game.
- `Paint Dumper` Dump all information about painted attributes in the game.
- `Certification Dumper` Dump all information about certified attributes in the game.
- `Special Edition Dumper` Dump all information about special edition attributes in the game.

## Commands and Examples

All dump commands (excluding the Function and Texture Dumper) can be used with custom parameters in any order the user wants. The map and playlist dumper features will only dump what is available to the user via the UI, this is to prevent accidently exposing unreleased game modes/maps.

-**Texture Browser**
Command: `brank_browsetextures {true_false}`

Usage Example: `brank_browsetextures true`
To cycle through textures you can use your arrow keys or your scroll wheel.

Output Example:

![](https://i.imgur.com/IS6AVkA.png)

-**Texture Drawer**
Command: `brank_drawtexture {texture_name}`
Command: `brank_erasetexture`

Usage Example: `brank_drawtexture Noise_Fire`

Output Example:

![](https://i.imgur.com/rPhY6Ox.png)

- **Texture Name Dumper**

Command: `brank_dump_textures`

Usage Example: `brank_dump_textures`

Output Example: `Texture2D EngineResources.WhiteSquareTexture`
- **Function Dumper**

Command: `brank_dump_functions`

Usage Example: `brank_dump_functions`

Output Example: `Function Core.Object.RSmoothInterpTo`

- **Inventory Dumper**

Command: `brank_dump_inventory {parameters}`

Usage Example: `brank_dump_inventory {product_id} {online_instance_id} {product_long_label} {slot_index} {slot_online_label} {product_quality_id} {product_quality_label}`

Output Example: `1334,117866551,Season 2 - Challenger,3,Rocket Boost,8,Limited`

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

Output Example: `1,AerialGoals,Aviator,When equipped in an online match\, this item keeps track of how many aerial goals you score.`

- **Special Edition Dumper**

Command: `brank_dump_specialeditions {parameters}`

Usage Example: `brank_dump_specialeditions {database_special_id} {database_special_name} {database_special_label}`

Output Example: `1,Edition_Holographic,Holographic`

# Parameters and Examples

Parameters can be used in any order you want, the final output will be organized to match what you put in.

Parameters are organized by what can be used with each specific command, there is `Slot`, `Online Product`, `Offline Product`, `Map`, `Playlist`, `Attribute`, and `Database`.

When dumping products related to your inventory all four parameters `Slot`, `Attribute`, `Online Product`, and `Offline Product` can be used. Online refers to information that is exclusive to products in your inventory. Offline refers to the information the game stores in it's database for products. As such the product dumper command can only use the `Slot` or `Offline Product` parameters. As you might guess, `Playlist` can only be used with the playlist dumper, `Map` will only work with the map dumper, and so on.

| Slot Parameters | Output Example |
| ------ | ------ |
| {slot_label} | Body |
| {slot_plural_Label} | Bodies |
| {slot_description} | Completely change your vehicle's style with a new body! |
| {slot_online_label} | Body |
| {slot_index} | 0 |

| Online Product Parameters | Output Example |
| ------ | ------ |
| {online_instance_id} | 2039203868 |
| {online_series_id} | 20 |
| {online_bool_tradable} | false |
| {online_added_timestamp} | 1509241699 |
| {online_cached_sort_label} | Vampire Bat	CertifiedTurtle0102039203868 |
| {online_cached_short_sort_label} | None |
| {online_cached_hash_id} | 60729611 |
| {online_attribute_string} | CertifiedTurtleGoals1: |

| Online Product Parameters | Output Example |
| ------ | ------ |
| {product_id} | 1300 |
| {product_unlock_method_id} | 1 |
| {product_unlock_method_label} | Online |
| {product_quality_id} | 8 |
| {product_quality_label} | Limited |
| {product_bool_licensed} | false |
| {product_bool_paintable} | false |
| {product_bool_currency} | false |
| {product_bool_blueprint} | false |
| {product_bool_schematic} | false |
| {product_bool_decryptor} | false |
| {product_asset_package} | skin_octane_esports |
| {product_asset_path} | skin_octane_esports.skin_octane_esports |
| {product_label} | RLCS |
| {product_ascii_label} | Octane: RLCS |
| {product_long_label} | Octane: RLCS |
| {product_short_ascii_label} | RLCS |
| {product_short_sort_label} | RLCS |
| {product_sort_label} | Octane: RLCS |
| {product_thumbnail_path} | Skin_Octane_Esports_T.Skin_Octane_Esports_T |
| {product_thumbnail_package} | Skin_Octane_Esports_T |
| {product_thumbnail_asset} | Skin_Octane_Esports_T |
| {product_trademark_label} | RLCS |

| Map Parameters | Output Example |
| ------ | ------ |
| {map_weather_variant_id} | 2 |
| {map_weather_variant_name} | Day |
| {map_random_weight} | 1.300000 |
| {map_variant_name} | Day |
| {map_base_name} | DFH Stadium |
| {map_file_name} | stadium_day_p |

| Playlist Parameters | Output Example |
| ------ | ------ |
| {playlist_id} | 3 |
| {playlist_title} | Standard |
| {playlist_description} | Ranked play with a team |
| {playlist_player_count} | 6 |
| {playlist_bool_standard} | true |
| {playlist_bool_ranked} | false |
| {playlist_bool_solo} | false |
| {palylist_bool_extramode} | false |
| {playlist_bool_private} | false |
| {playlist_bool_tournament} | false |
| {playlist_bool_applyquitpenalty} | true |
| {playlist_bool_allowforfiet} | false |
| {playlist_bool_disablereconnect} | false |
| {playlist_bool_ignoreassignteams} | false |
| {playlist_bool_allowbotfills} | true |
| {playlist_bool_kickonmigrate} | false |
| {playlist_bool_checkreservation} | false |
| {playlist_bool_ismicroevent} | false |
| {playlist_bool_hasvariableplayercount} | false |
| {playlist_bool_new} | false |
| {playlist_bool_allowclubs} | true |
| {playlist_bool_allowstayasparty} | true |
| {playlist_image_url} | https://rl-cdn.psyonix.com/Playlists/Images/rl_event_mode_bg_heatseeker.jpg |
| {playlist_image_texture} | None |
| {playlist_icon_active_url} | https://rl-cdn.psyonix.com/Playlists/Images/rl_mode_heatseeker_1.png |
| {playlist_icon_inactive_url} | https://rl-cdn.psyonix.com/Playlists/Images/rl_mode_heatseeker_2.png |
| {playlist_map_name} | throwbackhockey_p |
| {playlist_server_command} | Game=TAGame.GameInfo_GodBall_TA?playtest?listen?Public?GameTags=BotsNone |
| {playlist_mapset_name} | SoccarStandard |

| Attribute Parameters | Output Example |
| ------ | ------ |
| {attribute_painted_id} | 12 |
| {attribute_painted_name} | White_00 |
| {attribute_painted_label} | Titanium White |
| {attribute_certified_id} | 14 |
| {attribute_certified_name} | TurtleGoals |
| {attribute_certified_label} | Turtle |
| {attribute_certified_value} | 1 |
| {attribute_certified_description} | When equipped in an online match\, this item keeps track of how many upside down goals you score. |
| {attribute_title_id} | S15_SuperSonic_Legend |
| {attribute_title_category} | SZN_1_White |
| {attribute_title_text} | S1 Supersonic Legend |
| {attribute_title_color} | #E8E8E8 |
| {attribute_title_glowcolor} | #E8E8E8 |
| {attribute_special_id} | 2 |
| {attribute_special_name} | Edition_Infinite |
| {attribute_special_label} | Infinite |
| {attribute_team_id} | None |
| {attribute_team_name} | None |
| {attribute_team_teamname} | None |

| Database Parameters | Output Example |
| ------ | ------ |
| {database_paint_id} | 1 |
| {database_paint_name} | Red_00 |
| {database_paint_label} | Crimson |
| {database_paint_colors} | #990000|#FF0B0B|#720000|#FF0000 |
| {database_paint_finish_id} | 0 |
| {database_paint_finish_label} | Standard |
| {database_certified_id} | 1 |
| {database_certified_name} | AerialGoals |
| {database_certified_label} | Aviator |
| {database_certified_description} | When equipped in an online match\, this item keeps track of how many aerial goals you score. |
| {database_special_id} | 1 |
| {database_special_name} | Edition_Holographic |
| {database_special_label} | Holographic |
