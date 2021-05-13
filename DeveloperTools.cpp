#include "DeveloperTools.hpp"
//#include "Wrappers/CanvasWrapper.hpp" // Custom wrappers, no I won't give (yet).
//#include "Wrappers/StringWrapper.hpp" // Custom wrappers, no I won't give (yet).
//#include "Wrappers/Texture2DWrapper.hpp" // Custom wrappers, no I won't give (yet).
//#include "Wrappers/BulkDataWrapper.hpp" // Custom wrappers, no I won't give (yet).
//#include "Wrappers/Colors.hpp" // Custom wrappers, no I won't give (yet).
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

BAKKESMOD_PLUGIN(DeveloperTools, "BranK's Developer Tools", "2.0", PERMISSION_ALL)

ParameterPair::ParameterPair()
{
	Category = ParameterCategory::NONE;
	Type = 0;
}

ParameterPair::ParameterPair(const ParameterCategory& category, const uint8_t& type)
{
	Category = category;
	Type = type;
}

ParameterPair::~ParameterPair() { }

ParameterCategory ParameterPair::GetCategory() const
{
	return Category;
}

uint8_t ParameterPair::GetType() const
{
	return Type;
}

PairFields::PairFields()
{
	Category = FieldsCategory::NONE;
	Name = "NONE";
	Value = "NONE";
	PrintComma = false;
}

PairFields::PairFields(const FieldsCategory& category, const std::string& name, const std::string& value)
{
	Category = category;
	Name = name;
	Value = value;
	PrintComma = true;
}

PairFields::~PairFields() { }

std::string PairFields::GetName() const
{
	return Name;
}

FieldsCategory PairFields::GetCategory() const
{
	return Category;
}

std::string PairFields::GetValue() const
{
	return Value;
}

bool PairFields::ShouldPrintComma() const
{
	return PrintComma;
}

void PairFields::SetCategory(const FieldsCategory& category)
{
	Category = category;
}

void PairFields::SetName(const std::string& name)
{
	Name = name;
}

void PairFields::SetValue(const std::string& value)
{
	Value = value;
}

void PairFields::SetShouldComma(const bool& bPrintComma)
{
	PrintComma = bPrintComma;
}

bool DeveloperTools::AreGObjectsValid()
{
	if (UObject::GObjObjects()->Num() > 0 && UObject::GObjObjects()->Max() > UObject::GObjObjects()->Num())
	{
		if (UObject::GObjObjects()->At(0)->GetFullName() == "Class Core.Config_ORS")
		{
			return true;
		}
	}

	return false;
}

bool DeveloperTools::AreGNamesValid()
{
	if (FName::Names()->Num() > 0 && FName::Names()->Max() > FName::Names()->Num())
	{
		if (FName(0).ToString() == "None")
		{
			return true;
		}
	}

	return false;
}

bool DeveloperTools::AreClassesSafe()
{
	return ClassesSafe;
}

void DeveloperTools::LoadClasses()
{
	// INIT RLSDK CLASSES HERE, ACTUAL CODE REMOVED BECAUSE BAKKES WOULD BAN ME
}

void DeveloperTools::Debug()
{
	
}

void DeveloperTools::onLoad()
{
	DumpPath = gameWrapper->GetBakkesModPath().append("data");
	DumpPath = std::filesystem::absolute(DumpPath);
	DumpPath.append("DeveloperTools");
	std::filesystem::create_directory(DumpPath);

	if (std::filesystem::exists(DumpPath))
	{
		GObjects = reinterpret_cast<TArray<UObject*>*>(Utils::FindPattern(GetModuleHandleA("RocketLeague.exe"), GObjects_Pattern, GObjects_Mask));
		GNames = reinterpret_cast<TArray<FNameEntry*>*>(Utils::FindPattern(GetModuleHandleA("RocketLeague.exe"), GNames_Pattern, GNames_Mask));

		if (AreGObjectsValid() && AreGNamesValid())
		{
			LoadClasses();

			if (AreClassesSafe())
			{
				//cvarManager->registerNotifier("brank_debug", [this](std::vector<std::string> params) { Debug(); }, "Debug.", PERMISSION_ALL);

				cvarManager->registerNotifier("brank_drawtexture", [this](std::vector<std::string> params) { DrawTexture(params); }, "Draws a texture to the screen.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_erasetexture", [this](std::vector<std::string> params) { EraseTexture(); }, "Erases the texture currently being drawed to the screen.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_browsetextures", [this](std::vector<std::string> params) { ToggleBrowseTextures(params); }, "Toggle the texture browser.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_drawthumbnail", [this](std::vector<std::string> params) { DrawThumbnail(params); }, "Draws a products thumbnail by their id.", PERMISSION_ALL);

				cvarManager->registerNotifier("brank_dump_functions", [this](std::vector<std::string> params) { DumpFunctions(); }, "Dumps all functions the game uses.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_textures", [this](std::vector<std::string> params) { DumpTextures(); }, "Dumps all loaded texture names.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_services", [this](std::vector<std::string> params) { DumpServices(); }, "Dumps all information from every service class.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_slots", [this](std::vector<std::string> params) { DumpSlots(params); }, "Dumps all slots used by products.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_products", [this](std::vector<std::string> params) { DumpProducts(params); }, "Dumps all products in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_inventory", [this](std::vector<std::string> params) { DumpInventory(params); }, "Dumps all the products in your inventory.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_paints", [this](std::vector<std::string> params) { DumpPaints(params); }, "Dumps all paints in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_certifications", [this](std::vector<std::string> params) { DumpCertifications(params); }, "Dumps all certifications in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_specialeditions", [this](std::vector<std::string> params) { DumpSpecialEditions(params); }, "Dumps all special editions in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_titles", [this](std::vector<std::string> params) { DumpTitles(params); }, "Dumps all titles in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_teameditions", [this](std::vector<std::string> params) { DumpTeamEditions(params); }, "Dumps all team editions in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_playlists", [this](std::vector<std::string> params) { DumpPlaylists(params); }, "Dumps all playlists in the game.", PERMISSION_ALL);
				cvarManager->registerNotifier("brank_dump_maps", [this](std::vector<std::string> params) { DumpMaps(params); }, "Dumps all maps in the game.", PERMISSION_ALL);
				//cvarManager->registerNotifier("brank_dump_mutators", [this](std::vector<std::string> params) { DumpMutators(params); }, "Dumps all mutators in the game.", PERMISSION_ALL);

				gameWrapper->HookEventWithCaller<ActorWrapper>("Function TAGame.GFxData_ViewMetrics_TA.SetActiveView", std::bind(&DeveloperTools::SetActiveView, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
				gameWrapper->HookEventWithCaller<ActorWrapper>("Function TAGame.GameViewportClient_TA.HandleKeyPress", std::bind(&DeveloperTools::GameViewPortKeyPress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
				gameWrapper->HookEventWithCaller<ActorWrapper>("Function Engine.HUD.PostRender", std::bind(&DeveloperTools::CanvasRender, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			}
			else
			{
				cvarManager->log("(onLoad) Error: RLSDK classes are wrong, please contact ItsBranK if he doesn't already know!");
			}
		}
		else
		{
			cvarManager->log("(onLoad) Error: RLSDK classes are wrong, please contact ItsBranK if he doesn't already know!");
		}
	}
	else
	{
		cvarManager->log("(onLoad) Error: Failed to locate/create the \"DeveloperTools\" folder!");
	}
}

void DeveloperTools::onUnload()
{
	EraseTexture();

	gameWrapper->UnhookEvent("Function TAGame.GFxData_ViewMetrics_TA.SetActiveView");
	gameWrapper->UnhookEvent("Function TAGame.GameViewportClient_TA.HandleKeyPress");
	gameWrapper->UnhookEvent("Function Engine.HUD.PostRender");
}

void DeveloperTools::ParametersToFile(const std::vector<PairFields>& fields, const std::vector<ParameterPair>& parameters, const std::string& filename, const DumpFormat& format)
{
	if (format == DumpFormat::CSV)
	{
		std::ofstream file(DumpPath.u8string() + "\\" + filename + ".csv");

		file << GetCSVHeader(parameters);

		static bool bComma = false;

		for (PairFields field : fields)
		{
			if (field.GetCategory() == FieldsCategory::CSVLINE)
			{
				file << std::endl;

				bComma = false;
			}
			else if (field.GetCategory() != FieldsCategory::JSONSTART && field.GetCategory() != FieldsCategory::JSONEND && field.GetCategory() != FieldsCategory::NONE)
			{
				if (bComma)
				{
					file << ",";
				}

				bComma = true;

				file << field.GetValue();
			}
			else if (field.GetCategory() != FieldsCategory::JSONSTART && field.GetCategory() != FieldsCategory::JSONEND)
			{
				cvarManager->log("(ParametersToFile) CSV Error: Invalid category detected! Please give this id to ItsBranK: " + std::to_string(static_cast<int32_t>(field.GetCategory())));
			}
		}

		file.close();
	}
	else if (format == DumpFormat::JSON)
	{
		std::ofstream file(DumpPath.u8string() + "\\" + filename + ".json");

		file << "[" << std::endl;

		for (PairFields field : fields)
		{
			if (field.GetCategory() == FieldsCategory::JSONSTART)
			{
				file << "\t{" << std::endl;
			}
			else if (field.GetCategory() == FieldsCategory::JSONEND)
			{
				file << "\t}" << (field.ShouldPrintComma() ? "," : "") << std::endl;
			}
			else if (field.GetCategory() == FieldsCategory::STRING)
			{
				file << "\t\t\"" << field.GetName() << "\": \"" << field.GetValue() << "\"" << (field.ShouldPrintComma() ? "," : "") << std::endl;
			}
			else if (field.GetCategory() != FieldsCategory::CSVLINE && field.GetCategory() != FieldsCategory::NONE)
			{
				file << "\t\t\"" << field.GetName() << "\": " << field.GetValue() << (field.ShouldPrintComma() ? "," : "") << std::endl;
			}
			else if (field.GetCategory() != FieldsCategory::CSVLINE)
			{
				cvarManager->log("(ParametersToFile) JSON Error: Invalid category detected! Please give this id to ItsBranK: " + std::to_string(static_cast<int32_t>(field.GetCategory())));
			}
		}

		file << "]";

		file.close();
	}
	else
	{
		cvarManager->log("(ParametersToFile) Error: Invalid format type, something went wrong!");
	}
}

DumpFormat DeveloperTools::GetFormat(const std::string& fullCommand)
{
	if (fullCommand.find("[CSV]") != std::string::npos)
	{
		return DumpFormat::CSV;
	}
	else if (fullCommand.find("[JSON]") != std::string::npos)
	{
		return DumpFormat::JSON;
	}

	return DumpFormat::NONE;
}

std::string DeveloperTools::GetFullCommand(const std::vector<std::string>& params, const bool& skipFirst)
{
	std::string returnCommand;

	bool firstString = true;

	for (auto param = params.begin(); param < params.end(); param++)
	{
		if (param == params.begin())
		{
			if (!skipFirst)
			{
				returnCommand = *param;
			}
		}
		else
		{
			if (firstString)
			{
				returnCommand += *param;
				firstString = false;
			}
			else
			{
				returnCommand += (" " + *param);
			}
		}
	}

	return returnCommand;
}

std::string DeveloperTools::GetParameterLabel(const class ParameterPair& parameter)
{
	static bool initialized = false;
	static std::map<SlotParameters, std::string> slotLabels;
	static std::map<ProductParameters, std::string> productLabels;
	static std::map<OnlineParameters, std::string> onlineLabels;
	static std::map<AttributeParameters, std::string> attributeLabels;
	static std::map<MapParameters, std::string> mapLabels;
	static std::map<PlaylistParameters, std::string> playlistLabels;
	static std::map<MutatorParameters, std::string> mutatorLabels;
	static std::map<DatabaseParameters, std::string> databaseLabels;

	if (!initialized)
	{
		slotLabels.insert(std::make_pair<SlotParameters, std::string>(SlotParameters::SLOT_LABEL, "Slot Label"));
		slotLabels.insert(std::make_pair<SlotParameters, std::string>(SlotParameters::SLOT_PLURAL_LABEL, "Slot Plural Label"));
		slotLabels.insert(std::make_pair<SlotParameters, std::string>(SlotParameters::SLOT_DESCRIPTION, "Slot Description"));
		slotLabels.insert(std::make_pair<SlotParameters, std::string>(SlotParameters::SLOT_ONLINE_LABEL, "Slot Online Label"));
		slotLabels.insert(std::make_pair<SlotParameters, std::string>(SlotParameters::SLOT_INDEX, "Slot Index"));
	
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_ID, "Product Id"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_UNLOCK_METHOD_ID, "Product Unlock Method Id"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_UNLOCK_METHOD_LABEL, "Product Unlock Method Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_QUALITY_ID, "Product Quality Id"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_QUALITY_LABEL, "Product Quality Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_LICENSED, "Product Licensed"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_PAINTABLE, "Product Paintable"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_CURRENCY, "Product Currency"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_BLUEPRINT, "Product Blueprint"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_SCHEMATIC, "Product Schematic"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_BOOL_DECRYPTOR, "Product Decryptor"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_ASSET_PACKAGE, "Product Asset Package"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_ASSET_PATH, "Product Asset Path"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_LABEL, "Product Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_ASCII_LABEL, "Product Ascii Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_LONG_LABEL, "Product Long Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_SHORT_ASCII_LABEL, "Product Short Ascii Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_SHORT_SORT_LABEL, "Product Short Sort Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_SORT_LABEL, "Product Sort Label"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_THUMBNAIL_PATH, "Product Thumbnail Path"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_THUMBNAIL_PACKAGE, "Product Thumbnail Package"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_THUMBNAIL_ASSET, "Product Thumbnail Asset"));
		productLabels.insert(std::make_pair<ProductParameters, std::string>(ProductParameters::PRODUCT_TRADEMARK_LABEL, "Product Trademark Label"));

		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_INSTANCE_ID, "Online Instance Id"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_SERIES_ID, "Online Series Id"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_BOOL_TRADABLE, "Online Tradable"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_ADDED_TIMESTAMP, "Online Added Timestamp"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_CACHED_SORT_LABEL, "Online Cached Sort Label"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_CACHED_SHORT_SORT_LABEL, "Online Cached Short Sort Label"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_CACHED_HASH_ID, "Online Cached Hash Id"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_ATTRIBUTE_STRING, "Online Attribute String"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_ID, "Blueprint Series Id"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_LABEL, "Blueprint Series Label"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_ID, "Blueprint Type Id"));
		onlineLabels.insert(std::make_pair<OnlineParameters, std::string>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_LABEL, "Blueprint Type Label"));

		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_PAINTED_ID, "Painted Attribute Id"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_PAINTED_NAME, "Painted Attribute Name"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_PAINTED_LABEL, "Painted Attribute Label"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_CERTIFIED_ID, "Certified Attribute Certified Id"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_CERTIFIED_NAME, "Certified Attribute Name"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_CERTIFIED_LABEL, "Certified Attribute Label"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_CERTIFIED_VALUE, "Certified Attribute Value"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_CERTIFIED_DESCRIPTION, "Certified Attribute Description"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TITLE_ID, "Title Attribute Id"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TITLE_CATEGORY, "Title Attribute Category"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TITLE_TEXT, "Title Attribute Text"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TITLE_COLOR, "Title Attribute Color"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TITLE_GLOWCOLOR, "Title Attribute Glow Color"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_SPECIAL_ID, "Special Attribute Id"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_SPECIAL_NAME, "Special Attribute Name"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_SPECIAL_LABEL, "Special Attribute Label"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TEAM_ID, "Team Attribute Id"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TEAM_NAME, "Team Attribute Name"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_TEAM_LABEL, "Team Attribute Label"));
		attributeLabels.insert(std::make_pair<AttributeParameters, std::string>(AttributeParameters::ATTRIBUTE_BLUEPRINT_COST, "Blueprint Attribute Cost"));

		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_ID, "Paint Database Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_NAME, "Paint Database Name"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_LABEL, "Paint Database Label"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_COLORS, "Paint Database Colors"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_FINISH_ID, "Paint Database Finish Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_PAINT_FINISH_LABEL, "Paint Database Finish Label"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_CERTIFIED_ID, "Certified Database Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_CERTIFIED_NAME, "Certified Database Name"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_CERTIFIED_LABEL, "Certified Database Label"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_CERTIFIED_DESCRIPTION, "Certified Database Description"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_SPECIAL_ID, "Special Database Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_SPECIAL_NAME, "Special Database Name"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_SPECIAL_LABEL, "Special Database Label"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TITLE_ID, "Title Database Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TITLE_CATEGORY, "Title Database Category"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TITLE_TEXT, "Title Database Text"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TITLE_COLOR, "Title Database Color"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TITLE_GLOWCOLOR, "Title Database Glow"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TEAM_ID, "Team Database Id"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TEAM_NAME, "Team Database Name"));
		databaseLabels.insert(std::make_pair<DatabaseParameters, std::string>(DatabaseParameters::DATABASE_TEAM_LABEL, "Team Database Label"));

		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_ID, "Playlist Id"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_TITLE, "Playlist Title"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_DESCRIPTION, "Playlist Description"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_PLAYERCOUNT, "Playlist Player Count"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_STANDARD, "Playlist Standard"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_RANKED, "Playlist Ranked"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_SOLO, "Playlist Solo"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_EXTRAMODE, "Playlist Extra Mode"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_PRIVATE, "Playlist Private"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_TOURNAMENT, "Playlist Tournament"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_APPLYQUITPENALTY, "Playlist Quit Penalty"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_ALLOWFORFIET, "Playlist Allow Forfiet"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_DISABLERECONNECT, "Playlist Disable Reconnect"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_IGNOREASSIGNTEAMS, "Playlist Ignore Assign Teams"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_ALLOWBOTFILLS, "Playlist Allow Bot Fills"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_KICKONMIGRATE, "Playlist Kick On Migrate"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_CHECKRESERVATION, "Playlist Check Reservation"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_ISMICROEVENT, "Playlist Microevent"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_HASVARIABLEPLAYERCOUNT, "Playlist Variable Player Count"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_NEW, "Playlist New"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_ALLOWCLUBS, "Playlist Allow Clubs"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_BOOL_ALLOWSTAYASPARTY, "Playlist Allow Stay Party"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_IMAGE_URL, "Playlist Image Url"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_IMAGE_TEXTURE, "Playlist Image Texture"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_ICON_ACTIVE_URL, "Playlist Icon Active Url"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_ICON_INACTIVE_URL, "Playlist Icon Inactive Url"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_MAP_NAME, "Playlist Map Name"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_SERVER_COMMAND, "Playlist Server Command"));
		playlistLabels.insert(std::make_pair<PlaylistParameters, std::string>(PlaylistParameters::PLAYLIST_MAPSET_NAME, "Playlist Mapset Name"));

		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_WEATHER_VARIANT_ID, "Map Weather Variant Id"));
		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_WEATHER_VARIANT_NAME, "Map Weather Variant Name"));
		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_RANDOM_WEIGHT, "Map Random Weight"));
		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_VARIANT_NAME, "Map Variant Name"));
		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_BASE_NAME, "Map Base Name"));
		mapLabels.insert(std::make_pair<MapParameters, std::string>(MapParameters::MAP_FILE_NAME, "Map File Name"));

		mutatorLabels.insert(std::make_pair<MutatorParameters, std::string>(MutatorParameters::MUTATOR_PRESET_TAGS, "Mutator Preset Tags"));
		mutatorLabels.insert(std::make_pair<MutatorParameters, std::string>(MutatorParameters::MUTATOR_CATEGORY, "Mutator Category"));
		mutatorLabels.insert(std::make_pair<MutatorParameters, std::string>(MutatorParameters::MUTATOR_SETTING, "Mutator Settings"));
		mutatorLabels.insert(std::make_pair<MutatorParameters, std::string>(MutatorParameters::MUTATOR_REQUIRED_MAPS, "Mutator Required Maps"));
		mutatorLabels.insert(std::make_pair<MutatorParameters, std::string>(MutatorParameters::MUTATOR_OVERRIDE_NAME, "Mutator Override Name"));

		initialized = true;
	}

	if (parameter.GetCategory() == ParameterCategory::SLOT)
	{
		for (auto& slot : slotLabels)
		{
			if (static_cast<uint8_t>(slot.first) == parameter.GetType())
			{
				return slot.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::PRODUCT)
	{
		for (auto& product : productLabels)
		{
			if (static_cast<uint8_t>(product.first) == parameter.GetType())
			{
				return product.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::ONLINE)
	{
		for (auto& online : onlineLabels)
		{
			if (static_cast<uint8_t>(online.first) == parameter.GetType())
			{
				return online.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::ATTRIBUTE)
	{
		for (auto& attribute : attributeLabels)
		{
			if (static_cast<uint8_t>(attribute.first) == parameter.GetType())
			{
				return attribute.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		for (auto& database : databaseLabels)
		{
			if (static_cast<uint8_t>(database.first) == parameter.GetType())
			{
				return database.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::PLAYLIST)
	{
		for (auto& playlist : playlistLabels)
		{
			if (static_cast<uint8_t>(playlist.first) == parameter.GetType())
			{
				return playlist.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::MAP)
	{
		for (auto& map : mapLabels)
		{
			if (static_cast<uint8_t>(map.first) == parameter.GetType())
			{
				return map.second;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::MUTATOR)
	{
		for (auto& mutator : mutatorLabels)
		{
			if (static_cast<uint8_t>(mutator.first) == parameter.GetType())
			{
				return mutator.second;
			}
		}
	}
	
	return "Unknown";
}

std::string DeveloperTools::GetCSVHeader(const std::vector<ParameterPair>& parameters)
{
	std::string returnValue;

	for (size_t i = 0; i < parameters.size(); i++)
	{
		returnValue += GetParameterLabel(parameters[i]);

		if (i < (parameters.size() - 1))
		{
			returnValue += ", ";
		}
	}

	return returnValue;
}

std::vector<ParameterPair> DeveloperTools::GetParameters(const std::string& parameterString)
{
	std::map<size_t, ParameterPair> parameterMap;
	std::vector<ParameterPair> returnParams;

	// Sorting is done by the position returned by std::string::find.
	// Since we have the position "size_t" in the key type in "paramMap" it automatically sorts for us when we insert a new pair.

	parameterMap.insert(std::make_pair(parameterString.find("{slot_label}"), ParameterPair(ParameterCategory::SLOT, static_cast<uint32_t>(SlotParameters::SLOT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{slot_plural_label}"), ParameterPair(ParameterCategory::SLOT, static_cast<uint32_t>(SlotParameters::SLOT_PLURAL_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{slot_description}"), ParameterPair(ParameterCategory::SLOT, static_cast<uint32_t>(SlotParameters::SLOT_DESCRIPTION))));
	parameterMap.insert(std::make_pair(parameterString.find("{slot_online_label}"), ParameterPair(ParameterCategory::SLOT, static_cast<uint32_t>(SlotParameters::SLOT_ONLINE_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{slot_index}"), ParameterPair(ParameterCategory::SLOT, static_cast<uint32_t>(SlotParameters::SLOT_INDEX))));
	
	parameterMap.insert(std::make_pair(parameterString.find("{product_id}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_unlock_method_id}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_UNLOCK_METHOD_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_unlock_method_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_UNLOCK_METHOD_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_quality_id}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_QUALITY_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_quality_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_QUALITY_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_licensed}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_LICENSED))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_paintable}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_PAINTABLE))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_currency}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_CURRENCY))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_blueprint}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_BLUEPRINT))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_schematic}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_SCHEMATIC))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_bool_decryptor}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_BOOL_DECRYPTOR))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_asset_package}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_ASSET_PACKAGE))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_asset_path}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_ASSET_PATH))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_ascii_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_ASCII_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_long_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_LONG_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_short_ascii_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_SHORT_ASCII_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_short_sort_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_SHORT_SORT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_sort_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_SORT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_thumbnail_path}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_THUMBNAIL_PATH))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_thumbnail_package}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_THUMBNAIL_PACKAGE))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_thumbnail_asset}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_THUMBNAIL_ASSET))));
	parameterMap.insert(std::make_pair(parameterString.find("{product_trademark_label}"), ParameterPair(ParameterCategory::PRODUCT, static_cast<uint32_t>(ProductParameters::PRODUCT_TRADEMARK_LABEL))));

	parameterMap.insert(std::make_pair(parameterString.find("{online_instance_id}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_INSTANCE_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_series_id}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_SERIES_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_bool_tradable}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_BOOL_TRADABLE))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_added_timestamp}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_ADDED_TIMESTAMP))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_cached_sort_label}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_CACHED_SORT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_cached_sort_label}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_CACHED_SORT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_cached_short_sort_label}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_CACHED_SHORT_SORT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_cached_hash_id}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_CACHED_HASH_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_attribute_string}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_ATTRIBUTE_STRING))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_blueprint_series_id}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_blueprint_series_label}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_blueprint_type_id}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{online_blueprint_type_label}"), ParameterPair(ParameterCategory::ONLINE, static_cast<uint32_t>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_LABEL))));
	
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_painted_id}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_PAINTED_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_painted_name}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_PAINTED_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_painted_label}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_PAINTED_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_certified_id}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_certified_name}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_certified_label}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_certified_value}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_VALUE))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_certified_description}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_DESCRIPTION))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_title_id}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TITLE_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_title_category}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TITLE_CATEGORY))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_title_text}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TITLE_TEXT))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_title_color}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TITLE_COLOR))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_title_glowcolor}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TITLE_GLOWCOLOR))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_special_id}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_SPECIAL_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_special_name}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_SPECIAL_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_special_label}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_SPECIAL_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_team_id}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TEAM_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_team_name}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TEAM_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_team_label}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_TEAM_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{attribute_blueprint_cost}"), ParameterPair(ParameterCategory::ATTRIBUTE, static_cast<uint32_t>(AttributeParameters::ATTRIBUTE_BLUEPRINT_COST))));
	
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_name}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_label}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_colors}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_COLORS))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_finish_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_FINISH_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_paint_finish_label}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_PAINT_FINISH_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_certified_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_CERTIFIED_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_certified_name}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_CERTIFIED_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_certified_label}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_CERTIFIED_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_certified_description}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_CERTIFIED_DESCRIPTION))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_special_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_SPECIAL_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_special_name}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_SPECIAL_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_special_label}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_SPECIAL_LABEL))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_title_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TITLE_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_title_category}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TITLE_CATEGORY))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_title_text}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TITLE_TEXT))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_title_color}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TITLE_COLOR))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_title_glowcolor}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TITLE_GLOWCOLOR))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_team_id}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TEAM_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_team_name}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TEAM_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{database_team_label}"), ParameterPair(ParameterCategory::DATABASE, static_cast<uint32_t>(DatabaseParameters::DATABASE_TEAM_LABEL))));

	parameterMap.insert(std::make_pair(parameterString.find("{playlist_id}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_title}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_TITLE))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_description}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_DESCRIPTION))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_player_count}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_PLAYERCOUNT))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_standard}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_STANDARD))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_ranked}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_RANKED))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_solo}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_SOLO))));
	parameterMap.insert(std::make_pair(parameterString.find("{palylist_bool_extramode}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_EXTRAMODE))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_private}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_PRIVATE))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_tournament}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_TOURNAMENT))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_applyquitpenalty}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_APPLYQUITPENALTY))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_allowforfiet}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWFORFIET))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_disablereconnect}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_DISABLERECONNECT))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_ignoreassignteams}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_IGNOREASSIGNTEAMS))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_allowbotfills}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWBOTFILLS))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_kickonmigrate}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_KICKONMIGRATE))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_checkreservation}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_CHECKRESERVATION))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_ismicroevent}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_ISMICROEVENT))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_hasvariableplayercount}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_HASVARIABLEPLAYERCOUNT))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_new}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_NEW))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_allowclubs}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWCLUBS))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_bool_allowstayasparty}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWSTAYASPARTY))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_image_url}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_IMAGE_URL))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_image_texture}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_IMAGE_TEXTURE))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_icon_active_url}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_ICON_ACTIVE_URL))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_icon_inactive_url}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_ICON_INACTIVE_URL))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_map_name}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_MAP_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_server_command}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_SERVER_COMMAND))));
	parameterMap.insert(std::make_pair(parameterString.find("{playlist_mapset_name}"), ParameterPair(ParameterCategory::PLAYLIST, static_cast<uint32_t>(PlaylistParameters::PLAYLIST_MAPSET_NAME))));

	parameterMap.insert(std::make_pair(parameterString.find("{map_weather_variant_id}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_WEATHER_VARIANT_ID))));
	parameterMap.insert(std::make_pair(parameterString.find("{map_weather_variant_name}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_WEATHER_VARIANT_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{map_random_weight}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_RANDOM_WEIGHT))));
	parameterMap.insert(std::make_pair(parameterString.find("{map_variant_name}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_VARIANT_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{map_base_name}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_BASE_NAME))));
	parameterMap.insert(std::make_pair(parameterString.find("{map_file_name}"), ParameterPair(ParameterCategory::MAP, static_cast<uint32_t>(MapParameters::MAP_FILE_NAME))));

	parameterMap.insert(std::make_pair(parameterString.find("{mutator_preset_tags}"), ParameterPair(ParameterCategory::MUTATOR, static_cast<uint32_t>(MutatorParameters::MUTATOR_PRESET_TAGS))));
	parameterMap.insert(std::make_pair(parameterString.find("{mutator_category}"), ParameterPair(ParameterCategory::MUTATOR, static_cast<uint32_t>(MutatorParameters::MUTATOR_CATEGORY))));
	parameterMap.insert(std::make_pair(parameterString.find("{mutator_setting}"), ParameterPair(ParameterCategory::MUTATOR, static_cast<uint32_t>(MutatorParameters::MUTATOR_SETTING))));
	parameterMap.insert(std::make_pair(parameterString.find("{mutator_required_maps}"), ParameterPair(ParameterCategory::MUTATOR, static_cast<uint32_t>(MutatorParameters::MUTATOR_REQUIRED_MAPS))));
	parameterMap.insert(std::make_pair(parameterString.find("{mutator_override_name}"), ParameterPair(ParameterCategory::MUTATOR, static_cast<uint32_t>(MutatorParameters::MUTATOR_OVERRIDE_NAME))));

	for (std::map<size_t, ParameterPair>::iterator param = parameterMap.begin(); param != parameterMap.end(); param++)
	{
		if (param->first != std::string::npos)
		{
			returnParams.push_back(param->second);
		}
	}

	return returnParams;
}

std::string DeveloperTools::ColorToHex(struct FColor& color, const bool& includeHead)
{
	int32_t colorDecimal = ((color.R & 0xff) << 16) | ((color.G & 0xff) << 8) | (color.B & 0xff);

	std::string hexDigits = "0123456789ABCDEF";
	std::string hexColor;

	for (int32_t i = (3 * 2) - 1; i >= 0; i--)
	{
		hexColor += hexDigits[((colorDecimal >> i * 4) & 0xF)];
	}

	if (includeHead)
	{
		hexColor = "#" + hexColor;
	}

	return hexColor;
}

class UProduct_TA* DeveloperTools::GetProductFromId(const int32_t& productId)
{
	if (AreClassesSafe())
	{
		if (IUProductDatabase_TA)
		{
			for (UProduct_TA* product : IUProductDatabase_TA->Products_New)
			{
				if (product && product->GetID() == productId)
				{
					return product;
				}
			}
		}
		else
		{
			ClassesSafe = false;
		}
	}
	else
	{
		cvarManager->log("(GetProductFromId) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}

	return nullptr;
}

std::string DeveloperTools::GetValueFromSlot(class UProductSlot_TA* slot, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::SLOT)
	{
		if (parameter.GetType() == static_cast<uint8_t>(SlotParameters::SLOT_LABEL))
		{
			returnValue = slot->Label.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(SlotParameters::SLOT_PLURAL_LABEL))
		{
			returnValue = slot->PluralLabel.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(SlotParameters::SLOT_DESCRIPTION))
		{
			returnValue = slot->Description.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(SlotParameters::SLOT_ONLINE_LABEL))
		{
			returnValue = slot->OnlineLabel.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(SlotParameters::SLOT_INDEX))
		{
			returnValue = std::to_string(slot->SlotIndex);
			outCategory = FieldsCategory::INTEGER;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromProduct(class UOnlineProduct_TA* onlineProduct, class UProduct_TA* offlineProduct, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::SLOT)
	{
		returnValue = GetValueFromSlot(offlineProduct->Slot, parameter, outCategory);
	}
	else if (parameter.GetCategory() == ParameterCategory::ATTRIBUTE)
	{
		returnValue = GetValueFromAttribute(onlineProduct, parameter, outCategory);

		if (returnValue == "Unknown")
		{
			returnValue = "None";
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::ONLINE)
	{
		if (onlineProduct)
		{
			if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_INSTANCE_ID))
			{
				returnValue = std::to_string(onlineProduct->InstanceID);
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_SERIES_ID))
			{
				returnValue = std::to_string(onlineProduct->SeriesID);
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_BOOL_TRADABLE))
			{
				if (onlineProduct->GetIsUntradeable()) { returnValue = "false"; }
				else { returnValue = "true"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_ADDED_TIMESTAMP))
			{
				returnValue = std::to_string(onlineProduct->AddedTimestamp);
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_CACHED_SORT_LABEL))
			{
				returnValue = onlineProduct->CachedSortLabel.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_CACHED_SHORT_SORT_LABEL))
			{
				returnValue = onlineProduct->CachedShortSortLabel.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_CACHED_HASH_ID))
			{
				returnValue = std::to_string(onlineProduct->CachedHash.Id);
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_ATTRIBUTE_STRING))
			{
				returnValue = onlineProduct->GetAttributeString(TArray<UClass*>{}).ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_ID))
			{
				returnValue = std::to_string(onlineProduct->GetBlueprintSeriesID());
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_BLUEPRINT_SERIES_LABEL))
			{
				IUGFxData_ProductFilter_TA->InitProductSeriesIDs();

				bool found = false;
				int32_t blueprintSeries = onlineProduct->GetBlueprintSeriesID();

				for (FFilterProductSeries& series : IUGFxData_ProductFilter_TA->SeriesIDs)
				{
					if (series.SeriesID == blueprintSeries)
					{
						returnValue = series.Label.ToString();
						found = true;
						break;
					}
				}

				if (!found)
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_ID))
			{
				returnValue = std::to_string(static_cast<int32_t>(onlineProduct->GetBlueprintType()));
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(OnlineParameters::ONLINE_BLUEPRINT_TYPE_LABEL))
			{
				EBlueprintType blueprintType = static_cast<EBlueprintType>(onlineProduct->GetBlueprintType());

				if (blueprintType == EBlueprintType::BlueprintType_Unrevealed)
				{
					returnValue = "Unrevealed";
				}
				else if (blueprintType == EBlueprintType::BlueprintType_Revealed)
				{
					returnValue = "Revealed";
				}
				else if (blueprintType == EBlueprintType::BlueprintType_NotABlueprint)
				{
					returnValue = "Not A Blueprint";
				}

				outCategory = FieldsCategory::STRING;
			}
		}
	}
	else if (parameter.GetCategory() == ParameterCategory::PRODUCT)
	{
		if (offlineProduct)
		{
			if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_ID))
			{
				returnValue = std::to_string(offlineProduct->GetID());
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_UNLOCK_METHOD_ID))
			{
				returnValue = std::to_string(static_cast<int32_t>(offlineProduct->UnlockMethod));
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_UNLOCK_METHOD_LABEL))
			{
				switch (static_cast<EUnlockMethod>(offlineProduct->UnlockMethod))
				{
				case EUnlockMethod::UnlockMethod_Default:
					returnValue = "Default";
					break;
				case EUnlockMethod::UnlockMethod_Online:
					returnValue = "Online";
					break;
				case EUnlockMethod::UnlockMethod_DLC:
					returnValue = "DLC";
					break;
				case EUnlockMethod::UnlockMethod_Never:
					returnValue = "Never";
					break;
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_QUALITY_ID))
			{
				returnValue = std::to_string(static_cast<int32_t>(offlineProduct->Quality));
				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_QUALITY_LABEL))
			{
				returnValue = IU_Types_TA->ProductQualityToString(offlineProduct->Quality).ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_LICENSED))
			{
				if (offlineProduct->bLicensed) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_PAINTABLE))
			{
				if (offlineProduct->IsPaintable()) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_CURRENCY))
			{
				if (offlineProduct->IsCurrency()) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_BLUEPRINT))
			{
				if (offlineProduct->IsBlueprint()) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_SCHEMATIC))
			{
				if (offlineProduct->IsSchematic()) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_BOOL_DECRYPTOR))
			{
				if (offlineProduct->IsExactlyDecryptor()) { returnValue = "true"; }
				else { returnValue = "false"; }

				outCategory = FieldsCategory::BOOL;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_ASSET_PACKAGE))
			{
				returnValue = offlineProduct->AssetPackageName.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_ASSET_PATH))
			{
				returnValue = offlineProduct->AssetPath.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_LABEL))
			{
				returnValue = offlineProduct->Label.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_ASCII_LABEL))
			{
				returnValue = offlineProduct->AsciiLabel.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_LONG_LABEL))
			{
				returnValue = offlineProduct->LongLabel.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_SHORT_ASCII_LABEL))
			{
				returnValue = offlineProduct->ShortAsciiLabel.ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_SHORT_SORT_LABEL))
			{
				returnValue = offlineProduct->GetShortSortLabel().ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_SORT_LABEL))
			{
				returnValue = offlineProduct->GetSortLabel().ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_THUMBNAIL_PATH))
			{
				returnValue = offlineProduct->GetThumbnailAssetPath().ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_THUMBNAIL_PACKAGE))
			{
				returnValue = offlineProduct->GetThumbnailPackageName().ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_THUMBNAIL_ASSET))
			{
				returnValue = offlineProduct->GetThumbnailAssetName().ToString();
				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(ProductParameters::PRODUCT_TRADEMARK_LABEL))
			{
				returnValue = offlineProduct->GetTrademarkLabel().ToString();
				outCategory = FieldsCategory::STRING;
			}
		}
	}

	if (returnValue == "null")
	{
		returnValue == "None";
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromAttribute(class UOnlineProduct_TA* onlineProduct, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::ATTRIBUTE)
	{
		if (onlineProduct)
		{
			if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_PAINTED_ID))
			{
				UProductAttribute_Painted_TA* paintAttribute = reinterpret_cast<UProductAttribute_Painted_TA*>(onlineProduct->GetAttribute(UProductAttribute_Painted_TA::StaticClass()));

				if (paintAttribute)
				{
					returnValue = std::to_string(paintAttribute->PaintID);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_PAINTED_NAME))
			{
				UProductAttribute_Painted_TA* paintAttribute = reinterpret_cast<UProductAttribute_Painted_TA*>(onlineProduct->GetAttribute(UProductAttribute_Painted_TA::StaticClass()));

				if (paintAttribute)
				{
					returnValue = IUPaintDatabase_TA->GetPaintName(paintAttribute->PaintID).ToString();
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_PAINTED_LABEL))
			{
				UProductAttribute_Painted_TA* paintAttribute = reinterpret_cast<UProductAttribute_Painted_TA*>(onlineProduct->GetAttribute(UProductAttribute_Painted_TA::StaticClass()));

				if (paintAttribute)
				{
					returnValue = IUPaintDatabase_TA->GetPaint(paintAttribute->PaintID)->Label.ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_ID))
			{
				UProductAttribute_Certified_TA* certifiedAttribute = reinterpret_cast<UProductAttribute_Certified_TA*>(onlineProduct->GetAttribute(UProductAttribute_Certified_TA::StaticClass()));

				if (certifiedAttribute)
				{
					returnValue = std::to_string(certifiedAttribute->StatId);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_NAME))
			{
				UProductAttribute_Certified_TA* certifiedAttribute = reinterpret_cast<UProductAttribute_Certified_TA*>(onlineProduct->GetAttribute(UProductAttribute_Certified_TA::StaticClass()));

				if (certifiedAttribute)
				{
					returnValue = IUCertifiedStatDatabase_TA->GetStatName(certifiedAttribute->StatId).ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_LABEL))
			{
				UProductAttribute_Certified_TA* certifiedAttribute = reinterpret_cast<UProductAttribute_Certified_TA*>(onlineProduct->GetAttribute(UProductAttribute_Certified_TA::StaticClass()));

				if (certifiedAttribute)
				{
					returnValue = certifiedAttribute->GetRankLabel().ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_VALUE))
			{
				UProductAttribute_Certified_TA* certifiedAttribute = reinterpret_cast<UProductAttribute_Certified_TA*>(onlineProduct->GetAttribute(UProductAttribute_Certified_TA::StaticClass()));

				if (certifiedAttribute)
				{
					returnValue = std::to_string(certifiedAttribute->StatValue);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_CERTIFIED_DESCRIPTION))
			{
				UProductAttribute_Certified_TA* certifiedAttribute = reinterpret_cast<UProductAttribute_Certified_TA*>(onlineProduct->GetAttribute(UProductAttribute_Certified_TA::StaticClass()));

				if (certifiedAttribute)
				{
					returnValue = certifiedAttribute->GetDescription().ToString();

					size_t pos = returnValue.find(",");

					if (pos != std::string::npos)
					{
						returnValue = returnValue.replace(pos, 1, "\,");
					}
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TITLE_ID))
			{
				UProductAttribute_TitleID_TA* titleAttribute = reinterpret_cast<UProductAttribute_TitleID_TA*>(onlineProduct->GetAttribute(UProductAttribute_TitleID_TA::StaticClass()));

				if (titleAttribute)
				{
					returnValue = titleAttribute->TitleId.ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TITLE_CATEGORY))
			{
				UProductAttribute_TitleID_TA* titleAttribute = reinterpret_cast<UProductAttribute_TitleID_TA*>(onlineProduct->GetAttribute(UProductAttribute_TitleID_TA::StaticClass()));

				if (titleAttribute)
				{
					returnValue = IUPlayerTitleConfig_X->GetTitleData(titleAttribute->TitleId).Category.ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TITLE_TEXT))
			{
				UProductAttribute_TitleID_TA* titleAttribute = reinterpret_cast<UProductAttribute_TitleID_TA*>(onlineProduct->GetAttribute(UProductAttribute_TitleID_TA::StaticClass()));

				if (titleAttribute)
				{
					returnValue = IUPlayerTitleConfig_X->GetTitleData(titleAttribute->TitleId).Text.ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TITLE_COLOR))
			{
				UProductAttribute_TitleID_TA* titleAttribute = reinterpret_cast<UProductAttribute_TitleID_TA*>(onlineProduct->GetAttribute(UProductAttribute_TitleID_TA::StaticClass()));

				if (titleAttribute)
				{
					FColor textColor = IUPlayerTitleConfig_X->GetTitleData(titleAttribute->TitleId).Color;

					returnValue = ColorToHex(textColor, true);
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TITLE_GLOWCOLOR))
			{
				UProductAttribute_TitleID_TA* titleAttribute = reinterpret_cast<UProductAttribute_TitleID_TA*>(onlineProduct->GetAttribute(UProductAttribute_TitleID_TA::StaticClass()));

				if (titleAttribute)
				{
					FColor glowColor = IUPlayerTitleConfig_X->GetTitleData(titleAttribute->TitleId).GlowColor;

					returnValue = ColorToHex(glowColor, true);
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_SPECIAL_ID))
			{
				UProductAttribute_SpecialEdition_TA* specialAttribute = reinterpret_cast<UProductAttribute_SpecialEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_SpecialEdition_TA::StaticClass()));

				if (specialAttribute)
				{
					returnValue = std::to_string(specialAttribute->EditionID);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_SPECIAL_NAME))
			{
				UProductAttribute_SpecialEdition_TA* specialAttribute = reinterpret_cast<UProductAttribute_SpecialEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_SpecialEdition_TA::StaticClass()));

				if (specialAttribute)
				{
					returnValue = IUSpecialEditionDatabase_TA->GetSpecialEditionName(specialAttribute->EditionID).ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_SPECIAL_LABEL))
			{
				UProductAttribute_SpecialEdition_TA* specialAttribute = reinterpret_cast<UProductAttribute_SpecialEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_SpecialEdition_TA::StaticClass()));

				if (specialAttribute)
				{
					returnValue = IUSpecialEditionDatabase_TA->GetSpecialEdition(specialAttribute->EditionID)->Label.ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TEAM_ID))
			{
				UProductAttribute_TeamEdition_TA* teamAttribute = reinterpret_cast<UProductAttribute_TeamEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_TeamEdition_TA::StaticClass()));

				if (teamAttribute)
				{
					returnValue = std::to_string(teamAttribute->Id);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TEAM_NAME))
			{
				UProductAttribute_TeamEdition_TA* teamAttribute = reinterpret_cast<UProductAttribute_TeamEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_TeamEdition_TA::StaticClass()));

				if (teamAttribute)
				{
					returnValue = IUDataAssetDatabase_ESportsTeam_TA->GetName(teamAttribute->Id).ToString();
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_TEAM_LABEL))
			{
				UProductAttribute_TeamEdition_TA* teamAttribute = reinterpret_cast<UProductAttribute_TeamEdition_TA*>(onlineProduct->GetAttribute(UProductAttribute_TeamEdition_TA::StaticClass()));

				if (teamAttribute)
				{
					UProductAsset_ESportsTeam_TA* productAssetTeam = reinterpret_cast<UProductAsset_ESportsTeam_TA*>(IUProductAssetLoader_TA->LoadAsset(onlineProduct->ProductID));

					if (productAssetTeam)
					{
						returnValue = productAssetTeam->TeamName.ToString();
					}
					else
					{
						returnValue = "None";
					}
				}
				else
				{
					returnValue = "None";
				}

				outCategory = FieldsCategory::STRING;
			}
			else if (parameter.GetType() == static_cast<uint8_t>(AttributeParameters::ATTRIBUTE_BLUEPRINT_COST))
			{
				UProductAttribute_BlueprintCost_TA* costAttribute = reinterpret_cast<UProductAttribute_BlueprintCost_TA*>(onlineProduct->GetAttribute(UProductAttribute_BlueprintCost_TA::StaticClass()));

				if (costAttribute)
				{
					returnValue = std::to_string(costAttribute->Cost);
				}
				else
				{
					returnValue = "-1";
				}

				outCategory = FieldsCategory::INTEGER;
			}
		}
		else
		{
			returnValue = "None";
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromMap(class UMapData_TA* map, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::MAP)
	{
		if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_WEATHER_VARIANT_ID))
		{
			returnValue = std::to_string(static_cast<int32_t>(map->WeatherVariant));
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_WEATHER_VARIANT_NAME))
		{
			returnValue = map->GetLocalizedVariantName().ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_RANDOM_WEIGHT))
		{
			returnValue = std::to_string(map->RandomWeight);
			outCategory = FieldsCategory::FLOAT;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_VARIANT_NAME))
		{
			returnValue = map->GetLocalizedVariantName().ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_BASE_NAME))
		{
			returnValue = map->GetLocalizedBaseName().ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(MapParameters::MAP_FILE_NAME))
		{
			returnValue = map->GetFullName();
			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
		else
		{
			size_t pos1 = returnValue.find("MapData_TA MapList.");

			if (pos1 != std::string::npos)
			{
				returnValue = returnValue.replace(pos1, 19, "");

				size_t pos2 = returnValue.find("Maps.");

				if (pos2 != std::string::npos)
				{
					returnValue = returnValue.replace(pos1, 5, "");
				}
			}
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromPlaylist(class UPlaylistSettings_X* playlist, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::PLAYLIST)
	{
		if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_ID))
		{
			returnValue = std::to_string(playlist->PlaylistId);
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_TITLE))
		{
			returnValue = playlist->Title.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_DESCRIPTION))
		{
			returnValue = playlist->Description.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_PLAYERCOUNT))
		{
			returnValue = std::to_string(playlist->PlayerCount);
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_STANDARD))
		{
			if (playlist->bStandard) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_RANKED))
		{
			if (playlist->bRanked) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_SOLO))
		{
			if (playlist->bSolo) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_EXTRAMODE))
		{
			if (playlist->bExtraMode) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_PRIVATE))
		{
			if (playlist->bPrivate) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_TOURNAMENT))
		{
			if (playlist->bTournament) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_APPLYQUITPENALTY))
		{
			if (playlist->bApplyQuitPenalty) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWFORFIET))
		{
			if (playlist->bAllowForfeit) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_DISABLERECONNECT))
		{
			if (playlist->bDisableRankedReconnect) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_IGNOREASSIGNTEAMS))
		{
			if (playlist->bIgnoreAssignTeams) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWBOTFILLS))
		{
			if (playlist->bAllowBotFills) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_KICKONMIGRATE))
		{
			if (playlist->bKickOnMigrate) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_CHECKRESERVATION))
		{
			if (playlist->bCheckRankedMatchReservationID) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ISMICROEVENT))
		{
			if (playlist->bIsMicroEventPlaylist) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_HASVARIABLEPLAYERCOUNT))
		{
			if (playlist->bHasVariablePlayerCount) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_NEW))
		{
			if (playlist->bNew) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWCLUBS))
		{
			if (playlist->bAllowClubs) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWSTAYASPARTY))
		{
			if (playlist->bAllowStayAsParty) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_BOOL_ALLOWCLUBS))
		{
			if (playlist->bAllowClubs) { returnValue = "true"; }
			else { returnValue = "false"; }

			outCategory = FieldsCategory::BOOL;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_IMAGE_URL))
		{
			returnValue = playlist->PlaylistImageURL.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_IMAGE_TEXTURE))
		{
			returnValue = playlist->PlaylistImageTexture.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_ICON_ACTIVE_URL))
		{
			returnValue = playlist->PlaylistIconActiveURL.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_ICON_INACTIVE_URL))
		{
			returnValue = playlist->PlaylistIconInactiveURL.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_MAP_NAME))
		{
			returnValue = playlist->MapName.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_SERVER_COMMAND))
		{
			returnValue = playlist->ServerCommand.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(PlaylistParameters::PLAYLIST_MAPSET_NAME))
		{
			returnValue = playlist->MapSetName.ToString();
			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromPaint(class UProductPaint_TA* paint, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_ID))
		{
			returnValue = std::to_string(paint->GetID());
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_NAME))
		{
			returnValue = IUPaintDatabase_TA->GetPaintName(paint->GetID()).ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_LABEL))
		{
			returnValue = paint->Label.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_COLORS))
		{
			returnValue = "";

			for (int32_t i = 0; i < 12; i++)
			{
				FColor color = paint->LinearColorToColor(paint->Colors[i]);

				returnValue += ColorToHex(color, true);

				if (i != 11)
				{
					returnValue += "|";
				}
			}

			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_FINISH_ID))
		{
			returnValue = std::to_string(static_cast<int>(paint->FinishType));
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_PAINT_FINISH_LABEL))
		{
			EPaintFinishType finishType = static_cast<EPaintFinishType>(paint->FinishType);

			if (finishType == EPaintFinishType::PaintFinishType_Standard)
			{
				returnValue = "Standard";
			}
			else if (finishType == EPaintFinishType::PaintFinishType_Metallic)
			{
				returnValue = "Metallic";
			}
			else
			{
				returnValue = "None";
			}

			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromCertification(class UCertifiedStat_TA* certification, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_CERTIFIED_ID))
		{
			returnValue = std::to_string(certification->GetID());
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_CERTIFIED_NAME))
		{
			returnValue = IUCertifiedStatDatabase_TA->GetStatName(certification->GetID()).ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_CERTIFIED_LABEL))
		{
			returnValue = certification->GetRankLabel(0).ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_CERTIFIED_DESCRIPTION))
		{
			returnValue = certification->GetDescription().ToString();

			size_t pos = returnValue.find(",");

			if (pos != std::string::npos)
			{
				returnValue = returnValue.replace(pos, 1, "\,");
			}

			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromSpecialEdition(class UProductSpecialEdition_TA* specialEdition, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_SPECIAL_ID))
		{
			returnValue = std::to_string(specialEdition->GetID());
			outCategory = FieldsCategory::INTEGER;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_SPECIAL_NAME))
		{
			returnValue = IUSpecialEditionDatabase_TA->GetSpecialEditionName(specialEdition->GetID()).ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_SPECIAL_LABEL))
		{
			returnValue = specialEdition->Label.ToString();
			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromTitle(struct FPlayerTitleData& titleData, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TITLE_ID))
		{
			returnValue = titleData.Id.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TITLE_CATEGORY))
		{
			returnValue = titleData.Category.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TITLE_TEXT))
		{
			returnValue = titleData.Text.ToString();
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TITLE_COLOR))
		{
			returnValue = ColorToHex(titleData.Color, true);
			outCategory = FieldsCategory::STRING;
		}
		else if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TITLE_GLOWCOLOR))
		{
			returnValue = ColorToHex(titleData.GlowColor, true);
			outCategory = FieldsCategory::STRING;
		}
	}

	return returnValue;
}

std::string DeveloperTools::GetValueFromTeamEdition(class UDataAsset_ESportsTeam_TA* teamAsset, const ParameterPair& parameter, FieldsCategory& outCategory)
{
	std::string returnValue = "Unknown";

	if (parameter.GetCategory() == ParameterCategory::DATABASE)
	{
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TEAM_ID))
		{
			returnValue = std::to_string(teamAsset->TeamID);
			outCategory = FieldsCategory::INTEGER;
		}
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TEAM_NAME))
		{
			returnValue = IUDataAssetDatabase_ESportsTeam_TA->GetName(teamAsset->TeamID).ToString();
			outCategory = FieldsCategory::STRING;
		}
		if (parameter.GetType() == static_cast<uint8_t>(DatabaseParameters::DATABASE_TEAM_LABEL))
		{
			UProductAsset_ESportsTeam_TA* productAssetTeam = reinterpret_cast<UProductAsset_ESportsTeam_TA*>(IUProductAssetLoader_TA->LoadAsset(teamAsset->ESportsTeamReference->ProductID));

			if (productAssetTeam)
			{
				returnValue = productAssetTeam->TeamName.ToString();
			}
			else
			{
				returnValue = "None";
			}

			outCategory = FieldsCategory::STRING;
		}

		if (returnValue == "null")
		{
			returnValue = "None";
		}
	}

	return returnValue;
}

void DeveloperTools::DumpFunctions()
{
	if (AreClassesSafe())
	{
		std::ofstream file(DumpPath.u8string() + "\\FunctionDump.txt");

		int totalFunctions = 0;

		for (UObject* uObject : *UObject::GObjObjects())
		{
			if (uObject)
			{
				if (uObject->IsA(UFunction::StaticClass()))
				{
					file << uObject->GetFullName() << "\n";
					totalFunctions++;
				}
			}
		}

		file.close();

		if (totalFunctions > 0)
		{
			cvarManager->log("(DumpFunctions) Successfully dumped " + std::to_string(totalFunctions) + " functions to \"FunctionDump.txt\"!");
		}
		else
		{
			ClassesSafe = false;
			cvarManager->log("(DumpFunctions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
		}
	}
}

void DeveloperTools::DumpTextures()
{
	if (AreClassesSafe())
	{
		std::ofstream file(DumpPath.u8string() + "\\TextureDump.txt");

		int totalTextures = 0;

		for (UObject* uObject : *UObject::GObjObjects())
		{
			if (uObject)
			{
				if (uObject->IsA(UTexture::StaticClass()))
				{
					file << uObject->GetFullName() << "\n";
					totalTextures++;
				}
			}
		}

		file.close();

		if (totalTextures > 0)
		{
			cvarManager->log("(DumpFunctions) Successfully dumped " + std::to_string(totalTextures) + " textures to \"TextureDump.txt\"!");
		}
		else
		{
			ClassesSafe = false;
			cvarManager->log("(DumpFunctions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
		}
	}
}

void DeveloperTools::DumpServices()
{
	if (AreClassesSafe())
	{
		std::ofstream file(DumpPath.u8string() + "\\ServicesDump.txt");

		int totalServices = 0;

		for (UObject* object : *UObject::GObjObjects())
		{
			if (object && object->IsA(URPC_X::StaticClass()))
			{
				URPC_X* rpc = reinterpret_cast<URPC_X*>(object);

				if (rpc->GetFullName().find("Default") != std::string::npos)
				{
					file << "Class: " << rpc->GetName() << std::endl;
					file << "Service: " << rpc->Service.ToString() << std::endl;
					file << "Version: " << std::to_string(rpc->Version) << std::endl;
					file << "AllowBatching: " << (rpc->bAllowBatching == 0 ? "false" : "true") << std::endl;
					file << "RequiresAuth: " << (rpc->bRequiresAuth == 0 ? "false" : "true") << std::endl << std::endl;

					totalServices++;
				}
			}
		}

		file.close();

		cvarManager->log("(DumpServices) Successfully dumped " + std::to_string(totalServices) + " services to \"ServicesDump.txt\"!");
	}
}

void DeveloperTools::DumpSlots(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpSlots) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalSlots = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UProductSlot_TA* slot : IUGameData_TA->ProductSlots)
			{
				if (slot)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromSlot(slot, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalSlots++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalSlots > 0)
			{
				ParametersToFile(fieldPairs, parameters, "SlotDump", format);

				cvarManager->log("(DumpSlots) Successfully dumped " + std::to_string(totalSlots) + " slots!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpSlots) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpSlots) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpSlots) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpProducts(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpProducts) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			std::vector<int32_t> safeProductIds;

			if (ProductLimiter)
			{
				ArrayWrapper<ProductWrapper> bmProducts = gameWrapper->GetItemsWrapper().GetAllProducts();

				for (ProductWrapper bm : bmProducts)
				{
					if (!bm.IsNull())
					{
						int32_t productId = bm.GetID();

						if (productId != 0)
						{
							safeProductIds.push_back(productId);
						}
					}
				}
			}

			int32_t totalProducts = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UProduct_TA* product : IUProductDatabase_TA->Products_New)
			{
				if (product)
				{
					int32_t productId = product->GetID();

					if (ProductLimiter)
					{
						if (std::find(safeProductIds.begin(), safeProductIds.end(), productId) == safeProductIds.end())
						{
							continue;
						}
					}

					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromProduct(nullptr, product, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalProducts++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalProducts > 0)
			{
				ParametersToFile(fieldPairs, parameters, "ProductDump", format);

				cvarManager->log("(DumpProducts) Successfully dumped " + std::to_string(totalProducts) + " products!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpProducts) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpProducts) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpProducts) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpInventory(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpInventory) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalProducts = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UOnlineProduct_TA* onlineProduct : IUSaveData_TA->OnlineProducts)
			{
				if (onlineProduct)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromProduct(onlineProduct, onlineProduct->GetProduct(), param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalProducts++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalProducts > 0)
			{
				ParametersToFile(fieldPairs, parameters, "InventoryDump", format);

				cvarManager->log("(DumpInventory) Successfully dumped " + std::to_string(totalProducts) + " products!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpInventory) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpInventory) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpInventory) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpPaints(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpPaints) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalPaints = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UProductPaint_TA* paint : IUPaintDatabase_TA->Paints)
			{
				if (paint)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromPaint(paint, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalPaints++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalPaints > 0)
			{
				ParametersToFile(fieldPairs, parameters, "PaintDump", format);

				cvarManager->log("(DumpPaints) Successfully dumped " + std::to_string(totalPaints) + " paints!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpPaints) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpPaints) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpPaints) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpCertifications(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpCertifications) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalCertifications = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UCertifiedStat_TA* stat : IUCertifiedStatDatabase_TA->Stats)
			{
				if (stat)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromCertification(stat, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalCertifications++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalCertifications > 0)
			{
				ParametersToFile(fieldPairs, parameters, "CertificationDump", format);

				cvarManager->log("(DumpCertifications) Successfully dumped " + std::to_string(totalCertifications) + " certifications!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpCertifications) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpCertifications) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpCertifications) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpSpecialEditions(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpSpecialEditions) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalEditions = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UProductSpecialEdition_TA* edition : IUSpecialEditionDatabase_TA->SpecialEditions)
			{
				if (edition)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromSpecialEdition(edition, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalEditions++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalEditions > 0)
			{
				ParametersToFile(fieldPairs, parameters, "SpecialEditionDump", format);

				cvarManager->log("(DumpSpecialEditions) Successfully dumped " + std::to_string(totalEditions) + " special editions!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpSpecialEditions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpSpecialEditions) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpSpecialEditions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpTitles(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpTitles) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalTitles = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (FPlayerTitleData& title : IUPlayerTitleConfig_X->Titles)
			{
				if (title.Id.IsValid())
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromTitle(title, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalTitles++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalTitles > 0)
			{
				ParametersToFile(fieldPairs, parameters, "TitleDump", format);

				cvarManager->log("(DumpTitles) Successfully dumped " + std::to_string(totalTitles) + " titles!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpTitles) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpTitles) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpTitles) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpTeamEditions(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpTeamEditions) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalEditions = 0;

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UObject* dataAsset : IUDataAssetDatabase_ESportsTeam_TA->DataAssets)
			{
				if (dataAsset)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromTeamEdition(reinterpret_cast<UDataAsset_ESportsTeam_TA*>(dataAsset), param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalEditions++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalEditions > 0)
			{
				ParametersToFile(fieldPairs, parameters, "TeamEditionDump", format);

				cvarManager->log("(DumpTeamEditions) Successfully dumped " + std::to_string(totalEditions) + " team editions!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpTeamEditions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpTeamEditions) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpTeamEditions) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpPlaylists(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpPlaylists) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalPlaylists = 0;

			std::vector<UPlaylistSettings_X*> playlists = Utils::GetAllInstancesOf<UPlaylistSettings_X>();

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UPlaylistSettings_X* playlist : playlists)
			{
				if (playlist)
				{
					UGameSettingPlaylist_X* gamePlaylist = IUOnlineGamePlaylists_X->GetPlaylistByID(playlist->PlaylistId);

					if (gamePlaylist)
					{
						if (PlaylistLimiter)
						{
							if (!IUOnlineGamePlaylists_X->IsPlaylistEnabled(gamePlaylist))
							{
								continue;
							}
						}

						fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

						for (ParameterPair& param : parameters)
						{
							FieldsCategory category;
							std::string name = GetParameterLabel(param);
							std::string value = GetValueFromPlaylist(playlist, param, category);

							fieldPairs.push_back(PairFields(category, name, value));
						}

						fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
						fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
						fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

						totalPlaylists++;
					}
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalPlaylists > 0)
			{
				ParametersToFile(fieldPairs, parameters, "PlaylistDump", format);

				cvarManager->log("(DumpPlaylists) Successfully dumped " + std::to_string(totalPlaylists) + " playlists!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpPlaylists) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpPlaylists) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpPlaylists) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpMaps(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpMaps) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			int32_t totalMaps = 0;

			TArray<UMapData_TA*> mapList;

			if (PlaylistLimiter)
			{
				mapList = IUMapList_TA->SortedMaps;
			}
			else
			{
				mapList = IUMapList_TA->AllMaps;
			}

			fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));

			for (UMapData_TA* map : mapList)
			{
				if (map)
				{
					fieldPairs.push_back(PairFields(FieldsCategory::JSONSTART, "JSS", "JSS"));

					for (ParameterPair& param : parameters)
					{
						FieldsCategory category;
						std::string name = GetParameterLabel(param);
						std::string value = GetValueFromMap(map, param, category);

						fieldPairs.push_back(PairFields(category, name, value));
					}

					fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);
					fieldPairs.push_back(PairFields(FieldsCategory::CSVLINE, "NL", "NL"));
					fieldPairs.push_back(PairFields(FieldsCategory::JSONEND, "JSE", "JSE"));

					totalMaps++;
				}
			}

			fieldPairs[fieldPairs.size() - 1].SetShouldComma(false);

			if (totalMaps > 0)
			{
				ParametersToFile(fieldPairs, parameters, "MapDump", format);

				cvarManager->log("(DumpMaps) Successfully dumped " + std::to_string(totalMaps) + " maps!");
			}
			else
			{
				ClassesSafe = false;
				cvarManager->log("(DumpMaps) Error: RLSDK Classes are wrong, please contact ItsBranK!");
			}
		}
		else
		{
			cvarManager->log("(DumpMaps) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpMaps) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DumpMutators(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		std::string fullCommand = GetFullCommand(params, true);
		DumpFormat format = GetFormat(fullCommand);

		if (format != DumpFormat::NONE)
		{
			std::vector<ParameterPair> parameters = GetParameters(fullCommand);
			std::vector<PairFields> fieldPairs;

			if (parameters.size() == 0)
			{
				cvarManager->log("(DumpMutators) Error: Please enter at least one parameter, view the README on GitHub for a full list of parameters!");
				return;
			}

			// To Do!
		}
		else
		{
			cvarManager->log("(DumpMutators) Error: Please enter input a format type, either [CSV] or [JSON] at the end of the command!");
		}
	}
	else
	{
		cvarManager->log("(DumpMutators) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::ToggleBrowseTextures(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		if (params.size() == 2)
		{
			if (params.at(1) == "true")
			{
				EraseTexture();

				std::vector<UTexture2D*> activeTextures = Utils::GetAllInstancesOf<UTexture2D>();	
				TexturesToBrowse = activeTextures;

				BrowseIndex = 0;
				DrawMode = DrawModes::DRAW_BROWSER;
			}
			else if (params.at(1) == "false")
			{
				EraseTexture();
			}
		}
		else
		{
			cvarManager->log("(ToggleBrowseTextures) Error: Please enter the correct parameters!");
		}
	}
}

void DeveloperTools::DrawTexture(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		if (params.size() == 2)
		{
			UTexture* texture = Utils::StaticLoadObject<UTexture>(params.at(1));

			if (texture)
			{
				TextureToLoad = texture->GetFullName();

				cvarManager->log("(DrawTexture): Found Texture: \"" + texture->GetFullName() + "\"");

				DrawMode = DrawModes::DRAW_TEXTURE;
			}
			else
			{
				EraseTexture();

				cvarManager->log("(DrawTexture) Error: Failed to find desired texture!");
			}
		}
		else
		{
			cvarManager->log("(DrawTexture) Error: Please enter the correct parameters!");
		}
	}
	else
	{
		cvarManager->log("(DrawTexture) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::DrawThumbnail(const std::vector<std::string>& params)
{
	if (AreClassesSafe())
	{
		if (params.size() == 2)
		{
			EraseTexture();

			int32_t productId = std::stoi(params.at(1));
			UProduct_TA* product = GetProductFromId(productId);

			if (product)
			{
				UProductAsset_TA* productAsset = IUProductAssetLoader_TA->LoadAsset(productId);
				UGFxData_Products_TA* products = Utils::GetInstanceOf<UGFxData_Products_TA>();

				if (products)
				{
					products->LoadProduct(product->GetHashID(), static_cast<uint8_t>(EProductThumbnailSize::PTS_Garage), ViewId, true);

					if (productAsset)
					{
						bool foundThumbnail = false;

						for (ULoadingProduct_TA* loading : products->LoadingProducts)
						{
							if (loading && loading->ProductID == productId)
							{
								if (loading->ThumbnailAsset && loading->ThumbnailAsset->Thumbnail)
								{
									foundThumbnail = true;
									TextureToLoad = loading->ThumbnailAsset->Thumbnail->GetFullName();
									DrawMode = DrawModes::DRAW_TEXTURE;

									cvarManager->log("(DrawThumbnail): Thumbnail found: \"" + TextureToLoad + "\".");

									break;
								}
							}
						}

						if (!foundThumbnail)
						{
							cvarManager->log("(DrawThumbnail): Error: Failed to find thumbnail for \"" + productAsset->GetThumbnailAssetName().ToString() + "\", try again to force render it!");
						}
					}
					else
					{
						cvarManager->log("(DrawThumbnail): Error: Failed to load assets for \"" + product->LongLabel.ToString() + "\"!");
					}
				}
				else
				{
					cvarManager->log("(DrawThumbnail): Error: Boi get your ass on the main menu so I can load this shit.");
				}
			}
			else
			{
				cvarManager->log("(DrawThumbnail): Product \"" + std::to_string(productId) + "\" does not exist!");
			}
		}
		else
		{
			cvarManager->log("(DrawThumbnail) Error: Please enter the correct parameters!");
		}
	}
	else
	{
		cvarManager->log("(DrawThumbnail) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::EraseTexture()
{
	if (AreClassesSafe())
	{
		DrawMode = DrawModes::NOT_DRAWING;
		BrowseIndex = 0;
		TexturesToBrowse.clear();
		TextureToLoad = "DeveloperTools";
	}
	else
	{
		cvarManager->log("(EraseTexture) Error: RLSDK Classes are wrong, please contact ItsBranK!");
	}
}

void DeveloperTools::GameViewPortKeyPress(ActorWrapper caller, void* params, const std::string& functionName)
{
	if (DrawMode == DrawModes::DRAW_BROWSER)
	{
		if (params)
		{
			UGameViewportClient_TA_execHandleKeyPress_Params* handleKeyPress = reinterpret_cast<UGameViewportClient_TA_execHandleKeyPress_Params*>(params);

			if (handleKeyPress->EventType == static_cast<uint8_t>(EInputEvent::IE_Released))
			{
				std::string keyPressed = handleKeyPress->Key.ToString();

				if (keyPressed == "Right" || keyPressed == "MouseScrollUp")
				{
					if (BrowseIndex >= TexturesToBrowse.size() - 1)
					{
						BrowseIndex = 0;
					}
					else
					{
						BrowseIndex++;
					}
				}
				else if (keyPressed == "Left" || keyPressed == "MouseScrollDown")
				{
					if (BrowseIndex <= 0)
					{
						BrowseIndex = TexturesToBrowse.size() - 1;
					}
					else
					{
						BrowseIndex--;
					}
				}
			}
		}
	}
}

void DeveloperTools::CanvasRender(ActorWrapper caller, void* params, const std::string& functionName)
{
	if (DrawMode != DrawModes::NOT_DRAWING && caller.memory_address)
	{
		AHUD* hud = reinterpret_cast<AHUD*>(caller.memory_address);
		CanvasWrapperB canvas(hud->Canvas);

		canvas.SetSafeToDraw(true);

		if (DrawMode == DrawModes::DRAW_TEXTURE)
		{
			UTexture* texture = Utils::StaticLoadObject<UTexture>(TextureToLoad);

			if (texture)
			{
				// Mode box.

				canvas.DrawFilledBox(FVector2D{ 50.f, 20.f }, 500, 55, FColorList::Black);
				canvas.DrawString(FVector2D{ 60.f, 30.f }, "Mode: Drawer, Forced Scale: 500x500, Background: Transparent", 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 60.f, 49.f }, "Texture: " + texture->GetFullName(), 1.f, FColorList::White);
				canvas.DrawBoxOutline(FVector2D{ 50.f, 20.f }, 500, 55, FColorList::Green);

				// Texture.
				
				canvas.DrawTextureScaled(FVector2D{ 50.f, 80.f }, texture, 500.f, 500.f);
				canvas.DrawBoxOutline(FVector2D{ 50.f, 80.f }, 500.f, 500.f, FColorList::Green);
			}
		}
		else if (DrawMode == DrawModes::DRAW_BROWSER)
		{
			UTexture2D* texture = TexturesToBrowse[BrowseIndex];
			Texture2DWrapper texture2D(texture);

			// Mode box.

			canvas.DrawFilledBox(FVector2D{ 50.f, 20.f }, 500, 30, FColorList::Black);
			canvas.DrawString(FVector2D{ 60.f, 27.f }, "Mode: Browser, Forced Scale: 500x500, Background: Transparent", 1.f, FColorList::White);
			canvas.DrawBoxOutline(FVector2D{ 50.f, 20.f }, 500, 30, FColorList::Green);

			// Texture.

			if (texture)
			{
				canvas.DrawTextureScaled(FVector2D{ 50.f, 55.f }, texture, 500.f, 500.f);
			}

			canvas.DrawBoxOutline(FVector2D{ 50.f, 55.f }, 500, 500, FColorList::Green);

			if (texture)
			{
				// Texture information.

				canvas.DrawFilledBox(FVector2D{ 555.f, 20.f }, 500, 500, FColorList::Black);
				canvas.DrawString(FVector2D{ 565.f, 30.f }, "Texture Information", 1.f, FColorList::Green);
				canvas.DrawString(FVector2D{ 565.f, 49.f }, "Name: " + texture->GetName(), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 68.f }, "TFC Name: " + texture->TextureFileCacheName.ToString(), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 87.f }, "TFC Guid (ABCD): " + std::to_string(texture->TextureFileCacheGuid.A) + ", " + std::to_string(texture->TextureFileCacheGuid.B) + ", " + std::to_string(texture->TextureFileCacheGuid.C) + ", " + std::to_string(texture->TextureFileCacheGuid.D), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 106.f }, "Compression: " + texture2D.GetCompressionSettingsLabel(), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 125.f }, "Filter: " + texture2D.GetTextureFilterLabel(), 1.f, FColorList::White);

				// Pixel information.
				
				FPixelFormatInfo pixelInfo = texture2D.GetPixelFormatInfo();

				canvas.DrawString(FVector2D{ 565.f, 144.f }, "Pixel Information", 1.f, FColorList::Green);
				canvas.DrawString(FVector2D{ 565.f, 163.f }, "Block Size (XYZ): " + std::to_string(pixelInfo.BlockSizeX) + ", " + std::to_string(pixelInfo.BlockSizeY) + ", " + std::to_string(pixelInfo.BlockSizeZ), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 182.f }, "Block Bytes: " + std::to_string(pixelInfo.BlockBytes), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 201.f }, "Components: " + std::to_string(pixelInfo.NumComponents), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 220.f }, "Generation: " + texture2D.GetMipGenSettingsLabel(), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 239.f }, "Format: " + texture2D.GetPixelFormatLabel(), 1.f, FColorList::White);

				// Mip information.

				FTexture2DMipMap* mipMap = texture2D.GetMipMap(0);
				FBlockInfo blockInfo = texture2D.GetBlockInfo(mipMap);
				BulkDataWrapper bulkData(&mipMap->Data);

				canvas.DrawString(FVector2D{ 565.f, 258.f }, "Mip Information", 1.f, FColorList::Green);
				canvas.DrawString(FVector2D{ 565.f, 277.f }, "Mip Maps: " + std::to_string(texture->Mips.ArrayNum), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 296.f }, "Resolution: " + std::to_string(mipMap->SizeX) + "x" + std::to_string(mipMap->SizeY), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 315.f }, "Pixels: " + std::to_string(mipMap->SizeX * mipMap->SizeY), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 334.f }, "Blocks (XY): " + std::to_string(blockInfo.BlocksX) + ", " + std::to_string(blockInfo.BlocksY), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 353.f }, "Block Size: " + std::to_string(blockInfo.BlockSize), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 372.f }, "Element Count: " + std::to_string(bulkData.GetElementCount()), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 391.f }, "Element Size: " + std::to_string(bulkData.GetElementSize()), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 410.f }, "Bulk Data Size: " + std::to_string(bulkData.GetBulkDataSize()), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 429.f }, "Bulk Disk Size: " + std::to_string(bulkData.GetBulkDataSizeOnDisk()), 1.f, FColorList::White);
				canvas.DrawString(FVector2D{ 565.f, 448.f }, "Lock Status: " + bulkData.GetLockStatusLabel(), 1.f, FColorList::White);
				canvas.DrawBoxOutline(FVector2D{ 555.f, 20.f }, 500, 500, FColorList::Green);
			}

			// Navigation box.

			canvas.DrawFilledBox(FVector2D{ 555.f, 525.f }, 500, 30, FColorList::Black);
			canvas.DrawString(FVector2D{ 565.f, 532.f }, "[<] Previous", 1.f, FColorList::White);
			canvas.DrawString(FVector2D{ 781.f, 532.f }, std::to_string(BrowseIndex) + " / " + std::to_string(TexturesToBrowse.size()), 1.f, FColorList::Green);
			canvas.DrawString(FVector2D{ 990.f, 532.f }, "Next [>]", 1.f, FColorList::White);
			canvas.DrawBoxOutline(FVector2D{ 555.f, 525.f }, 500, 30, FColorList::Green);
		}

		canvas.SetSafeToDraw(false);
	}
}

void DeveloperTools::SetActiveView(ActorWrapper caller, void* params, const std::string& functionName)
{
	if (params)
	{
		ViewId = *reinterpret_cast<int32_t*>(params);
	}
}

void DeveloperTools::DebugHook(ActorWrapper caller, void* params, const std::string& functionName)
{
	if (params)
	{

	}
}