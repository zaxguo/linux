# mk image
echo "fs = $1"
trace_lib=keyword2.log.post
#dd if=/dev/zero of=loop.img bs=1k count=40000
#dd if=/dev/zero of=loop.img bs=1k count=2097152 # 2GB disk
# must overprovision the sybil disk to make as large actual fs
#dd if=/dev/zero of=loop_sybil.img bs=1k count=100000

# setup loop device
echo "setting up actual loop device.."
losetup -l /dev/loop0 loop_2g.img

echo "mkfs.ext4 for actual"
#mke2fs -t ext4 /dev/loop0 19m
#mke2fs -t ext4 /dev/loop0

echo "mkfs.ext4 for emu disk"
losetup -l /dev/loop1 loop_sybil_2g.img
mke2fs -t ext4 /dev/loop1

# data in fs0 are already made
mount /dev/loop0 /sybil/fs0
sync

# setup dirs & files, etc.
mount /dev/loop1 /sybil/fs1
mkdir -p /sybil/fs1/mail_index
mkdir -p /sybil/fs1/mail_index/seg_1
touch /sybil/fs1/mail_index/snapshot1.json
touch /sybil/fs1/mail_index/schema_1.json
touch /sybil/fs1/mail_index/seg_1/cfmeta.json
touch /sybil/fs1/mail_index/seg_1/segmeta.json
touch /sybil/fs1/mail_index/seg_1/cf.dat

./a.out 1 dummy

sync


echo "mounting sybil...."
END=$1

for ((i=2;i<END;i++)); do
	losetup -l /dev/loop${i} loop_sybil_2g.img
	mount /dev/loop${i} /sybil/fs${i} -o nodelalloc 
	sync
done


./a.out ${END} ${trace_lib}


