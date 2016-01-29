/*
 * File: config.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: General configuration of the kernel
 */

#ifndef _ATOMOS_CONFIG_H_
# define _ATOMOS_CONFIG_H_

/*
 * Debug
 */

# define CONFIG_DEBUG
# define CONFIG_DEBUG_SERIAL
# undef  CONFIG_DEBUG_VGA

/*
 * Std IO
 */

# define CONFIG_OUTPUT_VGA
# undef  CONFIG_OUTPUT_SERIAL

/*
 * Architecture: only i386 for the moment
 */

# define CONFIG_ARCH "i386"

/*
 * Filesystems
 */
# undef CONFIG_EXT2_FS
# undef CONFIG_FAT_FS

/*
 * Block devices
 */
# undef CONFIG_BLK_DEV

/*
 * Character devices
 */
# undef CONFIG_CHR_DEV
# define CONFIG_SERIAL
# define CONFIG_VGA
# define CONFIG_KEYBOARD

#endif /*!_ATOMOS_CONFIG_H_ */
