# mk image
echo "fs = $1"
dd if=/dev/zero of=loop.img bs=1k count=40000
# overprovision the disk for sybil
#dd if=/dev/zero of=loop_sybil.img bs=1k count=100000

# setup loop device
echo "setting up actual loop device.."
losetup -l /dev/loop0 loop.img

echo "mkfs.ext4 for actual"
mke2fs -t ext4 /dev/loop0 19m 

echo "mounting sybil...."
END=$1
for ((i=1;i<END;i++)); do
	cp loop.img loop_${i}.img
	losetup -l /dev/loop${i} loop_${i}.img
	mount /dev/loop${i} /sybil/fs${i}
	touch /sybil/fs${i}/test.txt
done
mount /dev/loop0 /sybil/fs0
touch /sybil/fs0/test.txt 

./a.out ${END}


