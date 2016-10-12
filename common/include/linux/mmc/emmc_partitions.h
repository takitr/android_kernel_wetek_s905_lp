#ifndef _EMMC_PARTITIONS_H
#define _EMMC_PARTITIONS_H

#include<linux/genhd.h>

#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/core.h>

/* #include <mach/register.h> */
/* #include <mach/am_regs.h> */
#define CONFIG_DTB_SIZE  (256*1024U)
#define	STORE_CODE				1
#define	STORE_CACHE				(1<<1)
#define	STORE_DATA				(1<<2)

#define     MAX_PART_NAME_LEN               16
#define     MAX_MMC_PART_NUM                16

/* MMC Partition Table */
#define     MMC_PARTITIONS_MAGIC            "MPT"
#define     MMC_RESERVED_NAME               "reserved"

#define     SZ_1M                           0x00100000

/* the size of bootloader partition */
#define     MMC_BOOT_PARTITION_SIZE         (4*SZ_1M)

/* the size of reserve space behind bootloader partition */
#define     MMC_BOOT_PARTITION_RESERVED     (32*SZ_1M)

#define     RESULT_OK                       0
#define     RESULT_FAIL                     1
#define     RESULT_UNSUP_HOST               2
#define     RESULT_UNSUP_CARD               3

struct partitions {
	/* identifier string */
	char name[MAX_PART_NAME_LEN];
	/* partition size, byte unit */
	uint64_t size;
	/* offset within the master space, byte unit */
	uint64_t offset;
	/* master flags to mask out for this partition */
	unsigned mask_flags;
};

struct mmc_partitions_fmt {
	char magic[4];
	unsigned char version[12];
	int part_num;
	int checksum;
	struct partitions partitions[MAX_MMC_PART_NUM];
};
#ifdef CONFIG_MMC_AML
int aml_emmc_partition_ops(struct mmc_card *card, struct gendisk *disk);
#else
static inline int aml_emmc_partition_ops(struct mmc_card *card,
					 struct gendisk *disk)
{
	return -1;
}
#endif
unsigned int mmc_capacity(struct mmc_card *card);
int mmc_read_internal(struct mmc_card *card,
	unsigned dev_addr, unsigned blocks, void *buf);
int mmc_write_internal(struct mmc_card *card,
	unsigned dev_addr, unsigned blocks, void *buf);
int get_reserve_partition_off_from_tbl(void);
int get_reserve_partition_off(struct mmc_card *card);/* byte unit */

#endif

extern int amlmmc_dtb_init(struct mmc_card *card);
