for i in `seq 0 100 3000`; do
	./preprocess.py timing3.log ${i} && ./mi.py;
done
