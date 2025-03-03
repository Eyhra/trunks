// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "aura.hpp"

#include "battle.hpp"
#include "map.hpp"
#include "pc.hpp"

AuraDatabase aura_db;

std::unordered_map<uint16, enum e_aura_special> special_effects{
	{202, AURA_SPECIAL_HIDE_DISAPPEAR},
	{362, AURA_SPECIAL_HIDE_DISAPPEAR}
};

//************************************
// Method:      getDefaultLocation
// FullName:    AuraDatabase::getDefaultLocation
// Description: Get the specific path of the YAML data file
// Access:      public 
// Returns:     const std::string
//************************************
const std::string AuraDatabase::getDefaultLocation() {
	return std::string(db_path) + "/aura_db.yml";
}

//************************************
// Method:      parseBodyNode
// FullName:    AuraDatabase::parseBodyNode
// Description: The main processing function for parsing the Body node
// Access:      public 
// Parameter:   const YAML::Node & node
// Returns:     uint64
//************************************
uint64 AuraDatabase::parseBodyNode(const YAML::Node& node) {
	uint32 aura_id = 0;

	if (!this->asUInt32(node, "AuraID", aura_id)) {
		return 0;
	}

	if (aura_id <= 0) {
		return 0;
	}

	auto aura = this->find(aura_id);
	bool exists = aura != nullptr;

	if (!exists) {
		aura = std::make_shared<s_aura>();
		aura->aura_id = aura_id;
	}
	else {
		aura->effects.clear();
	}

	if (!this->nodeExists(node, "EffectList")) {
		return 0;
	}

	for (const YAML::Node& subNode : node["EffectList"]) {
		uint16 effect_id;

		if (!this->asUInt16(subNode, "EffectID", effect_id)) {
			return 0;
		}

		aura->effects.push_back(effect_id);
	}

	if (!exists) {
		this->put(aura->aura_id, aura);
	}

	return 1;
}

//************************************
// Method:      aura_search
// FullName:    aura_search
// Description: Get the information recorded in aura_db.yml according to the aura number
// Access:      public 
// Parameter:   uint32 aura_id
// Returns:     std::shared_ptr<s_aura>
//************************************
std::shared_ptr<s_aura> aura_search(uint32 aura_id) {
	return aura_db.find(aura_id);
}

//************************************
// Method:      aura_special
// FullName:    aura_special
// Description: Given an effect number, query whether it is a special effect, and return its flag bit
// Access:      public 
// Parameter:   uint16 effect_id
// Returns:     enum e_aura_special 特殊标记位
//************************************
enum e_aura_special aura_special(uint16 effect_id) {
	if (special_effects.find(effect_id) != special_effects.end()) {
		return special_effects[effect_id];
	}
	return AURA_SPECIAL_NOTHING;
}

//************************************
// Method:      aura_make_effective
// FullName:    aura_make_effective
// Description: Sets the aura to bl and enables it to refresh immediately
// Access:      public 
// Parameter:   struct block_list * bl
// Parameter:   uint32 aura_id
// Parameter:   bool pc_saved If it is a player unit, whether to save this aura to the database
// Returns:     void
//************************************
void aura_make_effective(struct block_list* bl, uint32 aura_id, bool pc_saved) {
	if (!bl) return;
	if (aura_id && !aura_search(aura_id)) return;

	map_freeblock_lock();

	struct map_data* mapdata = map_getmapdata(bl->m);
	struct s_unit_common_data* ucd = status_get_ucd(bl);

	if (ucd) {
		ucd->aura.id = aura_id;
	}

	switch (bl->type)
	{
	case BL_PC: {
		struct map_session_data* sd = BL_CAST(BL_PC, bl);
		if (!sd) break;

		if (pc_saved) {
			pc_setglobalreg(sd, add_str(AURA_VARIABLE), aura_id);
		}

		if (ucd) {
			ucd->aura.hidden = false;
		}
		pc_setpos(sd, sd->mapindex, sd->bl.x, sd->bl.y, CLR_OUTSIGHT);
		break;
	}
	case BL_MOB:
		// If it is a monster, you can use clif_clearunit_area to send CLR_TRICKDEAD directly to clear the cache
		// Instead of broadcasting the clif_outsight packet like the else branch
		// In this way, when the aura is replaced during the movement of the monster, there will be no obvious effect of disappearing and reappearing.
		if (mapdata && mapdata->users) {
			clif_clearunit_area(bl, CLR_TRICKDEAD);
			map_foreachinallrange(clif_insight, bl, AREA_SIZE, BL_PC, bl);
		}
		break;
	default:
		if (mapdata && mapdata->users) {
			map_foreachinallrange(clif_outsight, bl, AREA_SIZE, BL_PC, bl);
			map_foreachinallrange(clif_insight, bl, AREA_SIZE, BL_PC, bl);
		}
		break;
	}

	map_freeblock_unlock();
}

//************************************
// Method:      aura_reload
// FullName:    aura_reload
// Description: Reload the aura_db.yml aura combo database
// Access:      public 
// Parameter:   void
// Returns:     void
//************************************
void aura_reload(void) {
	aura_db.clear();
	aura_db.load();
}

//************************************
// Method:      do_final_aura
// FullName:    do_final_aura
// Description: Release the content saved by the instance object aura_db of AuraDatabase
// Access:      public 
// Parameter:   void
// Returns:     void
//************************************
void do_final_aura(void) {
	aura_db.clear();
}

//************************************
// Method:      do_init_aura
// FullName:    do_init_aura
// Description: Initialize the aura mechanism, load data from the aura_db.yml aura combination database
// Access:      public 
// Parameter:   void
// Returns:     void
//************************************
void do_init_aura(void) {
	aura_db.load();
}