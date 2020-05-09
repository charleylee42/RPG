//#define VISUAL_STUDIO
//#define DEBUG_MSG
//#define HERO_RANDOM_MOVE

#define FPS 10
#define DELAY_MILLI_SECOND 10

//------------------------------------------------------------------------------
// Speed
//------------------------------------------------------------------------------
#define SPEED_MAX 5
#define SPEED_NORMAL 0
#define SPEED_MIN -5

//------------------------------------------------------------------------------
// DEBUF
//------------------------------------------------------------------------------
#define DEBUF_FOREVER -1

#define DEBUF_DELAY_FREEZE 5
#define DEBUF_DELAY_STUN 2
#define DEBUF_DELAY_ALLY 5

#ifndef HERO_RANDOM_MOVE
#define HERO_KEYBOARD_NO_ENTER_MOVE
#endif

//------------------------------------------------------------------------------
// Shapes
//------------------------------------------------------------------------------
#define DEFAULT_HERO_SHAPE 'H'
#define DEFAULT_MONSTER_SHAPE 'm'
#define DEFAULT_ALLY_SHAPE 'M'
#define DEFAULT_POTION_SHAPE 'b'
#define DEFAULT_BREAD_SHAPE 'B'
#define DEFAULT_TREE_SHAPE 'T'
#define DEFAULT_FLOWER_SHAPE 'F'

//------------------------------------------------------------------------------
// class Tile related
//------------------------------------------------------------------------------
#define TILE_EMPTY 'E'

//------------------------------------------------------------------------------
// class Board related
//------------------------------------------------------------------------------
#define DEFAULT_ROW_SIZE 10
#define DEFAULT_COL_SIZE 40

//------------------------------------------------------------------------------
// class Cursor related
//------------------------------------------------------------------------------
#define DEFAULT_CURSOR_SHAPE 'V'

//------------------------------------------------------------------------------
// Edit Mode related
//------------------------------------------------------------------------------
#define EDIT_MODE_EMPTY_SHAPE '.'

//------------------------------------------------------------------------------
// class Unit related
//------------------------------------------------------------------------------
#define UNIT_SHAPES "HmMJ"

#define DEFAULT_UNIT_SHAPE 'U'
#define DEFAULT_UNIT_MAX_HP 200
#define DEFAULT_UNIT_HP 100
#define DEFAULT_UNIT_MAX_MP 200
#define DEFAULT_UNIT_MP 100
#define DEFAULT_UNIT_EXP 0
#define DEFAULT_UNIT_GOLD 10
#define DEFAULT_UNIT_ATK 10
#define DEFAULT_UNIT_SPEED SPEED_NORMAL

#define NUM_DIRECTIONS 4
#define DIR_NORTH 0
#define DIR_EAST 1
#define DIR_SOUTH 2
#define DIR_WEST 3
#define DIR_NORTH_CHAR 'w'
#define DIR_EAST_CHAR 'd'
#define DIR_SOUTH_CHAR 's'
#define DIR_WEST_CHAR 'a'

//------------------------------------------------------------------------------
// class Hero related
//------------------------------------------------------------------------------
#define DEFAULT_HERO_SLOTS_CAPACITY 5

#define DEFAULT_HERO_MAX_HP 300
#define DEFAULT_HERO_HP 300
#define DEFAULT_HERO_MAX_MP 0
#define DEFAULT_HERO_MP 0
#define DEFAULT_HERO_EXP 0
#define DEFAULT_HERO_GOLD 10000
#define DEFAULT_HERO_ATK 10
#define DEFAULT_HERO_SPEED SPEED_NORMAL

//------------------------------------------------------------------------------
// class Monster related
//------------------------------------------------------------------------------
#define DEFAULT_MAX_NUM_MONS 20

#define DEFAULT_MONSTER_MAX_HP 30
#define DEFAULT_MONSTER_HP 30
#define DEFAULT_MONSTER_MAX_MP 0
#define DEFAULT_MONSTER_MP 0
#define DEFAULT_MONSTER_EXP 10
#define DEFAULT_MONSTER_GOLD 10
#define DEFAULT_MONSTER_ATK 5

//------------------------------------------------------------------------------
// class Merchant related
//------------------------------------------------------------------------------
#define DEFAULT_MAX_NUM_MERCHANTS 5

#define DEFAULT_MERCHANT_SHAPE 'G'

//------------------------------------------------------------------------------
// class Prop related
//------------------------------------------------------------------------------
#define PROP_SHAPES "TF"

#define MAX_NUM_TREES 20
#define MAX_NUM_FLOWERS 15

#define DEFAULT_PROP_SHAPE 'P'

//------------------------------------------------------------------------------
// class Item related
//------------------------------------------------------------------------------
#define ITEM_SHAPE_NONE '\0'

#define ITEM_SHAPES "bB"

#define MAX_NUM_ITEMS 10

#define DEFAULT_ITEM_SHAPE 'I'

//------------------------------------------------------------------------------
// class Potion
//------------------------------------------------------------------------------
#define DEFAULT_POTION_HP 10
#define DEFAULT_POTION_MP 0

#define DEFAULT_POTION_NAME "Potion"
#define DEFAULT_POTION_PRICE 10

//------------------------------------------------------------------------------
// class Bread
//------------------------------------------------------------------------------
#define DEFAULT_BREAD_SPEED 10
//#define DEFAULT_UBREAD_SP 0

#define DEFAULT_BREAD_NAME "Bread"
#define DEFAULT_BREAD_PRICE 1

//------------------------------------------------------------------------------
// class Inventory related
//------------------------------------------------------------------------------
#define DEFAULT_INVENTORY_CAPACITY 10
#define INVENTORY_EMPTY_SHAPE ' '

//------------------------------------------------------------------------------
// class Base related
//------------------------------------------------------------------------------

//===================================
// Base Type
//===================================
#define BASE_DIRT 0 // normal
#define BASE_FLOOR 1
#define BASE_WATER 2
#define BASE_LAVA 3
#define BASE_SNOW 4
#define BASE_MUD 5
#define BASE_MOUNTAIN 6
#define BASE_ROCK 7

#define BASE_WALL 100

//#define BASE_ICE ?
//#define BASE_GRASS ?
//#define BASE_SAND ?

//===================================
// Base Climbable
//===================================
#define BASE_DIRT_CLIMBABLE true // normal
#define BASE_FLOOR_CLIMBABLE true
#define BASE_WATER_CLIMBABLE true
#define BASE_LAVA_CLIMBABLE true
#define BASE_SNOW_CLIMBABLE true
#define BASE_MUD_CLIMBABLE true
#define BASE_MOUNTAIN_CLIMBABLE true
#define BASE_ROCK_CLIMBABLE false

#define BASE_WALL_CLIMBABLE false

//#define BASE_ICE_CLIMBABLE ?
//#define BASE_GRASS_CLIMBABLE ?
//#define BASE_SAND_CLIMBABLE ?

//===================================
// Base Shapes
//===================================
#define BASE_DIRT_SHAPE '.' // normal
#define BASE_FLOOR_SHAPE ' '
#define BASE_WATER_SHAPE '~'
#define BASE_LAVA_SHAPE '@'
#define BASE_SNOW_SHAPE '*'
#define BASE_MUD_SHAPE ','
#define BASE_MOUNTAIN_SHAPE '^'
#define BASE_ROCK_SHAPE 'D'

#define BASE_WALL_01_SHAPE '+'
#define BASE_WALL_02_SHAPE '|'
#define BASE_WALL_03_SHAPE '-'
#define BASE_WALL_04_SHAPE '\\'
#define BASE_WALL_05_SHAPE '/'
#define BASE_WALL_06_SHAPE '#'
#define BASE_WALL_07_SHAPE '['
#define BASE_WALL_08_SHAPE ']'

//#define BASE_ICE_SHAPE ?
//#define BASE_GRASS_SHAPE ?
//#define BASE_SAND_SHAPE ?

//==================================
// Base Speed
//==================================
#define BASE_DIRT_SPEED 0 // normal
#define BASE_FLOOR_SPEED 0
#define BASE_WATER_SPEED 3
#define BASE_LAVA_SPEED 1
#define BASE_SNOW_SPEED 2
#define BASE_MUD_SPEED 3
#define BASE_MOUNTAIN_SPEED 2
#define BASE_ROCK_SPEED 0

#define BASE_WALL_SPEED 0

//#define BASE_ICE_SPEED ?
//#define BASE_GRASS_SPEED ?
//#define BASE_SAND_SPEED ?

//===================================
// Shockwave related
//===================================
#define HERO_POSTIONING_WAVE_RANGE 10
#define HERO_POSTIONING_WAVE_FRAME_INTERVAL 1
#define HERO_POSTIONING_WAVE_SHAPE '*'

#define MAX_NUM_SHOCKWAVES 100

#define MAGIC_00_FIREWAVE 0
#define MAGIC_00_FIREWAVE_ATK 200

#define MAGIC_01_FREEZE 1
#define MAGIC_01_FREEZE_ATK 10

#define MAGIC_02_STUN 2
#define MAGIC_02_STUN_ATK 15

#define MAGIC_03_ALLY 3
#define MAGIC_03_ALLY_ATK 5

#define MAGIC_04_JUICE 4
#define DEFAULT_JUICE_HP 5

//===================================
// AirBalloon related
//===================================
#define DEFAULT_MAX_NUM_BALLOONS 5

#define DEFAULT_AIR_BALLOON_SHAPE 'L'

#define DEFAULT_AIR_BALLOON_SPEED 10

#define DEFAULT_MAX_NUM_BOATS 10

#define DEFAULT_BOAT_SHAPE ':'

#define DEFAULT_BOAT_SPEED 10

//===================================
// Weapon related
//===================================
#define DEFAULT_MAX_NUM_WEAPONS 5

#define DEFAULT_WEAPON_NAME "Weapon"
#define DEFAULT_WEAPON_PRICE 0
#define DEFAULT_WEAPON_ATK 0

#define WEAPON_ONE_HAND 1
#define WEAPON_TWO_HAND 2

#define WEAPON_SHAPE_ONE_HAND '!'
#define WEAPON_SHAPE_TWO_HAND '?'

//===================================
// Armor related
//===================================
#define DEFAULT_MAX_NUM_ARMORS 5

#define DEFAULT_ARMOR_DEF 10

#define DEFAULT_ARMOR_NAME "Armor"
#define DEFAULT_ARMOR_PRICE 0

#define ARMOR_SHAPE_HEAD 'A'
#define ARMOR_SHAPE_CHEST 'W'
#define ARMOR_SHAPE_BACK 'Q'
#define ARMOR_SHAPE_HANDS 'U'
#define ARMOR_SHAPE_LEGS 'L'
#define ARMOR_SHAPE_FEET 'F'

#define BODY_PART_ID_NONE 0
#define BODY_PART_ID_HEAD 1
#define BODY_PART_ID_CHEST 2
#define BODY_PART_ID_BACK 3
#define BODY_PART_ID_HANDS 4
#define BODY_PART_ID_LEGS 5
#define BODY_PART_ID_FEET 6
#define BODY_PART_ID_LEFT_HAND 7
#define BODY_PART_ID_RIGHT_HAND 8

//===================================
// Chest related
//===================================

#define DEFAULT_CHEST_SHAPE 'c'
#define DEFAULT_KEY_SHAPE 't'
