// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef	_VENDING_HPP_
#define	_VENDING_HPP_

#include "../common/cbasetypes.hpp"
#include "../common/db.hpp"
#include "../common/mmo.hpp"

struct map_session_data;
struct s_search_store_search;
struct s_autotrader;

struct s_vending {
	short index; /// cart index (return item data)
	short amount; ///amout of the item for vending
	unsigned int value; ///at wich price
};

DBMap * vending_getdb();
void do_final_vending(void);
void do_init_vending(void);
void do_init_vending_autotrade( void );
 
void vending_reopen( struct map_session_data* sd );
void vending_closevending(struct map_session_data* sd);
int8 vending_openvending(struct map_session_data* sd, const char* message, const uint8* data, int count, struct s_autotrader *at);
void vending_vendinglistreq(struct map_session_data* sd, int id);
void vending_purchasereq(struct map_session_data* sd, int aid, int uid, const uint8* data, int count);
bool vending_search(struct map_session_data* sd, t_itemid nameid);
bool vending_searchall(struct map_session_data* sd, const struct s_search_store_search* s);

void vending_autovend(uint32 account_id, uint32 char_id);
bool vending_create_autovend(struct map_session_data* sd);
bool vending_close_autovend(struct map_session_data* sd);
void do_reinit_vending_autovend(struct map_session_data* sd);

#endif /* _VENDING_HPP_ */
