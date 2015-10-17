
for file in $(ls cases/$1*)
do
	printf "=========="$file"===========\n"
	echo "Content: "; 
	cat $file
	printf "\n"
	./build/test/test-eval $file
done
