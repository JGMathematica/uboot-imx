/*
 * Copyright 2017 NXP
 */

#ifndef __PICO_IMX7D_ANDROID_COMMON_H
#define __PICO_IMX7D_ANDROID_COMMON_H

#define CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_DUALSPEED

#define CONFIG_BCB_SUPPORT
#define CONFIG_CMD_READ

#define CONFIG_USB_GADGET
#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_USB_GADGET_VBUS_DRAW     2

#define CONFIG_G_DNL_VENDOR_NUM         0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM        0x0d02
#define CONFIG_G_DNL_MANUFACTURER	"FSL"

#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_CMD_FASTBOOT
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_FASTBOOT_FLASH

#define CONFIG_FSL_FASTBOOT
#define CONFIG_ANDROID_RECOVERY

#if defined CONFIG_NAND_BOOT
#define CONFIG_FASTBOOT_STORAGE_NAND
#elif defined CONFIG_SYS_BOOT_SATA
#define CONFIG_FASTBOOT_STORAGE_SATA
#else
#define CONFIG_FASTBOOT_STORAGE_MMC
#endif

#define CONFIG_CMD_BOOTA
#define CONFIG_SUPPORT_RAW_INITRD
#define CONFIG_SERIAL_TAG

#undef CONFIG_EXTRA_ENV_SETTINGS
#undef CONFIG_BOOTCOMMAND

#define CONFIG_EXTRA_ENV_SETTINGS					\
    "script=boot.scr\0" \
    "image=zImage\0" \
    "console=ttymxc4\0" \
    "splashpos=m,m\0" \
    "som=imx7d-pico\0" \
    "baseboard=nymph\0" \
    "default_baseboard=dwarf\0" \
    "fdtfile=undefined\0" \
    "fdt_high=0xffffffff\0" \
    "initrd_high=0xffffffff\0" \
    "bootramdisk=uramdisk.img\0" \
    "initrd_addr=0x83800000\0" \
    "fdt_addr=0x83000000\0" \
    "bootargs_base=console=ttymxc4,115200\0" \
    "boot_fdt=try\0" \
    "mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
    "mmcpart=1\0" \
    "searchbootdev=" \
        "if test ${bootdev} = SD0; then " \
            "setenv mmcroot /dev/mmcblk2p2 rootwait rw; " \
        "else " \
            "setenv mmcroot /dev/mmcblk0p2 rootwait rw; " \
        "fi\0" \
    "mmcargs=setenv bootargs console=${console},${baudrate} androidboot.console=ttymxc4\0 " \
    "loadbootscript=" \
        "fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
    "bootscript=echo Running bootscript from mmc ...; " \
        "source\0" \
    "loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
    "loadramdisk=fatload mmc ${mmcdev}:${mmcpart} ${initrd_addr} ${bootramdisk}\0" \
    "setfdt=setenv fdtfile ${som}_${baseboard}.dtb\0" \
    "loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdtfile}\0" \
    "bootenv=uEnv.txt\0" \
    "loadbootenv=fatload mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
    "importbootenv=echo Importing environment from mmc ...; " \
        "env import -t -r $loadaddr $filesize\0" \
    "tn_boot_init=" \
           "mmc dev ${mmcdev}; if mmc rescan; then " \
        "if run loadbootenv; then " \
        "echo Loaded environment from ${bootenv};" \
        "run importbootenv;" \
        "fi;" \
           "if run loadimage; then " \
               "run setfdt; " \
               "run loadfdt; " \
               "else " \
                   "echo WARN: Cannot load kernel from boot media; " \
               "fi; " \
           "fi; " \
           "if run loadramdisk; then " \
	       "run mmcargs;" \
               "bootz ${loadaddr} ${initrd_addr} ${fdt_addr};" \
           "fi;" \
        "splashpos=m,m\0"	  \
	"fdt_high=0xffffffff\0"	  \
	"initrd_high=0xffffffff\0" \


#define CONFIG_FASTBOOT_BUF_ADDR   CONFIG_SYS_LOAD_ADDR
#define CONFIG_FASTBOOT_BUF_SIZE   0x19000000

#endif /* __PICO_IMX7D_ANDROID_COMMON_H */
