//VBXCOPYRIGHTTAG
/**
 * @file
 * @defgroup VectorBlox_MXP VectorBlox MXP
 * @brief Details the instance of our VectorBlox MXP processor
 *
 * @ingroup VBXapi
 */
/**@{*/

#ifndef __VECTORBLOX_MXP_NIOS_H
#define __VECTORBLOX_MXP_NIOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vbx_macros.h"
#include "sys/alt_llist.h"

// From "Creating a Custom Device Driver for the HAL" in the
// NIOS II Software Developer's Handbook:
//
// - The *_INSTANCE macro performs any required static memory allocation. For
// drivers, *_INSTANCE is invoked once per device instance, so that memory can
// be initialized on a per-device basis. [...]
// - The *_INIT macro performs runtime initialization of the device driver [...]
//
// Both macros take two input arguments:
// - The first argument, name, is the capitalized name of the device instance.
// - The second argument, dev, is the lower case version of the device name.
// dev is the name given to the component at system generation time.

typedef struct {

	/* Standard device parameters */
	alt_llist	llist;
	const char	*name;

	/* MXP characteristics */
	vbx_mxp_t   mxp;

} vbx_mxp_dev_t;

void      _vectorblox_mxp_init( vbx_mxp_dev_t *dev );

#define VECTORBLOX_MXP_INSTANCE(name, dev) \
static vbx_mxp_dev_t dev = \
{ \
	ALT_LLIST_ENTRY, \
	(name##_NAME), \
	{\
		((vbx_void_t *)(((int)0x80000000)|(int)(name##_BASE                            ))), /* addr, force uncached */ \
		((vbx_void_t *)(((int)0x80000000)|(int)(name##_BASE + name##_SCRATCHPAD_KB*1024))), /* end,  force uncached */ \
		((vbx_void_t *)((int) 0)), /* instr_port_addr */ \
		((uint32_t *)((int) 0)), /* instr_port_addr */ \
		(name##_SCRATCHPAD_KB*1024), \
		(name##_CORE_FREQ), \
		(name##_MEMORY_WIDTH_LANES*4), \
		(name##_VECTOR_LANES*4), \
		(name##_VECTOR_LANES), \
		(name##_VCUSTOM0_LANES), \
		(name##_VCUSTOM1_LANES), \
		(name##_VCUSTOM2_LANES), \
		(name##_VCUSTOM3_LANES), \
		(name##_VCUSTOM4_LANES), \
		(name##_VCUSTOM5_LANES), \
		(name##_VCUSTOM6_LANES), \
		(name##_VCUSTOM7_LANES), \
		(name##_VCUSTOM8_LANES), \
		(name##_VCUSTOM9_LANES), \
		(name##_VCUSTOM10_LANES), \
		(name##_VCUSTOM11_LANES), \
		(name##_VCUSTOM12_LANES), \
		(name##_VCUSTOM13_LANES), \
		(name##_VCUSTOM14_LANES), \
		(name##_VCUSTOM15_LANES), \
		(name##_MAX_MASKED_VECTOR_LENGTH), \
		(name##_MASK_PARTITIONS), \
		(name##_VECTOR_CUSTOM_INSTRUCTIONS), \
		(name##_MULFXP_WORD_FRACTION_BITS), \
		(name##_MULFXP_HALF_FRACTION_BITS), \
		(name##_MULFXP_BYTE_FRACTION_BITS), \
		((char) 0), /* init */ \
		((vbx_void_t *)(((int)0x80000000)|(int)(name##_BASE                            ))), /* sp, force uncached */ \
		((vbx_void_t **)(NULL)), /*sp_stack */ \
		((int) 0), /* sp_stack_top */ \
		((int) 0)  /* sp_stack_max */ \
	} \
}

/** Initialize MXP processor
 * Reads key parameters, saving to @ref vbx_mxp_dev_t
 *
 * @param[in] name
 * @param[out] dev
 */
#define VECTORBLOX_MXP_INIT(name, dev) \
	VBX_S{ \
		_vectorblox_mxp_init( &dev ); \
	}VBX_E


#ifdef __cplusplus
}
#endif

#endif //__VECTORBLOX_MXP_NIOS_H
/**@}*/
