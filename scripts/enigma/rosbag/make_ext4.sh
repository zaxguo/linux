# mk image
dd if=/dev/zero of=loop.img bs=1k count=40000
dd if=/dev/zero of=loop_sybil.img bs=1k count=40000

# setup loop device
echo "setting up actual loop device.."
losetup -l /dev/loop0 loop.img

echo "mkfs.vfat..."
mkfs.ext4 /dev/loop0

echo "setting up sybil images.."
losetup -l /dev/loop1 loop_sybil.img
mkfs.ext4 /dev/loop1
