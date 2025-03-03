// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#pragma once

#include "../common/database.hpp"

struct s_aura {
	uint32 aura_id;
	std::vector<uint16> effects;
};

enum e_aura_special : uint32 {
	AURA_SPECIAL_NOTHING		= 0x0000,	// Normal effect, nothing special
	AURA_SPECIAL_HIDE_DISAPPEAR = 0x0001	// When the character uses the hidden skill, this effect will disappear (when the character is displayed again, the effect needs to be repainted)
};

class AuraDatabase : public TypesafeYamlDatabase<uint32, s_aura> {
public:
	AuraDatabase() : TypesafeYamlDatabase("AURA_DB", 1) {

	}

	const std::string getDefaultLocation();
	uint64 parseBodyNode(const YAML::Node& node);
};

extern AuraDatabase aura_db;

void aura_reload(void);
void do_final_aura(void);
void do_init_aura(void);

std::shared_ptr<s_aura> aura_search(uint32 aura_id);
enum e_aura_special aura_special(uint16 effect_id);
void aura_make_effective(struct block_list* bl, uint32 aura_id, bool pc_saved = true);
