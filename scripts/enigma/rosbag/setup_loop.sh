mount /dev/loop0 /sybil/fs0
touch /sybil/fs0/test.txt 
mount /dev/loop1 /sybil/fs1
touch /sybil/fs1/test.txt 

echo "mounting sybil...."
END=9
for ((i=2;i<END;i++)); do
	losetup -l /dev/loop${i} loop_sybil.img
	mount /dev/loop${i} /sybil/fs${i}
	touch /sybil/fs${i}/test.txt
	sleep 10
done
