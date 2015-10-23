for file in $(ls cases/)
do
	printf "=========="$file"===========\n"
	echo "Content: "; 
	cat cases/$file
	printf "\n"
	./build/test/test-lex cases/$file
done