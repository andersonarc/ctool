/**
 * @file bitset.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-10-31
 * 
 *  Bitset type with a variable amount of used bits
 *  with each bit representing either a state of 0 or 1
 * 
 *  These bitsets are quite primitive, because they can
 *  store only up to 64 bit values and all the functions
 *  accept only constant (compile-time known) indices.
 * 
 *  But this primitiveness actually makes the bitset implementation
 *  fast, because all the checks and bit mask computations are done
 *  at compile time.
 * 
 *  This particular bitset is intended for storage of flags
 *  and nothing more, and should do its task well.
 * 
 *  @note Bitset size which is passed to a generic type template
 *         and the definition macro is actually rounded up to the nearest
 *         power of 2 larger than 4 and less than 128 (8, 16, 32, 64), so
 *         defining bitset(1) and bitset(2) will result in a name conflict.
 */
    /* header guard */
#ifndef CTOOL_TYPE_BITSET_H
#define CTOOL_TYPE_BITSET_H

    /* includes */
#include "ctool/type/_internal.h" /* internal definitions */

#include <stdint.h> /* integer types */
#include <assert.h> /* static assert */

    /* defines */
/**
 * Checks if an index is in the bounds for a specific bitset
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define _bitset_index(this, index) static_assert(index < (sizeof(this._data) * 8), "index out of bounds for a bitset");

/**
 * Rounds up bitset size to a corresponding
 * primitive storage type
 * 
 * @param[in] size Size of the bitset
 */
#define _bitset_storage_type(size) _BITSET_STORAGE_TYPE_##size

#define _BITSET_STORAGE_TYPE_1 uint8_t
#define _BITSET_STORAGE_TYPE_2 uint8_t
#define _BITSET_STORAGE_TYPE_3 uint8_t
#define _BITSET_STORAGE_TYPE_4 uint8_t
#define _BITSET_STORAGE_TYPE_5 uint8_t
#define _BITSET_STORAGE_TYPE_6 uint8_t
#define _BITSET_STORAGE_TYPE_7 uint8_t
#define _BITSET_STORAGE_TYPE_8 uint8_t

#define _BITSET_STORAGE_TYPE_9  uint16_t
#define _BITSET_STORAGE_TYPE_10 uint16_t
#define _BITSET_STORAGE_TYPE_11 uint16_t
#define _BITSET_STORAGE_TYPE_12 uint16_t
#define _BITSET_STORAGE_TYPE_13 uint16_t
#define _BITSET_STORAGE_TYPE_14 uint16_t
#define _BITSET_STORAGE_TYPE_15 uint16_t
#define _BITSET_STORAGE_TYPE_16 uint16_t

#define _BITSET_STORAGE_TYPE_17 uint32_t
#define _BITSET_STORAGE_TYPE_18 uint32_t
#define _BITSET_STORAGE_TYPE_19 uint32_t
#define _BITSET_STORAGE_TYPE_20 uint32_t
#define _BITSET_STORAGE_TYPE_21 uint32_t
#define _BITSET_STORAGE_TYPE_22 uint32_t
#define _BITSET_STORAGE_TYPE_23 uint32_t
#define _BITSET_STORAGE_TYPE_24 uint32_t
#define _BITSET_STORAGE_TYPE_25 uint32_t
#define _BITSET_STORAGE_TYPE_26 uint32_t
#define _BITSET_STORAGE_TYPE_27 uint32_t
#define _BITSET_STORAGE_TYPE_28 uint32_t
#define _BITSET_STORAGE_TYPE_29 uint32_t
#define _BITSET_STORAGE_TYPE_30 uint32_t
#define _BITSET_STORAGE_TYPE_31 uint32_t
#define _BITSET_STORAGE_TYPE_32 uint32_t

#define _BITSET_STORAGE_TYPE_33 uint64_t
#define _BITSET_STORAGE_TYPE_34 uint64_t
#define _BITSET_STORAGE_TYPE_35 uint64_t
#define _BITSET_STORAGE_TYPE_36 uint64_t
#define _BITSET_STORAGE_TYPE_37 uint64_t
#define _BITSET_STORAGE_TYPE_38 uint64_t
#define _BITSET_STORAGE_TYPE_39 uint64_t
#define _BITSET_STORAGE_TYPE_40 uint64_t
#define _BITSET_STORAGE_TYPE_41 uint64_t
#define _BITSET_STORAGE_TYPE_42 uint64_t
#define _BITSET_STORAGE_TYPE_43 uint64_t
#define _BITSET_STORAGE_TYPE_44 uint64_t
#define _BITSET_STORAGE_TYPE_45 uint64_t
#define _BITSET_STORAGE_TYPE_46 uint64_t
#define _BITSET_STORAGE_TYPE_47 uint64_t
#define _BITSET_STORAGE_TYPE_48 uint64_t
#define _BITSET_STORAGE_TYPE_49 uint64_t
#define _BITSET_STORAGE_TYPE_50 uint64_t
#define _BITSET_STORAGE_TYPE_51 uint64_t
#define _BITSET_STORAGE_TYPE_52 uint64_t
#define _BITSET_STORAGE_TYPE_53 uint64_t
#define _BITSET_STORAGE_TYPE_54 uint64_t
#define _BITSET_STORAGE_TYPE_55 uint64_t
#define _BITSET_STORAGE_TYPE_56 uint64_t
#define _BITSET_STORAGE_TYPE_57 uint64_t
#define _BITSET_STORAGE_TYPE_58 uint64_t
#define _BITSET_STORAGE_TYPE_59 uint64_t
#define _BITSET_STORAGE_TYPE_60 uint64_t
#define _BITSET_STORAGE_TYPE_61 uint64_t
#define _BITSET_STORAGE_TYPE_62 uint64_t
#define _BITSET_STORAGE_TYPE_63 uint64_t
#define _BITSET_STORAGE_TYPE_64 uint64_t

/**
 * Generates a generic name for a bitset of specified size
 * 
 * @param[in] size Size of the bitset
 */
#define bitset(size) _ctool_generic_type(bitset, _bitset_storage_type(size))

/**
 * Declares a bitset of specified size (from 1 to 64 inclusive)
 * 
 * @note The declaration should be placed in a header file
 * 
 * @param[in] size Size of the bitset
**/
#define bitset_declare(size)          \
                                      \
typedef struct bitset(size) {         \
    _bitset_storage_type(size) _data; \
} bitset(size);

    /* macro functions */
/**
 * Initializes a bitset with all bits set to 0
 * 
 * @param[in] this The bitset
 */
#define bitset_init(this) this._data = 0;

/**
 * Checks a bit in a bitset and if it is set,
 * executes the following statement
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define bitset_if_set(this, index) _bitset_index(this, index); if ((this._data & (1ULL << index)) != 0)

/**
 * Checks a bit in a bitset and if it is *not* set,
 * executes the following statement
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define bitset_if_not_set(this, index) _bitset_index(this, index); if ((this._data & (1ULL << index)) == 0)

/**
 * Enables (sets to 1) a bit in a bitset
 * at the specified index
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define bitset_set(this, index)    _bitset_index(this, index); this._data |= (1ULL << index);

/**
 * Clears (sets to 0) a bit in a bitset
 * at the specified index
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define bitset_clear(this, index)  _bitset_index(this, index); this._data &= ~(1ULL << index);

/**
 * Toggles a bit in a bitset
 * at the specified index
 * 
 * @param[in] this The bitset
 * @param[in] index Constant index of the bit
 */
#define bitset_toggle(this, index) _bitset_index(this, index); this._data ^= (1ULL << index);


#endif /* CTOOL_TYPE_BITSET_H */