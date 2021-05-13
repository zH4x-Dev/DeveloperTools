#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <filesystem>

/*
	2.0 Changelog:
	- Fixed the thumbnail drawer sometimes rendering decals on loadouts, instead of just the thumbnail itself.

	Features:
	- Texture Drawer (Done)
	- Texture Browser (Done)
	- Thumbnail Drawer (Done)
	- Service Dumper (Done)
	- Thumbnail Drawer (Done)
	- Function Dumper (Done)
	- Texture Name Dumper (Done)
	- Slot Dumper (Done)
	- Product Dumper (Done)
	- Inventory Dumper (Done)
	- Paint Dumper (Done)
	- Certification Dumper (Done)
	- Special Edition Dumper (Done)
	- Title Dumper (Done)
	- Team Edition Dumper (Done)
	- Playlist Dumper (Done)
	- Map Dumper (Done)
*/

enum class DrawModes : uint8_t
{
	NOT_DRAWING =	0,
	DRAW_TEXTURE =	1,
	DRAW_BROWSER =	2
};

enum class DumpFormat : uint8_t
{
	NONE =			0,
	CSV =			1,		// [CSV]
	JSON =			2		// [JSON]
};

enum class FieldsCategory : uint8_t
{
	NONE =			0,
	CSVLINE =		1,
	JSONSTART =		2,
	JSONEND =		3,
	INTEGER =		4,
	FLOAT =			5,
	BOOL =			6,
	STRING =		7
};

enum class ParameterCategory : uint8_t
{
	NONE =			0,
	SLOT =			1,
	PRODUCT =		2,
	ONLINE =		3,
	MAP =			4,
	PLAYLIST =		5,
	MUTATOR =		6,
	ATTRIBUTE =		7,
	DATABASE =		8
};

enum class SlotParameters : uint8_t
{
	NONE =                                 0,
	SLOT_LABEL =                           1,	// {slot_label}								Example: Body
	SLOT_PLURAL_LABEL =                    2,	// {slot_plural_label}						Example: Bodies
	SLOT_DESCRIPTION =                     3,	// {slot_description}						Example: Completely change your vehicle's style with a new body!
	SLOT_ONLINE_LABEL =                    4,	// {slot_online_label}						Example: Body
	SLOT_INDEX =                           5	// {slot_index}								Example: 0
};

enum class ProductParameters : uint8_t
{
	NONE =                                 0,
	PRODUCT_ID =                           1,	// {product_id}								Example: 1300
	PRODUCT_UNLOCK_METHOD_ID =             2,	// {product_unlock_method_id}				Example: 1
	PRODUCT_UNLOCK_METHOD_LABEL =          3,	// {product_unlock_method_label}			Example: Online
	PRODUCT_QUALITY_ID =                   4,	// {product_quality_id}						Example: 8
	PRODUCT_QUALITY_LABEL =                5,	// {product_quality_label}					Example: Limited
	PRODUCT_BOOL_LICENSED =                6,	// {product_bool_licensed}					Example: false
	PRODUCT_BOOL_PAINTABLE =               7,	// {product_bool_paintable}					Example: false
	PRODUCT_BOOL_CURRENCY =                8,	// {product_bool_currency}					Example: false
	PRODUCT_BOOL_BLUEPRINT =               9,	// {product_bool_blueprint}					Example: false
	PRODUCT_BOOL_SCHEMATIC =               10,	// {product_bool_schematic}					Example: false
	PRODUCT_BOOL_DECRYPTOR =               11,	// {product_bool_decryptor}					Example: false
	PRODUCT_ASSET_PACKAGE =                12,	// {product_asset_package}					Example: skin_octane_esports
	PRODUCT_ASSET_PATH =                   13,	// {product_asset_path}						Example: skin_octane_esports.skin_octane_esports
	PRODUCT_LABEL =                        14,	// {product_label}							Example: RLCS
	PRODUCT_ASCII_LABEL =                  15,	// {product_ascii_label}					Example: Octane: RLCS
	PRODUCT_LONG_LABEL =                   16,	// {product_long_label}						Example: Octane: RLCS
	PRODUCT_SHORT_ASCII_LABEL =            17,	// {product_short_ascii_label}				Example: RLCS
	PRODUCT_SHORT_SORT_LABEL =             18,	// {product_short_sort_label}				Example: RLCS
	PRODUCT_SORT_LABEL =                   19,	// {product_sort_label}						Example: Octane: RLCS
	PRODUCT_THUMBNAIL_PATH =               20,	// {product_thumbnail_path}					Example: Skin_Octane_Esports_T.Skin_Octane_Esports_T
	PRODUCT_THUMBNAIL_PACKAGE =            21,	// {product_thumbnail_package}				Example: Skin_Octane_Esports_T
	PRODUCT_THUMBNAIL_ASSET =              22,	// {product_thumbnail_asset}				Example: Skin_Octane_Esports_T
	PRODUCT_TRADEMARK_LABEL =              23	// {product_trademark_label}				Example: RLCS
};

enum class OnlineParameters : uint8_t
{
	NONE =                                 0,
	ONLINE_INSTANCE_ID =                   1,	// {online_instance_id}						Example: 2039203868
	ONLINE_SERIES_ID =                     2,	// {online_series_id}						Example: 20
	ONLINE_BOOL_TRADABLE =                 3,	// {online_bool_tradable}					Example: false
	ONLINE_ADDED_TIMESTAMP =               4,	// {online_added_timestamp}					Example: 1509241699
	ONLINE_CACHED_SORT_LABEL =             5,	// {online_cached_sort_label}				Example: Vampire Bat	CertifiedTurtle0102039203868
	ONLINE_CACHED_SHORT_SORT_LABEL =       6,	// {online_cached_short_sort_label}			Example: None
	ONLINE_CACHED_HASH_ID =                7,	// {online_cached_hash_id}					Example: 60729611
	ONLINE_ATTRIBUTE_STRING =              8,	// {online_attribute_string}				Example: CertifiedTurtleGoals1:
	ONLINE_BLUEPRINT_SERIES_ID =           9,	// {online_blueprint_series_id}				Example: 48
	ONLINE_BLUEPRINT_SERIES_LABEL =        10,	// {online_blueprint_series_label}			Example: Revival
	ONLINE_BLUEPRINT_TYPE_ID =             11,	// {online_blueprint_type_id}				Example: 1
	ONLINE_BLUEPRINT_TYPE_LABEL =          12	// {online_blueprint_type_label}			Example: Revealed
};

enum class AttributeParameters : uint8_t
{
	NONE =                                 0,
	ATTRIBUTE_PAINTED_ID =                 1,	// {attribute_painted_id}					Example: 12
	ATTRIBUTE_PAINTED_NAME =               2,	// {attribute_painted_name}					Example: White_00
	ATTRIBUTE_PAINTED_LABEL =              3,	// {attribute_painted_label}				Example: Titanium White
	ATTRIBUTE_CERTIFIED_ID =               4,	// {attribute_certified_id}					Example: 14
	ATTRIBUTE_CERTIFIED_NAME =             5,	// {attribute_certified_name}				Example: TurtleGoals
	ATTRIBUTE_CERTIFIED_LABEL =            6,	// {attribute_certified_label}				Example: Turtle
	ATTRIBUTE_CERTIFIED_VALUE =            7,	// {attribute_certified_value}				Example: 1
	ATTRIBUTE_CERTIFIED_DESCRIPTION =      8,	// {attribute_certified_description}		Example: When equipped in an online match, this item keeps track of how many upside down goals you score.
	ATTRIBUTE_TITLE_ID =                   9,	// {attribute_title_id}						Example: S15_SuperSonic_Legend
	ATTRIBUTE_TITLE_CATEGORY =             10,	// {attribute_title_category}				Example: SZN_1_White
	ATTRIBUTE_TITLE_TEXT =                 11,	// {attribute_title_text}					Example: S1 Supersonic Legend
	ATTRIBUTE_TITLE_COLOR =                12,	// {attribute_title_color}					Example: #E8E8E8
	ATTRIBUTE_TITLE_GLOWCOLOR =            13,	// {attribute_title_glowcolor}				Example: #E8E8E8
	ATTRIBUTE_SPECIAL_ID =                 14,	// {attribute_special_id}					Example: 2
	ATTRIBUTE_SPECIAL_NAME =               15,	// {attribute_special_name}					Example: Edition_Infinite
	ATTRIBUTE_SPECIAL_LABEL =              16,	// {attribute_special_label}				Example: Infinite
	ATTRIBUTE_TEAM_ID =                    17,	// {attribute_team_id}						Example: 26
	ATTRIBUTE_TEAM_NAME =                  18,	// {attribute_team_name}					Example: NRG_Season8
	ATTRIBUTE_TEAM_LABEL =                 19,	// {attribute_team_label}					Example: NRG Esports
	ATTRIBUTE_BLUEPRINT_COST =             20	// {attribute_blueprint_cost}				Example: 2000
};

enum class DatabaseParameters : uint8_t
{
	NONE =                                 0,
	DATABASE_PAINT_ID =                    1,	// {database_paint_id}						Example: 1
	DATABASE_PAINT_NAME =                  2,	// {database_paint_name}					Example: Red_00
	DATABASE_PAINT_LABEL =                 3,	// {database_paint_label}					Example: Crimson
	DATABASE_PAINT_COLORS =                4,	// {database_paint_colors}					Example: #990000|#FF0B0B|#720000|#FF0000
	DATABASE_PAINT_FINISH_ID =             5,	// {database_paint_finish_id}				Example: 0
	DATABASE_PAINT_FINISH_LABEL =          6,	// {database_paint_finish_label}			Example: Standard
	DATABASE_CERTIFIED_ID =                7,	// {database_certified_id}					Example: 1
	DATABASE_CERTIFIED_NAME =              8,	// {database_certified_name}				Example: AerialGoals
	DATABASE_CERTIFIED_LABEL =             9,	// {database_certified_label}				Example: Aviator
	DATABASE_CERTIFIED_DESCRIPTION =       10,	// {database_certified_description}			Example: When equipped in an online match, this item keeps track of how many aerial goals you score.
	DATABASE_SPECIAL_ID =                  11,	// {database_special_id}					Example: 1
	DATABASE_SPECIAL_NAME =                12,	// {database_special_name}					Example: Edition_Holographic
	DATABASE_SPECIAL_LABEL =               13,	// {database_special_label}					Example: Holographic
	DATABASE_TITLE_ID =                    14,	// {database_title_id}						Example: S15_SuperSonic_Legend
	DATABASE_TITLE_CATEGORY =              15,	// {database_title_category}				Example: SZN_1_White
	DATABASE_TITLE_TEXT =                  16,	// {database_title_text}					Example: S1 Supersonic Legend
	DATABASE_TITLE_COLOR =                 17,	// {database_title_color}					Example: #E8E8E8
	DATABASE_TITLE_GLOWCOLOR =             18,	// {database_title_glowcolor}				Example: #E8E8E8
	DATABASE_TEAM_ID =                     19,	// {database_team_id}						Example: 26
	DATABASE_TEAM_NAME =                   20,	// {database_team_name}						Example: NRG_Season8
	DATABASE_TEAM_LABEL =                  21	// {database_team_label}					Example: NRG Esports
};

enum class PlaylistParameters : uint32_t
{
	NONE =                                 0,
	PLAYLIST_ID =                          1,	// {playlist_id}							Example: 3
	PLAYLIST_TITLE =                       2,	// {playlist_title}							Example: Standard
	PLAYLIST_DESCRIPTION =                 3,	// {playlist_description}					Example: Ranked play with a team
	PLAYLIST_PLAYERCOUNT =                 4,	// {playlist_player_count}					Example: 6
	PLAYLIST_BOOL_STANDARD =               5,	// {playlist_bool_standard}					Example: true
	PLAYLIST_BOOL_RANKED =                 6,	// {playlist_bool_ranked}					Example: false
	PLAYLIST_BOOL_SOLO =                   7,	// {playlist_bool_solo}						Example: false
	PLAYLIST_BOOL_EXTRAMODE =              8,	// {palylist_bool_extramode}				Example: false
	PLAYLIST_BOOL_PRIVATE =                9,	// {playlist_bool_private}					Example: false
	PLAYLIST_BOOL_TOURNAMENT =             10,	// {playlist_bool_tournament}				Example: false
	PLAYLIST_BOOL_APPLYQUITPENALTY =       11,	// {playlist_bool_applyquitpenalty}			Example: true
	PLAYLIST_BOOL_ALLOWFORFIET =           12,	// {playlist_bool_allowforfiet}				Example: false
	PLAYLIST_BOOL_DISABLERECONNECT =       13,	// {playlist_bool_disablereconnect}			Example: false
	PLAYLIST_BOOL_IGNOREASSIGNTEAMS =      14,	// {playlist_bool_ignoreassignteams}		Example: false
	PLAYLIST_BOOL_ALLOWBOTFILLS =          15,	// {playlist_bool_allowbotfills}			Example: true
	PLAYLIST_BOOL_KICKONMIGRATE =          16,	// {playlist_bool_kickonmigrate}			Example: false
	PLAYLIST_BOOL_CHECKRESERVATION =       17,	// {playlist_bool_checkreservation}			Example: false
	PLAYLIST_BOOL_ISMICROEVENT =           18,	// {playlist_bool_ismicroevent}				Example: false
	PLAYLIST_BOOL_HASVARIABLEPLAYERCOUNT = 19,	// {playlist_bool_hasvariableplayercount}	Example: false
	PLAYLIST_BOOL_NEW =                    20,	// {playlist_bool_new}						Example: false
	PLAYLIST_BOOL_ALLOWCLUBS =             21,	// {playlist_bool_allowclubs}				Example: true
	PLAYLIST_BOOL_ALLOWSTAYASPARTY =       22,	// {playlist_bool_allowstayasparty}			Example: true
	PLAYLIST_IMAGE_URL =                   23,	// {playlist_image_url}						Example: https://rl-cdn.psyonix.com/Playlists/Images/rl_event_mode_bg_heatseeker.jpg
	PLAYLIST_IMAGE_TEXTURE =               24,	// {playlist_image_texture}					Example: None
	PLAYLIST_ICON_ACTIVE_URL =             25,	// {playlist_icon_active_url}				Example: https://rl-cdn.psyonix.com/Playlists/Images/rl_mode_heatseeker_1.png
	PLAYLIST_ICON_INACTIVE_URL =           26,	// {playlist_icon_inactive_url}				Example: https://rl-cdn.psyonix.com/Playlists/Images/rl_mode_heatseeker_2.png
	PLAYLIST_MAP_NAME =                    27,	// {playlist_map_name}						Example: throwbackhockey_p
	PLAYLIST_SERVER_COMMAND =              28,	// {playlist_server_command}				Example: Game=TAGame.GameInfo_GodBall_TA?playtest?listen?Public?GameTags=BotsNone
	PLAYLIST_MAPSET_NAME =                 29	// {playlist_mapset_name}					Example: SoccarStandard
};

enum class MapParameters : uint8_t
{
	NONE =                                 0,
	MAP_WEATHER_VARIANT_ID =               1,	// {map_weather_variant_id}					Example: 2
	MAP_WEATHER_VARIANT_NAME =             2,	// {map_weather_variant_name}				Example: Day
	MAP_RANDOM_WEIGHT =                    3,	// {map_random_weight}						Example: 1.300000
	MAP_VARIANT_NAME =                     4,	// {map_variant_name}						Example: Day
	MAP_BASE_NAME =                        5,	// {map_base_name}							Example: DFH Stadium
	MAP_FILE_NAME =                        6	// {map_file_name}							Example: stadium_day_p
};

enum class MutatorParameters : uint8_t
{
	NONE =                                 0,
	MUTATOR_PRESET_TAGS =                  1,	// {mutator_preset_tags}					Example: Mutators_Balls|Ball_Haunted
	MUTATOR_CATEGORY =                     2,	// {mutator_category}						Example: Mutators_Items
	MUTATOR_SETTING =                      3,	// {mutator_setting}						Example: ItemsModeHauntedBallBeam
	MUTATOR_REQUIRED_MAPS =                4,	// {mutator_required_maps}					Example: None
	MUTATOR_OVERRIDE_NAME =                5	// {mutator_override_name}					Example: Haunted Ball
};

class ParameterPair
{
private:
	ParameterCategory Category;
	uint8_t Type;

public:
	ParameterPair();
	ParameterPair(const ParameterCategory& category, const uint8_t& type);
	~ParameterPair();

public:
	ParameterCategory GetCategory() const;
	uint8_t GetType() const;
};

class PairFields
{
private:
	FieldsCategory Category;
	std::string Name;
	std::string Value;
	bool PrintComma;

public:
	PairFields();
	PairFields(const FieldsCategory& category, const std::string& name, const std::string& value);
	~PairFields();

public:
	FieldsCategory GetCategory() const;
	std::string GetName() const;
	std::string GetValue() const;
	bool ShouldPrintComma() const;
	void SetCategory(const FieldsCategory& category);
	void SetName(const std::string& name);
	void SetValue(const std::string& value);
	void SetShouldComma(const bool& bPrintComma);
};

class DeveloperTools : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	bool ClassesSafe = false;
	bool MapLimiter = true;
	bool PlaylistLimiter = true;
	bool ProductLimiter = false;

	DrawModes DrawMode;

	int32_t ViewId = -1;
	int32_t BrowseIndex = 0;
	std::vector<class UTexture2D*> TexturesToBrowse;
	std::string TextureToLoad = "DeveloperTools";

	std::filesystem::path DumpPath = "DeveloperTools";

private:
	class U_Types_TA* IU_Types_TA = nullptr;
	class UGameData_TA* IUGameData_TA = nullptr;
	class UProductDatabase_TA* IUProductDatabase_TA = nullptr;
	class UPaintDatabase_TA* IUPaintDatabase_TA = nullptr;
	class UCertifiedStatDatabase_TA* IUCertifiedStatDatabase_TA = nullptr;
	class USpecialEditionDatabase_TA* IUSpecialEditionDatabase_TA = nullptr;
	class UDataAssetDatabase_ESportsTeam_TA* IUDataAssetDatabase_ESportsTeam_TA = nullptr;
	class UGFxData_ProductFilter_TA* IUGFxData_ProductFilter_TA = nullptr;
	class UChallengeManager_TA* IUChallengeManager_TA = nullptr;
	class UPlayerTitleConfig_X* IUPlayerTitleConfig_X = nullptr;
	class UMapList_TA* IUMapList_TA = nullptr;
	class UOnlineGamePlaylists_X* IUOnlineGamePlaylists_X = nullptr;
	class USaveData_TA* IUSaveData_TA = nullptr;
	class UProductAssetLoader_TA* IUProductAssetLoader_TA = nullptr;

public:
	bool AreGObjectsValid();
	bool AreGNamesValid();
	bool AreClassesSafe();
	void LoadClasses();

	void Debug();
	virtual void onLoad();
	virtual void onUnload();

	void ParametersToFile(const std::vector<PairFields>& fields, const std::vector<ParameterPair>& parameters, const std::string& filename, const DumpFormat& format);
	DumpFormat GetFormat(const std::string& params);
	std::string GetFullCommand(const std::vector<std::string>& params, const bool& skipFirst);
	std::string GetParameterLabel(const ParameterPair& parameter);
	std::string GetCSVHeader(const std::vector<ParameterPair>& parameters);
	std::vector<ParameterPair> GetParameters(const std::string& parameterString);
	std::string ColorToHex(struct FColor& color, const bool& includeHead);
	class UProduct_TA* GetProductFromId(const int32_t& productId);

	std::string GetValueFromSlot(class UProductSlot_TA* slot, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromProduct(class UOnlineProduct_TA* onlineProduct, class UProduct_TA* offlineProduct, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromMap(class UMapData_TA* map, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromPlaylist(class UPlaylistSettings_X* playlist, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromPaint(class UProductPaint_TA* paint, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromAttribute(class UOnlineProduct_TA* onlineProduct, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromCertification(class UCertifiedStat_TA* certification, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromSpecialEdition(class UProductSpecialEdition_TA* specialEdition, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromTitle(struct FPlayerTitleData& titleData, const ParameterPair& parameter, FieldsCategory& outCategory);
	std::string GetValueFromTeamEdition(class UDataAsset_ESportsTeam_TA* teamAsset, const ParameterPair& parameter, FieldsCategory& outCategory);

	void DumpFunctions();
	void DumpTextures();
	void DumpServices();
	void DumpSlots(const std::vector<std::string>& params);
	void DumpProducts(const std::vector<std::string>& params);
	void DumpInventory(const std::vector<std::string>& params);
	void DumpPaints(const std::vector<std::string>& params);
	void DumpCertifications(const std::vector<std::string>& params);
	void DumpSpecialEditions(const std::vector<std::string>& params);
	void DumpTitles(const std::vector<std::string>& params);
	void DumpTeamEditions(const std::vector<std::string>& params);
	void DumpPlaylists(const std::vector<std::string>& params);
	void DumpMaps(const std::vector<std::string>& params);
	void DumpMutators(const std::vector<std::string>& params);

	void ToggleBrowseTextures(const std::vector<std::string>& params);
	void DrawTexture(const std::vector<std::string>& params);
	void DrawThumbnail(const std::vector<std::string>& params);
	void EraseTexture();

	void GameViewPortKeyPress(ActorWrapper caller, void* params, const std::string& functionName);
	void CanvasRender(ActorWrapper caller, void* params, const std::string& functionName);
	void SetActiveView(ActorWrapper caller, void* params, const std::string& functionName);
	void DebugHook(ActorWrapper caller, void* params, const std::string& functionName);
};