#ifndef ACTION_H_
#define ACTION_H_

#include <stdint.h>
#include "types.h"
#include "sha256.h"

void door_init(void);
void main_open(void);
void main_close(void);
void dump_authblock(authblock_t * ab);

void add_user(char * nickname, sha256_hash_t pinhash,uint8_t anon, uint8_t pinflags, authblock_t *dest);
void rem_user(uint8_t* id);
void lock_user(uint8_t* id);
void unlock_user(uint8_t* id);
void add_admin(uint8_t* id);
void rem_admin(uint8_t* id);
void keymigration(void);
void rem_keymigration(void);
void self_destruct(void);

#endif /*ACTION_H_*/
