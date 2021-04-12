# mk image
echo "fs = $1"
trace_lib=keyword2.log.post
dd if=/dev/zero of=loop.img bs=1k count=64000
# must overprovision the sybil disk to make as large actual fs
dd if=/dev/zero of=loop_sybil.img bs=1k count=100000
#dd if=/dev/zero of=loop.img bs=1k count=2097152 # 2GB disk
#dd if=/dev/zero of=loop_sybil.img bs=1k count=100000

# setup loop device
echo "setting up actual loop device.."
losetup -l /dev/loop0 loop.img

echo "mkfs.ext4 for actual"
mke2fs -t ext4 /dev/loop0 60m
#mke2fs -t ext4 /dev/loop0

echo "mkfs.ext4 for emu disk"
losetup -l /dev/loop1 loop_sybil.img
mke2fs -t ext4 /dev/loop1 60m

mount /dev/loop0 /sybil/fs0
touch /sybil/fs0/model.bin
sync

# setup dirs & files, etc.
mount /dev/loop1 /sybil/fs1
touch /sybil/fs1/model.bin

./a.out 0 dummy
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


