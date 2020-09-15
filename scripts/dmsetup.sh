# setup loop device
echo "setting up loop device.."
losetup -l /dev/loop0 meta.img
losetup -l /dev/loop1 data.img

echo "setting up dm pool device"
dmsetup create test-thin-metadata --table '0 1000 linear /dev/loop0 0'
dmsetup create test-thin-data --table '0 1000 linear /dev/loop1 0'
# binding metadtata and data device 
# 128 sector = 64KB is the miminal unit for pool to allocate data blocks 
dmsetup create pool --table '0 1000 thin-pool /dev/mapper/test-thin-metadata /dev/mapper/test-thin-data 128 0'

echo 'load actual fs'
# actual fs always has uuid 0
# uuid > 0 share the same data block
dmsetup create actual --table '0 1000 thin /dev/mapper/pool 0'
echo 'load sybil fs 1'
dmsetup create sybil1 --table '0 1000 thin /dev/mapper/pool 1'
echo 'load sybil fs 2'
dmsetup create sybil2 --table '0 1000 thin /dev/mapper/pool 2'

