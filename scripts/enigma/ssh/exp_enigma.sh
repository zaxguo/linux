# mk image
echo "fs = $1"
dd if=/dev/zero of=loop.img bs=1k count=40000
# overprovision the disk for sybil
dd if=/dev/zero of=loop_sybil.img bs=1k count=100000

# setup loop device
echo "setting up actual loop device.."
losetup -l /dev/loop0 loop.img

echo "mkfs.ext4 for actual"
mke2fs -t ext4 /dev/loop0 19m

echo "mkfs.ext4 for emu disk"
losetup -l /dev/loop1 loop_sybil.img
mke2fs -t ext4 /dev/loop1 19m

mount /dev/loop0 /sybil/fs0
touch /sybil/fs0/{0..20}.pub
sync

sleep 5

mount /dev/loop1 /sybil/fs1
touch /sybil/fs1/{0..20}.pub
sync

echo "mounting sybil...."
END=$1

for ((i=2;i<END;i++)); do
	losetup -l /dev/loop${i} loop_sybil.img
	mount /dev/loop${i} /sybil/fs${i} -o nodelalloc
	sync
done

sleep 10

./a.out ${END}


